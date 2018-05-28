#include "gui/textrender.h"
#include "gui/utf8.h"

#include "core/mathlib.h"

#include <algorithm>
#include <iostream>


namespace
{

FT_Pos ftFloor(FT_Pos x)
{
    return x & -64;
}

FT_Error FaceRequester(
    FTC_FaceID ftc_face_id,
    FT_Library library,
    FT_Pointer /*requestData*/,
    FT_Face* face)
{
    auto face_id = static_cast<bmce::FaceId*>(ftc_face_id);

    if (face_id->data() != nullptr)
    {
        return FT_New_Memory_Face(
            library,
            face_id->data(),
            face_id->dataSize(),
            face_id->index(),
            face);
    }

    return FT_New_Face(
        library, face_id->fileName().c_str(), face_id->index(), face);
}

class RasterData
{
public:
    using Pos = bmce::Pos2d<int>;
    using Rect = bmce::Rect<int>;

private:
    Pos offset_;
    bmce::RGBA8 color_;
    bmce::Texture* texture_;
    Rect* rect_;

public:
    RasterData(const Pos& offset, bmce::Texture* texture) :
        offset_(offset),
        texture_(texture),
        rect_(nullptr)
    {
    }

    const Pos& offset() const
    {
        return offset_;
    }

    const bmce::RGBA8& color() const
    {
        return color_;
    }

    void setColor(const bmce::RGBA8& color)
    {
        color_ = color;
    }

    bmce::Texture* texture()
    {
        return texture_;
    }

    const Rect* rect()
    {
        return rect_;
    }
};

void RasterCallback(
    const int sy,
    const int count,
    const FT_Span* spans,
    void* const user)
{
    auto raster_data = static_cast<RasterData*>(user);

    int offset_x = raster_data->offset().x;
    int offset_y = raster_data->offset().y;
    bmce::RGBA8 fg = raster_data->color();
    bmce::Texture* texture = raster_data->texture();
    const RasterData::Rect* rect = raster_data->rect();

    int y = -sy + offset_y;
    if (y < 0 || y >= texture->height())
    {
        return;
    }

    for (int i = 0; i < count; ++i)
    {
        const FT_Span& span = spans[i];
        int sx = span.x + offset_x;
        fg.a = span.coverage;

        for (int x = sx; x < span.len + sx; ++x)
        {
            if (rect != nullptr && !rect->inside(x, y))
            {
                continue;
            }

            if (x < 0 || x >= texture->width())
            {
                continue;
            }

            texture->pixel(x, y).blend(fg);
        }
    }
}

} // namespace


namespace bmce
{

TextRender::TextRender()
{
    init();
}

TextRender::TextRender(size_t dpi) :
    hdpi_(dpi),
    vdpi_(dpi)
{
    init();
}

TextRender::TextRender(size_t hdpi, size_t vdpi) :
    hdpi_(hdpi),
    vdpi_(vdpi)
{
    init();
}

TextRender::~TextRender()
{
    release();
}

size_t TextRender::hDPI() const
{
    return hdpi_;
}

size_t TextRender::vDPI() const
{
    return vdpi_;
}

const Pos2d<int>& TextRender::pos() const
{
    return pos_;
}

void TextRender::setPos(const Pos2d<int> &pos)
{
    pos_ = pos;
}

void TextRender::setPos(int x, int y)
{
    pos_.x = x;
    pos_.y = y;
}

const Font& TextRender::font() const
{
    return font_;
}

void TextRender::setFont(const Font& font)
{
    font_ = font;
    dirty_ = true;
}

const TextConstraints& TextRender::constraints() const
{
    return constraints_;
}

void TextRender::setConstraints(const TextConstraints& constraints)
{
    constraints_ = constraints;
    dirty_ = true;
}

void TextRender::select(size_t begin, size_t end)
{
    if (!text_.empty())
    {
        use_selection_ = true;
        size_t last = text_.size() - 1;
        sel_begin_ = std::max<size_t>(0, std::min(begin, last));
        sel_end_ = std::max<size_t>(0, std::min(end, last));
    }
    else
    {
        deselect();
    }
}

void TextRender::deselect()
{
    use_selection_ = false;
    sel_begin_ = 0;
    sel_end_ = 0;
}

FaceId* TextRender::faceId(const std::string& name)
{
    auto pos = faces_.find(name);

    if (faces_.end() == pos)
    {
        return nullptr;
    }

    return &pos->second;
}

void TextRender::addFace(const std::string& file_name)
{
    auto pos = faces_.find(file_name);
    if (faces_.end() == pos)
    {
        faces_[file_name] = FaceId(file_name);
    }
}

void TextRender::addFace(
    const std::string &name, const std::string& file_name)
{
    auto pos = faces_.find(name);
    if (faces_.end() == pos)
    {
        faces_[name] = FaceId(file_name);
    }
}

void TextRender::addFace(
    const std::string &name,
    const FaceId::Byte *data,
    FaceId::Size data_size)
{
    auto pos = faces_.find(name);
    if (faces_.end() == pos)
    {
        faces_[name] = FaceId(data, data_size);
    }
}

void TextRender::delFace(const std::string& name)
{
    auto pos = faces_.find(name);
    if (faces_.end() != pos)
    {
        faces_.erase(pos);
    }
}

const UString& TextRender::text() const
{
    return text_;
}

void TextRender::setText(const std::string& text)
{
    text_.resize(0);
    utf8::unchecked::utf8to32(text.begin(), text.end(), back_inserter(text_));
    if (use_selection_)
    {
        select(sel_begin_, sel_end_);
    }
    dirty_ = true;
}

Rect<int> TextRender::rect()
{
    validate();
    Rect<int> ret(rect_);
    ret.add(pos_.x - rect_.x0, pos_.y - rect_.y0);
    return ret;
}

void TextRender::render(Texture* texture)
{
    validate();

    Pos2d<int> adjusted_pos(pos_);
    adjusted_pos.add(-rect_.x0, -rect_.y0);

    RasterData raster_data(adjusted_pos, texture);

    FT_Raster_Params params = {};
    params.flags = FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
    params.gray_spans = RasterCallback;
    params.user = &raster_data;

    auto begin = glyphs_.begin();
    auto end = glyphs_.end();
    if (use_selection_)
    {
        begin += sel_begin_;
        end = glyphs_.begin() + sel_end_ + 1;
    }

    if (font_.outlineSize() > 0)
    {
        FT_Stroker stroker;
        if (FT_Stroker_New(library_, &stroker) != 0)
        {
            NW_ERROR("FreeType2 stroker init failed.")
        }
        else
        {
            raster_data.setColor(font_.outlineColor());
            for (auto it = begin; it != end; ++it)
            {
                FT_Glyph glyph = *it;
                if (glyph == nullptr) { continue; }
                if (glyph->format != FT_GLYPH_FORMAT_OUTLINE) { continue; }
                FT_Glyph_StrokeBorder(&glyph, stroker, false, false);
                FT_Outline_Render(
                    library_,
                    &reinterpret_cast<FT_OutlineGlyph>(glyph)->outline,
                    &params);
                FT_Done_Glyph(glyph);
            }
            FT_Stroker_Done(stroker);
        }
    }

    raster_data.setColor(font_.color());
    for (auto it = begin; it != end; ++it)
    {
        FT_Glyph glyph = *it;
        if (glyph == nullptr) { continue; }
        if (glyph->format != FT_GLYPH_FORMAT_OUTLINE) { continue; }
        FT_Outline_Render(
            library_,
            &reinterpret_cast<FT_OutlineGlyph>(glyph)->outline,
            &params);
    }
}

void TextRender::init()
{
    release();

    int error = FT_Init_FreeType(&library_);
    if (error)
    {
        NW_ERROR("FreeType2 init failed.")
    }

    error = FTC_Manager_New(
        library_, 0, 0, 0, &FaceRequester, nullptr, &manager_);
    if (error)
    {
        NW_ERROR("FreeType2 manager init failed.")
    }

    error = FTC_ImageCache_New(manager_, &image_cache_);
    if (error)
    {
        NW_ERROR("FreeType2 cache init failed.")
    }
}

void TextRender::release()
{
    FTC_Manager_Done(manager_);
    FT_Done_FreeType(library_);
}

void TextRender::validate()
{
    if (dirty_)
    {
        genGlyphs();
        dirty_ = false;
    }
}

void TextRender::genGlyphs()
{
    resetCache();

    FT_Face face;
    FTC_ScalerRec scaler = {};
    {
        bmce::FaceId* face_id = faceId(font_.name());
        if (face_id == nullptr)
        {
            NW_ERROR("Font '" << font_.name() << "' not registered.")
            return;
        }

        int error = FTC_Manager_LookupFace(manager_, face_id, &face);
        if (error != 0)
        {
            if (error == FT_Err_Unknown_File_Format)
            {
                NW_ERROR(
                    "FreeType2  font '" << font_.name() << "' unknown format.")
            }
            else
            {
                NW_ERROR(
                    "FreeType2  font '" << font_.name() << "' init failed.")
            }

            return;
        }

        scaler.face_id = static_cast<FTC_FaceID>(face_id);
        scaler.width = font_.size() * 64;
        scaler.height = scaler.width;
        scaler.pixel = 0;
        scaler.x_res = hDPI();
        scaler.y_res = vDPI();
    }

    FT_Vector pen = {0, 0};
    FT_UInt prev_index = 0;

    auto font_height = static_cast<float>(face->height);
    font_height /= face->units_per_EM;
    font_height *= font_.size();

    FT_Matrix transform = {};
    {
        static auto pi_over_180 = static_cast<FPType>(M_PI) / 180;
        FPType angle = -font_.rotation() * pi_over_180;
        transform.xx = static_cast<FT_Fixed>( cos(angle) * 0x10000L);
        transform.xy = static_cast<FT_Fixed>(-sin(angle) * 0x10000L);
        transform.yx = static_cast<FT_Fixed>( sin(angle) * 0x10000L);
        transform.yy = static_cast<FT_Fixed>( cos(angle) * 0x10000L);
    }

    glyphs_.resize(text_.size());
    for (size_t i = 0; i < text_.size(); ++i)
    {
        FT_UInt index = FT_Get_Char_Index(face, text_[i]);
        int error = FTC_ImageCache_LookupScaler(
            image_cache_,
            &scaler,
            FT_LOAD_DEFAULT,
            index,
            &glyphs_[i],
            nullptr);
        if (error != 0)
        {
            NW_WARNING(
                "FreeType2 get glyph failed for char '"
                << text_[i] << "'")
            continue;
        }
        FT_Glyph_Copy(glyphs_[i], &glyphs_[i]);

        if (glyphs_[i]->format != FT_GLYPH_FORMAT_OUTLINE)
        {
            continue;
        }

        // Kerning
        if (FT_HAS_KERNING(face) && prev_index != 0 && index != 0)
        {
            FT_Vector delta = {};
            FT_Get_Kerning(
                face,
                prev_index,
                index,
                FT_KERNING_DEFAULT,
                &delta);
            pen.x += delta.x;
            pen.y += delta.y;
        }
        prev_index = index;

        FT_Vector vec = pen;
        pen.x += glyphs_[i]->advance.x >> 10;
        pen.y += glyphs_[i]->advance.y >> 10;

        if (constraints_.isNewLine(text_[i]))
        {
            pen.x = 0;
            pen.y -= font_height * 64 * 1.75;
            prev_index = 0;
        }
        else if ((pen.x >> 6) > constraints_.width())
        {
            pen.x = 0;
            pen.y -= font_height * 64;
            prev_index = 0;
        }

        FT_Vector_Transform(&vec, &transform);
        FT_Glyph_Transform(glyphs_[i], &transform, &vec);
    }

    calcRect();
}

void TextRender::calcRect()
{
    FT_BBox g_bbox = {};

    FT_BBox bbox = {};
    bbox.xMin = 32000;
    bbox.yMin = 32000;
    bbox.xMax = -32000;
    bbox.yMax = -32000;

    for (auto glyph: glyphs_)
    {
        if (glyph == nullptr)
        {
            continue;
        };

        FT_Outline_Get_BBox(
            &reinterpret_cast<FT_OutlineGlyph>(glyph)->outline,
            &g_bbox);

        if (g_bbox.xMin < bbox.xMin) { bbox.xMin = g_bbox.xMin; }
        if (g_bbox.yMin < bbox.yMin) { bbox.yMin = g_bbox.yMin; }
        if (g_bbox.xMax > bbox.xMax) { bbox.xMax = g_bbox.xMax; }
        if (g_bbox.yMax > bbox.yMax) { bbox.yMax = g_bbox.yMax; }
    }

    rect_.set(
         (ftFloor(bbox.xMin) >> 6),
        -(ftFloor(bbox.yMax) >> 6),
         (ftFloor(bbox.xMax) >> 6),
        -(ftFloor(bbox.yMin) >> 6));

    if (font_.outlineSize() > 0)
    {
        rect_.x0 -= font_.outlineSize();
        rect_.y0 -= font_.outlineSize();
        rect_.x1 += font_.outlineSize();
        rect_.y1 += font_.outlineSize();
    }
}

void TextRender::resetCache()
{
    for (auto glyph: glyphs_)
    {
        FT_Done_Glyph(glyph);
    }
    glyphs_.resize(0);
    rect_.reset();
}

} // namespace bmce

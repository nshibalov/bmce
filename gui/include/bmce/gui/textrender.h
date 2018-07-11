#ifndef BMCE_GUI_TEXTRENDER_H
#define BMCE_GUI_TEXTRENDER_H


#include <map>
#include <string>
#include <vector>

#include <ft2build.h>

#include FT_FREETYPE_H
#include FT_BBOX_H
#include FT_CACHE_H
#include FT_GLYPH_H
#include FT_LCD_FILTER_H
#include FT_STROKER_H

#include "core/pos2d.h"
#include "core/rect.h"
#include "core/texture.h"

#include "gui/faceid.h"
#include "gui/font.h"
#include "gui/textconstraints.h"
#include "gui/ustring.h"


namespace bmce
{

class TextRender
{
private:
    FT_Library library_ = nullptr;
    FTC_Manager manager_ = nullptr;
    FTC_ImageCache image_cache_ = nullptr;

    std::map<std::string, FaceId> faces_;

    size_t hdpi_ = 120;
    size_t vdpi_ = 120;

    Pos2d<int> pos_;
    Font font_;
    TextConstraints constraints_;

    size_t sel_begin_ = 0;
    size_t sel_end_ = 0;
    bool use_selection_ = false;

    // CACHE
    bool dirty_ = false;
    UString text_;
    std::vector<FT_Glyph> glyphs_;
    Rect<int> rect_;

public:
    TextRender();
    explicit TextRender(size_t dpi);
    TextRender(size_t hdpi, size_t vdpi);
    virtual ~TextRender();

    size_t hDPI() const;
    size_t vDPI() const;

    const Pos2d<int>& pos() const;
    void setPos(const Pos2d<int>& pos);
    void setPos(int x, int y);

    const Font& font() const;
    void setFont(const Font& font);

    const TextConstraints& constraints() const;
    void setConstraints(const TextConstraints& constraints);

    void select(size_t begin, size_t end);
    void deselect();

    FaceId* faceId(const std::string& name);

    void addFace(const std::string& file_name);
    void addFace(const std::string& name, const std::string& file_name);
    void addFace(
        const std::string& name,
        const FaceId::Byte* data,
        FaceId::Size data_size);

    void delFace(const std::string& name);

    const UString& text() const;

    void setText(const std::string& text);

    Rect<int> rect();
    void render(Texture* texture);

private:
    TextRender(const TextRender& copy);
    TextRender& operator=(const TextRender& copy);

    void init();
    void release();

    void validate();
    void genGlyphs();
    void calcRect();
    void resetCache();
};

} // namespace bmce


#endif

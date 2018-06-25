#ifndef BMCE_GUI_GUI_H
#define BMCE_GUI_GUI_H


#include "core/camera.h"
#include "core/log/loggable.h"
#include "core/pos2d.h"
#include "core/rect.h"
#include "core/texture.h"

#include "gui/font.h"
#include "gui/textconstraints.h"
#include "gui/textrender.h"


namespace bmce
{

class Gui : public Loggable
{
private:
    Rect<int> rect_;
    Pos2d<int> cursor_pos_;

    Font font_;
    TextConstraints text_constraints_;
    TextRender text_render_;

    Camera camera_;
    Texture texture_;

public:
    explicit Gui(int width, int height) :
        font_("Arial", 12)
    {
        text_constraints_.setWidth(100);

        text_render_.addFace(font_.name(), "data/fonts/arial.ttf");
        text_render_.setFont(font_);
        text_render_.setConstraints(text_constraints_);
        text_render_.setText("VAвцфцфа: dawdwdвфввияяяЁ\nVersion");

        camera_.setOrthographic(-1, 1, -1, 1);
        resize(width, height);
    }

    const Camera& camera() const
    {
        return camera_;
    }

    const Texture& texture() const
    {
        return texture_;
    }

    void resize(int width, int height)
    {
        rect_.set(0, 0, width, height);
        texture_.resize(width, height);
    }

    void setCursor(int x, int y)
    {
        cursor_pos_.x = x;
        cursor_pos_.y = y;
    }

    virtual void update()
    {
        static bool flag = true;
        static float angle = 0.0;

        if (flag)
        {
            texture_.fill(bmce::RGBA8(36, 45, 47, 34));
            text_render_.setPos(9, 18);
            //text.setOutlineSize(1);
            font_.setColor(bmce::RGBA8(90, 245, 199));
            flag = false;
        }

        //texture_.fill(bmce::RGBA8(0, 0, 0, 0), text_render_.rect());
        texture_.fill(bmce::RGBA8(0, 0, 0, 0));

        font_.setRotation(angle);
        font_.setOutlineSize(1);
        font_.setColor(bmce::RGBA8(90, 245, 199));

        text_render_.setFont(font_);
        text_render_.deselect();
        text_render_.render(&texture_);

        font_.setOutlineSize(1);
        font_.setColor(bmce::RGBA8(0, 255, 0));

        text_render_.setFont(font_);
        text_render_.select(4, 8);
        text_render_.render(&texture_);

        angle += 0.1;
    }
};

} // namespace bmce


#endif

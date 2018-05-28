#include "core/gl/gltexture.h"
#include "core/texture.h"

#include <climits>


namespace bmce
{

GLTexture::GLTexture() :
    id_(0)
{}

GLTexture::~GLTexture()
{ release(); }

void GLTexture::bind(size_t unit)
{
    static const size_t maxUnits = 16;
    static GLuint activeIds[maxUnits] = { UINT_MAX };
    static size_t activeUnit = maxUnits + 1;

    if (unit >= maxUnits)
    {
        return;
    }

    if (activeUnit != unit)
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        activeUnit = unit;
    }

    if (activeIds[unit] != id_)
    {
        glBindTexture(GL_TEXTURE_2D, id_);
        activeIds[unit] = id_;
    }
}

void GLTexture::init(const Texture& texture)
{
    release();
    glGenTextures(1, &id_);
    set(texture);
}

void GLTexture::release()
{
    if (id_ > 0)
    {
        glDeleteTextures(1, &id_);
        id_ = 0;
    }
}

void GLTexture::set(const Texture& texture)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        texture.width(),
        texture.height(),
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        &texture.data()[0]
    );
}

void GLTexture::sub(const Texture& texture, int x, int y)
{
    bind();
    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        x,
        y,
        texture.width(),
        texture.height(),
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        &texture.data()[0]
    );
}

} // namespace bmce

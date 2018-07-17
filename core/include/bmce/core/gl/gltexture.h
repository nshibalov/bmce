#ifndef BMCE_CORE_GL_GLTEXTURE_H
#define BMCE_CORE_GL_GLTEXTURE_H


#include "core/gl/gl.h"


namespace bmce
{

class Texture;

class GLTexture
{
private:
    GLuint id_;

private:
    GLTexture(const GLTexture& o);
    GLTexture& operator=(const GLTexture& rhs);

public:
    GLTexture();
    ~GLTexture();

    void bind(size_t unit=0);

    void init(const Texture& texture);
    void release();

    void set(const Texture& texture);
    void sub(const Texture& texture, int x, int y);
};

} // namespace bmce


#endif

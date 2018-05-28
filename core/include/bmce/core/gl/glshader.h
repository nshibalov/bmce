#ifndef BMCE_CORE_GL_GLSHADER_H
#define BMCE_CORE_GL_GLSHADER_H


#include <map>
#include <string>

#include "core/gl/gl.h"
#include "core/log/loggable.h"
#include "core/mathlib.h"


namespace bmce
{

class GLShader : public Loggable
{
public:
    enum Attrib
    {
        VERTEX = 0,
        NORMAL = 1,
        TEXTURE = 2,
        COLOR = 3
    };

private:
    GLuint id_;
    GLuint projection_matrix_id_;
    GLuint model_view_matrix_id_;

private:
    GLShader(const GLShader& copy);
    GLShader& operator=(const GLShader& right);

public:
    GLShader();
    ~GLShader();

    void bind();

    void init(const std::string& vsfile, const std::string& fsfile);
    void release();
    GLuint getShaderProgramId() const;

    GLint getAttribId(const std::string& attrib) const;
    GLint getUniformId(const std::string& uniform) const;

    void setUniform(GLuint uniform_id, GLint value) const;
    void setUniform(GLuint uniform_id, const Mat4& matrix) const;
    void setProjectionMatrix(const Mat4& matrix) const;
    void setModelViewMatrix(const Mat4& matrix) const;

private:
    GLuint compileShader(GLenum type, const std::string& fname) const;
    bool checkShader(GLuint shader_id) const;
    bool checkProgram(GLuint program_id) const;
};

} // namespace bmce


#endif

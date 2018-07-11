#include "core/gl/glshader.h"
#include "core/log/log.h"
#include "core/utils.h"

#include <iostream>
#include <string>


#define SHADER_ATTRIB_POSITION_STR "position"
#define SHADER_ATTRIB_NORMAL_STR "normal"
#define SHADER_ATTRIB_TEXTURE_STR "uv_coord"
#define SHADER_ATTRIB_COLOR_STR "color"

#define SHADER_PROJECTION_MATRIX_STR "projectionMatrix"
#define SHADER_MODEL_VIEW_MATRIX_STR "modelViewMatrix"


namespace bmce
{

GLShader::GLShader() :
    id_(0),
    projection_matrix_id_(-1),
    model_view_matrix_id_(-1)
{}

GLShader::~GLShader()
{ release(); }

void GLShader::bind()
{
    static GLuint active = 0;
    if (active != id_)
    {
        glUseProgram(id_);
        active = id_;
    }
}

void GLShader::init(const std::string& vsfile, const std::string& fsfile)
{
    release();

    GLuint vsid = compileShader(GL_VERTEX_SHADER, vsfile);
    GLuint fsid = compileShader(GL_FRAGMENT_SHADER, fsfile);

    if (vsid == 0 && fsid == 0)
    {
        return;
    }

    id_ = glCreateProgram();

    if (vsid > 0) { glAttachShader(id_, vsid); }
    if (fsid > 0) { glAttachShader(id_, fsid); }

    glBindAttribLocation(id_, GLShader::VERTEX, SHADER_ATTRIB_POSITION_STR);
    glBindAttribLocation(id_, GLShader::NORMAL, SHADER_ATTRIB_NORMAL_STR);
    glBindAttribLocation(id_, GLShader::TEXTURE, SHADER_ATTRIB_TEXTURE_STR);
    glBindAttribLocation(id_, GLShader::COLOR, SHADER_ATTRIB_COLOR_STR);

    glLinkProgram(id_);
    glValidateProgram(id_);

    if (vsid > 0)
    {
        glDetachShader(id_, vsid);
        glDeleteShader(vsid);
    }

    if (fsid > 0)
    {
        glDetachShader(id_, fsid);
        glDeleteShader(fsid);
    }

    if (!checkProgram(id_))
    {
        release();
        return;
    }

    bind();
    projection_matrix_id_ = getUniformId(SHADER_PROJECTION_MATRIX_STR);
    model_view_matrix_id_ = getUniformId(SHADER_MODEL_VIEW_MATRIX_STR);
}

void GLShader::release()
{
    projection_matrix_id_ = -1;
    model_view_matrix_id_ = -1;

    if (id_ > 0)
    {
        glDeleteProgram(id_);
        id_ = 0;
    }
}

GLuint GLShader::getShaderProgramId() const
{ return id_; }

GLint GLShader::getAttribId(const std::string& attrib) const
{
    static std::map<std::string, GLint> attributes;
    if (attributes.find(attrib) == attributes.end())
    {
        attributes[attrib] = glGetAttribLocation(id_, attrib.c_str());

    }
    return attributes[attrib];
}

GLint GLShader::getUniformId(const std::string& uniform) const
{
    static std::map<std::string, GLint> uniforms;
    if (uniforms.find(uniform) == uniforms.end())
    {
        uniforms[uniform] = glGetUniformLocation(id_, uniform.c_str());

    }
    return uniforms[uniform];
}

void GLShader::setUniform(GLuint uniform_id, GLint value) const
{
    glUniform1i(uniform_id, value);
}

void GLShader::setUniform(GLuint uniform_id, const Mat4& matrix) const
{
    glUniformMatrix4fv(uniform_id, 1, GL_FALSE, &matrix.m[0][0]);
}

void GLShader::setProjectionMatrix(const Mat4& matrix) const
{
    setUniform(projection_matrix_id_, matrix);
}

void GLShader::setModelViewMatrix(const Mat4& matrix) const
{
    setUniform(model_view_matrix_id_, matrix);
}

GLuint GLShader::compileShader(GLenum type, const std::string& fname) const
{
    if (fname.empty())
    {
        return 0;
    }

    std::string data = ReadFileToString(fname);
    const char* p = data.c_str();

    GLuint sid = glCreateShader(type);
    glShaderSource(sid, 1, &p, nullptr);
    glCompileShader(sid);

    if (!checkShader(sid))
    {
        glDeleteShader(sid);
        return 0;
    }

    return sid;
}

bool GLShader::checkShader(GLuint shader_id) const
{
    GLint status = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        GLsizei length = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        std::string buffer;
        buffer.resize(length > 0 ? length - 1 : 0);
        glGetShaderInfoLog(shader_id, length, nullptr, &buffer[0]);
        BMCE_ERROR("Shader (id=" << shader_id << "): " << buffer)
        return false;
    }
    return true;
}

bool GLShader::checkProgram(GLuint program_id) const
{
    GLint link_status = 0, validate_status = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
    glGetProgramiv(program_id, GL_VALIDATE_STATUS, &validate_status);
    if (link_status != GL_TRUE || validate_status != GL_TRUE)
    {
        GLsizei length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);
        std::string buffer;
        buffer.resize(length > 0 ? length - 1 : 0);
        glGetProgramInfoLog(program_id, length, nullptr, &buffer[0]);
        BMCE_ERROR("Program (id=" << program_id << "): " << buffer)
        return false;
    }
    return true;
}

} // namespace bmce

#include "core/gl/glmesh.h"
#include "core/gl/glshader.h"
#include "core/mesh.h"


#define GLOFFSET(ST, EL) (reinterpret_cast<GLvoid*>(offsetof(ST, EL)))


namespace bmce
{

GLMesh::GLMesh() :
    vaoId_(-1),
    vboId_(-1),
    indId_(-1),
    indCount_(0)
{
}

GLMesh::GLMesh(const Mesh& mesh) :
    vaoId_(-1),
    vboId_(-1),
    indId_(-1),
    indCount_(0)
{
    init(mesh);
}

GLMesh::~GLMesh()
{
    release();
}

void GLMesh::bind() const
{
    static GLuint active = 0;
    if (active != vaoId_)
    {
        glBindVertexArray(vaoId_);
        active = vaoId_;
    }
}

void GLMesh::init(const Mesh& mesh)
{
    release();

    indCount_ = mesh.indicies().size();

    // Generate GLMesh
    glGenVertexArrays(1, &vaoId_);
    glBindVertexArray(vaoId_);

    // Generate VBO
    glGenBuffers(1, &vboId_);
    glBindBuffer(GL_ARRAY_BUFFER, vboId_);
    glBufferData(GL_ARRAY_BUFFER, mesh.verticies().size() * sizeof(Vertex), &mesh.verticies()[0], GL_STATIC_DRAW);

    // Generate Indicies
    glGenBuffers(1, &indId_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indId_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indicies().size() * sizeof(GLuint), &mesh.indicies()[0], GL_STATIC_DRAW);

    // Set vertex attribs
    glEnableVertexAttribArray(GLShader::VERTEX);
    glVertexAttribPointer(GLShader::VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), GLOFFSET(Vertex, position));

    glEnableVertexAttribArray(GLShader::NORMAL);
    glVertexAttribPointer(GLShader::NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), GLOFFSET(Vertex, normal));

    glEnableVertexAttribArray(GLShader::TEXTURE);
    glVertexAttribPointer(GLShader::TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), GLOFFSET(Vertex, texture));

    glEnableVertexAttribArray(GLShader::COLOR);
    glVertexAttribPointer(GLShader::COLOR, 3, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), GLOFFSET(Vertex, color));

}

void GLMesh::release()
{
    if (vaoId_ != 0)
    {
        glDeleteVertexArrays(1, &vaoId_);
        vaoId_ = 0;
    }

    if (vboId_ != 0)
    {
        glDeleteBuffers(1, &vboId_);
        vboId_ = 0;
    }

    if (indId_ != 0)
    {
        glDeleteBuffers(1, &indId_);
        indId_ = 0;
    }

    indCount_ = 0;
}

void GLMesh::draw() const
{
    bind();
    glDrawElements(GL_TRIANGLES, indCount_, GL_UNSIGNED_INT, nullptr);
}

} // namespace bmce

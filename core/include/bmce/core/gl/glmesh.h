#ifndef BMCE_CORE_GL_GLMESH_H
#define BMCE_CORE_GL_GLMESH_H


#include "core/gl/gl.h"


namespace bmce
{

class Mesh;

class GLMesh
{
private:
    GLuint vaoId_;
    GLuint vboId_;
    GLuint indId_;

    size_t indCount_;

public:
    GLMesh();
    GLMesh(const Mesh& mesh);
    ~GLMesh();

    void bind() const;
    void init(const Mesh& mesh);
    void release();

    void draw() const;
};

} // namespace bmce


#endif

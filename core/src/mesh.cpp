#include "core/mesh.h"

#include <iostream>


namespace bmce
{

Mesh::Verticies& Mesh::verticies()
{
    return verticies_;
}

const Mesh::Verticies& Mesh::verticies() const
{
    return verticies_;
}

Mesh::Indicies& Mesh::indicies()
{
    return indicies_;
}

const Mesh::Indicies& Mesh::indicies() const
{
    return indicies_;
}

void Mesh::setVerticies(Vertex* verticies, size_t len)
{
    verticies_.resize(len);
    memcpy(&verticies_[0], verticies, sizeof(Vertex) * len);
}

void Mesh::setIndicies(Mesh::Index* indicies, size_t len)
{
    indicies_.resize(len);
    memcpy(&indicies_[0], indicies, sizeof(Mesh::Index) * len);
}

void Mesh::clear()
{
    verticies_.clear();
    indicies_.clear();
}

Mesh Mesh::FromRect(const Rect<FPType>& rect, FPType z)
{
    Mesh mesh;

    Vertex verticies[] = {
        {{rect.x0, rect.y1, z}, {0, 0, 1}, {0, 0}, RGB8(1, 1, 0)},
        {{rect.x1, rect.y1, z}, {0, 0, 1}, {1, 0}, RGB8(0, 1, 1)},
        {{rect.x0, rect.y0, z}, {0, 0, 1}, {0, 1}, RGB8(1, 0, 1)},
        {{rect.x1, rect.y0, z}, {0, 0, 1}, {1, 1}, RGB8(0, 1, 1)}
    };

    Index indicies[] = {0, 2, 1, 2, 3, 1};

    mesh.setVerticies(verticies, sizeof(verticies) / sizeof(Vertex));
    mesh.setIndicies(indicies, sizeof(indicies) / sizeof(Index));

    return mesh;
}

} // namespace bmce

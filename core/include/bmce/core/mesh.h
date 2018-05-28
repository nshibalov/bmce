#ifndef BMCE_CORE_MESH_H
#define BMCE_CORE_MESH_H


#include <vector>

#include "core/rect.h"
#include "core/colortypes.h"
#include "core/mathlib.h"


namespace bmce
{

struct Position
{
    FPType x, y, z;
};

struct UVCoord
{
    FPType u, v;
};

struct Vertex
{
    Position position = {0, 0, 0};
    Position normal = {0, 0, 0};
    UVCoord texture = {0, 0};
    RGB8 color;
};

class Mesh
{
public:
    using Index = unsigned int;
    using Verticies = std::vector<Vertex>;
    using Indicies = std::vector<Index>;

private:
    Verticies verticies_;
    Indicies indicies_;

public:
    Verticies& verticies();
    const Verticies& verticies() const;

    Indicies& indicies();
    const Indicies& indicies() const;

    void setVerticies(Vertex* verticies, size_t len);
    void setIndicies(Index* indicies, size_t len);

    void clear();

    static Mesh FromRect(const Rect<FPType>& rect, FPType z);
};

} // namespace bmce


#endif

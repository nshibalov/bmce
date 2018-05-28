#ifndef BMCE_CORE_FILEIMPORT_H
#define BMCE_CORE_FILEIMPORT_H


#include <string>
#include <vector>

#include "core/mesh.h"


namespace bmce
{

std::vector<Mesh> ImportStaticMesh(const std::string& fname);

} // namespace bmce


#endif

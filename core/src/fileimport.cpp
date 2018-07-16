#include "core/fileimport.h"


#include <iostream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#pragma GCC diagnostic pop


namespace bmce
{

std::vector<Mesh> ImportStaticMesh(const std::string& fname)
{
    std::vector<Mesh> meshes;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        fname,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    if(scene == nullptr)
    {
        std::cout << importer.GetErrorString();
        return meshes;
    }

    meshes.reserve(scene->mNumMeshes);
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
    {
        const aiMesh* pMesh = scene->mMeshes[i];

        Mesh mesh;
        mesh.indicies().resize(pMesh->mNumFaces * 3);
        for (unsigned int j = 0; j < pMesh->mNumFaces; ++j)
        {
            aiFace* pFace = &(pMesh->mFaces[j]);
            assert(pFace->mNumIndices == 3);
            memcpy(
                &mesh.indicies()[j * 3],
                pFace->mIndices,
                sizeof(unsigned int) * 3);
        }

        mesh.verticies().reserve(pMesh->mNumVertices);
        for (unsigned int j = 0; j < pMesh->mNumVertices; ++j)
        {
            aiVector3D* pPos = &(pMesh->mVertices[j]);
            aiVector3D* pNorm = &(pMesh->mNormals[j]);
            Vertex v = {
                {pPos->x, pPos->y, pPos->z},
                {pNorm->x, pNorm->y, pNorm->z},
                {0, 0},
                RGB8(1, 1, 1)
            };
            mesh.verticies().push_back(v);
        }
        meshes.push_back(mesh);
    }

    return meshes;
}

} // namespace bmce

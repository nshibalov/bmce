#ifndef BMCE_CORE_SCENE_H
#define BMCE_CORE_SCENE_H


namespace bmce
{


class Scene
{
public:
    Scene() = default;
    Scene(Scene&& o) = default;
    Scene(const Scene& o) = default;
    virtual ~Scene() = default;

    Scene& operator=(Scene&& o) = default;
    Scene& operator=(const Scene& o) = default;
};


}  // namespace bmce


#endif

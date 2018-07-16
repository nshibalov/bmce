#ifndef BMCE_CORE_SCENE_H
#define BMCE_CORE_SCENE_H


namespace bmce
{

class Scene;


class Scene
{
public:
    Scene() = default;
    Scene(Scene&& from) = default;
    Scene(const Scene& copy) = default;
    virtual ~Scene() = default;

    Scene& operator=(Scene&& from) = default;
    Scene& operator=(const Scene& copy) = default;
};

}  // namespace bmce


#endif

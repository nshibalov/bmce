#ifndef BMCE_CORE_SCENE_H
#define BMCE_CORE_SCENE_H


#include "core/log/log.h"
#include "core/renderer.h"


namespace bmce
{


class Scene
{
private:
    bool active_{false};

public:
    Scene() = default;
    Scene(Scene&& o) = default;
    Scene(const Scene& o) = default;
    virtual ~Scene() = default;

    Scene& operator=(Scene&& o) = default;
    Scene& operator=(const Scene& o) = default;

    bool isActive()
    {
        return active_;
    }

    void setActive(bool is_active)
    {
        active_ = is_active;
    }

    void activate()
    {
        setActive(true);
    }

    void deactivate()
    {
        setActive(false);
    }

    virtual void update(int ms)
    {
    }

    virtual void partialUpdate(int full_frame_ms, int ms)
    {
    }
};


}  // namespace bmce


#endif

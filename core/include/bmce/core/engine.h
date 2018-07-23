#ifndef BMCE_CORE_ENGINE_H
#define BMCE_CORE_ENGINE_H


#include <map>
#include <memory>
#include <vector>

#include "core/keyboard.h"
#include "core/mouse.h"
#include "core/object.h"
#include "core/renderer.h"
#include "core/scene.h"
#include "core/signal.h"
#include "core/threadcontext.h"


namespace bmce
{


class Engine : public ThreadContext, public Object
{
public:
    using ScenePriorities = std::map<Scene*, int>;
    using SceneList = std::vector<Scene*>;

public:
    Signal<> started;
    Signal<> stopped;

    Signal<unsigned int> key_down;
    Signal<unsigned int> key_up;
    Signal<int, int> cursor_moved;
    Signal<int, int> window_resized;

    enum
    {
        UPDATE_INTERVAL_MS = 10
    };

private:
    Keyboard keyboard_;
    Mouse mouse_;

    Renderer* renderer_;
    bool stopped_{false};

    ScenePriorities scenes_;
    SceneList sorted_scenes_;

public:
    Engine();

    Engine(Engine&& o) = delete;
    Engine& operator=(Engine&& rhs) = delete;

    Engine(const Engine& o) = delete;
    Engine& operator=(const Engine& rhs) = delete;

    ~Engine() override = default;

    Keyboard& keyboard();
    const Keyboard& keyboard() const;

    Mouse& mouse();
    const Mouse& mouse() const;

    Renderer* renderer();
    void setRenderer(Renderer* renderer);

    void run() override;
    void stop();

    void addScene(Scene* scene);
    void addScene(Scene* scene, int priority);
    void removeScene(Scene* scene);

private:
    void init();
    void destroy();
    void loop();

    void updateSortedScenes();
    void update();
    void partialUpdate(int ms);
    void render();
};


} // namespace bmce


#endif

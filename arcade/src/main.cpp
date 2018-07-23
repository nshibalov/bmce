#include "core/engine.h"
#include "core/errors/commonerror.h"
#include "core/gl/glrenderer.h"
#include "core/log/consolelogger.h"
#include "core/log/log.h"
#include "core/scene.h"


using bmce::CommonError;
using bmce::Engine;
using bmce::Log;
using bmce::ConsoleLogger;
using bmce::GLRenderer;
using bmce::Scene;


class Arcade : public Scene
{
public:
    void update(int ms) override
    {
        //BMCE_INFO("update: full frame: " << ms)
    }

    void partialUpdate(int full_frame_ms, int ms) override
    {
        //BMCE_INFO("update: " << float(ms) / full_frame_ms << " frame")
    }
};


int main(int /*argc*/, char** /*argv*/)
{
    try
    {
        static ConsoleLogger logger;
        Log::setLogger(&logger);

        Engine engine;

        GLRenderer renderer("Arcade", 640, 480);

        Arcade arcade;

        engine.keyboard().key_up.connect<Arcade>(&Arcade::activate, &arcade);

        engine.setRenderer(&renderer);
        engine.addScene(&arcade);
        engine.run();
    }
    catch (const CommonError& error)
    {
        BMCE_ERROR(error.message());
    }

    return 0;
}

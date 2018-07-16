#include "core/engine.h"
#include "core/errors/commonerror.h"
#include "core/gl/glrenderer.h"
#include "core/log/consolelogger.h"
#include "core/log/log.h"


using bmce::CommonError;
using bmce::Engine;
using bmce::Log;
using bmce::ConsoleLogger;
using bmce::GLRenderer;


class Test
{
private:
    std::string str_;
public:
    explicit Test(std::string str) : str_(std::move(str)) {}
};


int main(int /*argc*/, char** /*argv*/)
{
    try
    {
        static ConsoleLogger logger;
        Log::setLogger(&logger);

        Engine engine;
        engine.setRenderer(std::make_unique<GLRenderer>("Arcade", 640, 480));
        engine.run();
    }
    catch (const CommonError& error)
    {
        BMCE_ERROR(error.message());
    }

    return 0;
}

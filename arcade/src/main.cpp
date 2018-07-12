#include "core/engine.h"
#include "core/log/log.h"
#include "core/log/consolelogger.h"


using bmce::Engine;
using bmce::Log;
using bmce::ConsoleLogger;


int main(int /*argc*/, char** /*argv*/)
{
    static bmce::ConsoleLogger logger;

    bmce::Log::setLogger(&logger);

    Engine engine;
    engine.run();

    return 0;
}

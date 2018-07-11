#include "core/engine.h"
#include "core/log/log.h"
#include "core/log/consolelogger.h"


using bmce::Engine;
using bmce::Log;
using bmce::ConsoleLogger;


int main(int /*argc*/, char** /*argv*/)
{
    bmce::ConsoleLogger logger;
    bmce::Log::setLogger(&logger);

    Engine engine;
    engine.run();

    bmce::Log::setLogger(nullptr);
    return 0;
}

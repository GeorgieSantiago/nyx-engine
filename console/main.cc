#include "engine/nyx.h"

int main() {
    Nyx* engine = &Nyx();
    if (engine->startup() == 0) {
        engine->logger->log_message("Failed to startup");
    }

    engine->run();

    if (engine->shutdown() == 0) {
        engine->logger->log_message("Failed to shutdown smoothly");
    }

    return 0;
}
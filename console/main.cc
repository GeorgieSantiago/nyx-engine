#include "engine/nyx.h"
#include "engine/example/vulkan_init.h"

int main() {
    Nyx* engine = &Nyx();
    if (engine->startup() == 0) {
        engine->logger->log_message("Failed to startup");
        //Throw error
    }

    engine->run();

    if (engine->shutdown() == 0) {
        engine->logger->log_message("Failed to shutdown smoothly");
    }

    return 0;
}
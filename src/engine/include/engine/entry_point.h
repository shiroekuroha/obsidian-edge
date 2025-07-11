#pragma once

#include "engine/core/application/application.h"

extern ObsidianEdge::Application *
ObsidianEdge::createApplication();

int main(int argc, char **argv) {
    ObsidianEdge::Logger::init();

    auto app = ObsidianEdge::createApplication();
    app->run();
    delete app;
}

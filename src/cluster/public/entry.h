#pragma once

#include "external.h"

extern auto ObsidianEdge::createApplication() -> ObsidianEdge::Application *;

auto main(int argc, char **argv) -> int {
    ObsidianEdge::Log::init();
    std::unique_ptr<ObsidianEdge::Application> app(ObsidianEdge::createApplication());
    app->run();
}

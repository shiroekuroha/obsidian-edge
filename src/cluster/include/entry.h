#pragma once

#include "application/application.h"
#include "core/log/log.h"

extern auto ObsidianEdge::createApplication() -> ObsidianEdge::Application*;

/**
 * @brief Entry point of client program, do not include this file alone
 *
 * @param argc
 * @param argv
 * @return int
 */
auto main(int argc, char** argv) -> int {
    // * Start log system
    ObsidianEdge::Log::init();

    // * Create app, this app belongs to client
    std::unique_ptr<ObsidianEdge::Application> app(ObsidianEdge::createApplication());

    // * Run app's routine
    app->run();
}

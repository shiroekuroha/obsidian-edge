#pragma once

#include "engine/core/application/application.h"
#include <memory>

extern ObsidianEdge::Application *ObsidianEdge::createApplication ();

int
main (int argc, char **argv)
{
    ObsidianEdge::Logger::init ();

    std::shared_ptr<ObsidianEdge::Application> app
        = std::shared_ptr<ObsidianEdge::Application> (
            ObsidianEdge::createApplication ());

    app->init (argc, argv);
    app->run ();
}

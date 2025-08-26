#pragma once

#include "engine/obsidian_edge.h"

extern ObsidianEdge::Application *ObsidianEdge::createApplication ();

int
main (int argc, char **argv)
{
    ObsidianEdge::Logger::init ();
    ObsidianEdge::Application* app = ObsidianEdge::createApplication ();
    app->run ();
    delete app;
}

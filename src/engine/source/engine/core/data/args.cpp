#include "engine/core/data/args.h"

namespace ObsidianEdge
{
ArgsContainer::ArgsContainer (int argc, char **argv) { set (argc, argv); }

void
ArgsContainer::set (int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
        {

            std::string target = argv[i];
            int sepIndex = target.find ('=');

            if (sepIndex == std::string::npos)
                {
                    m_args[target] = "";
                }
            else
                {
                    std::string key = target.substr (0, sepIndex);
                    std::string value = target.substr (
                        sepIndex + 1, target.length () - key.length () - 1);

                    m_args[key] = value;
                }
        }
}

bool
ArgsContainer::has (const char *arg) const
{
    return m_args.find (std::string (arg)) != m_args.end ();
}

std::string &
ArgsContainer::operator[] (const char *arg)
{
    return m_args.at (std::string (arg));
}
}
#pragma once

#include <string>
#include <unordered_map>

namespace ObsidianEdge
{
class ArgsContainer
{
  public:
    ArgsContainer () = default;
    ArgsContainer (int argc, char **argv);

    void set (int argc, char **argv);
    bool has (const char *arg) const;

    std::string &operator[] (const char *arg);

  private:
    std::unordered_map<std::string, std::string> m_args;
};
}
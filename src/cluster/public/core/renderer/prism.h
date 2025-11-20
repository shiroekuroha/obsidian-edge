#pragma once

namespace ObsidianEdge {
class Prism {
public:
    Prism();
    ~Prism();

    Prism(const Prism &other);
    Prism(Prism &&other) noexcept;

    auto operator=(const Prism &other) -> Prism &;
    auto operator=(Prism &&other) noexcept -> Prism &;

private:
};
} // namespace ObsidianEdge

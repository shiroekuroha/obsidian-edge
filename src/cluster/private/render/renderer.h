#pragma once

namespace ObsidianEdge {
struct Vertex {};

class RenderObject {
public:
    RenderObject();
    virtual ~RenderObject();

    RenderObject(const RenderObject &other);
    RenderObject(RenderObject &&other) noexcept;

    auto operator=(const RenderObject &other) -> RenderObject &;
    auto operator=(RenderObject &&other) noexcept -> RenderObject &;

    virtual void setData();

private:
};

class Renderer {
public:
    Renderer();
    virtual ~Renderer();

    Renderer(const Renderer &other);
    Renderer(Renderer &&other) noexcept;

    auto operator=(const Renderer &other) -> Renderer &;
    auto operator=(Renderer &&other) noexcept -> Renderer &;

private:
};
} // namespace ObsidianEdge

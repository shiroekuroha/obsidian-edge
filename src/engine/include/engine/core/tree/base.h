#pragma once

#include <memory>
#include <vector>

namespace ObsidianEdge
{
class Base
{
  public:
    Base ();
    Base (const char *name);
    virtual ~Base () = default;

    Base &getParent () const;
    const std::vector<std::shared_ptr<Base>> &getChildren () const;

    void setParent (Base *parent);

    void insertChild (Base *child, int index);
    void pushChild (Base *child);
    void removeChild (Base *child);
    void clearChildren ();

    void onAttach ();
    void onDetach ();

    static std::string getObjectClass ();

  protected:
    std::string p_name;

  private:
    std::shared_ptr<Base> m_parent;
    std::vector<std::shared_ptr<Base>> m_children;
};
}
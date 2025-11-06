#ifndef OE_NODE_H
#define OE_NODE_H

#include "obsidian/core/event/event.h"

namespace ObsidianEdge
{
class Node
{
public:
    Node ();
    virtual ~Node ();

    void addChild (Node *node);
    void removeChild (Node *node);

    void setParent (Node *parent);

    Node &getParent ();
    Node *getParentNative () const;

    Node &getChild (unsigned int index);
    Node *getChildNative (unsigned int index) const;

    Vector<Node *>::iterator childrenBegin ();
    Vector<Node *>::iterator childrenEnd ();

    // For children to call when they updated their arrangement
    virtual void treeUpdated ();

    virtual void onAttach () = 0;
    virtual void onDetach () = 0;
    virtual void onUpdate () = 0;
    virtual void onEvent (Event &event) = 0;

private:
    Vector<Node *> m_children = {};
    Node *m_parent = nullptr;
};
}

#endif

#include "obsidian/core/ecs/node.h"

namespace ObsidianEdge
{
Node::Node () {}

Node::~Node () {}

void
Node::addChild (Node *node)
{
    if (node == nullptr)
        return;

    m_children.push_back (node);
    node->setParent (this);
    node->onAttach ();
}

void
Node::removeChild (Node *node)
{
    if (node == nullptr)
        return;

    auto it = std::find (m_children.begin (), m_children.end (), node);

    if (it != m_children.end ())
        {
            (*it)->onDetach ();
            (*it)->setParent (nullptr);
            m_children.erase (it);
        }
}

void
Node::setParent (Node *parent)
{
    m_parent = parent;
}

Node &
Node::getParent ()
{
    return *m_parent;
}

Node *
Node::getParentNative () const
{
    return m_parent;
}

Node &
Node::getChild (unsigned int index)
{
    return *m_children[index];
}

Node *
Node::getChildNative (unsigned int index) const
{
    return m_children[index];
}

Vector<Node *>::iterator
Node::childrenBegin ()
{
    return m_children.begin ();
}

Vector<Node *>::iterator
Node::childrenEnd ()
{
    return m_children.end ();
}

void
Node::treeUpdated ()
{
}

void
Node::onAttach ()
{
}

void
Node::onDetach ()
{
}

void
Node::onUpdate ()
{
}

void
Node::onEvent (Event &event)
{
}
}

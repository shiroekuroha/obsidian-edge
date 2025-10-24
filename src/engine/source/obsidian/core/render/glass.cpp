#include <obsidian/core/data/pch.h>

#include "obsidian/core/render/glass.h"

namespace ObsidianEdge
{
void
Glass::onAttach ()
{
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader.create ("shaders/vertex.glsl", "shaders/fragment.glsl");

    Vector<Rectangle> rects = { { { 10.0f, 10.0f }, { 10.0f, 10.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } } };
    Vector<Rectangle> rects2 = { { { -1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } } };
    Vector<Rectangle> rects3 = { { { 0.0f, -1.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } } };
    createBuffer (rects);
    createBuffer (rects2);
    createBuffer (rects3);

    model = glm::translate (model, glm::vec3 (0.0f, 0.0f, 0.0f));
    model = glm::rotate (model, 0.0f, { 1.0f, 0.0f, 0.0f });
    model = glm::scale (model, glm::vec3 (20.0f, 20.0f, 1.0f));
    view = glm::translate (view, glm::vec3 (0.0f, 0.0f, 0.0f));
    proj = glm::orthoLH (
        // Left, Right
        0.0f, (float)Application::get ().window ().getWidth (),
        // Up, Down
        0.0f, (float)Application::get ().window ().getHeight (),
        // Near, Far
        -1.0f, 1.0f);
}

void
Glass::onDetach ()
{
    std::for_each (vao.begin (), vao.end (), [] (unsigned int &id) { glDeleteVertexArrays (1, &id); });
    glBindVertexArray (0);

    std::for_each (vbo.begin (), vbo.end (),
                   [] (Pair<unsigned int, Vector<Vertex>> &pair) { glDeleteBuffers (1, &pair.first); });
    glBindBuffer (GL_ARRAY_BUFFER, 0);

    std::for_each (ibo.begin (), ibo.end (),
                   [] (Pair<unsigned int, Vector<Index>> &pair) { glDeleteBuffers (1, &pair.first); });
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
}

void
Glass::onUpdate (float delta)
{
    shader.use ();

    glClearColor (0.25f, 0.25f, 0.25f, 0.25f);
    glClear (GL_COLOR_BUFFER_BIT);

    if (currentBuffer < vbo.size () && currentBuffer < ibo.size ())
        {
            Matrix4 mvp = proj * view * model;

            glUniformMatrix4fv (glGetUniformLocation (shader.id (), "g_MVP"), 1, GL_FALSE, &mvp[0][0]);

            drawBuffer (currentBuffer);
        };
}

void
Glass::createBuffer (const Vector<Rectangle> &rects)
{
    Vector<Vertex> vertices;
    Vector<Index> indicies;
    Vector<Texture> textures;

    unsigned int x = 0;
    for (const Rectangle &rect : rects)
        {
            Vector<Vertex> vert = rect.getVertices ();
            Vector<Index> indi = rect.getIndicies ();
            textures.push_back (rect.getTexture ());

            for (Index &i : indi)
                i = x * 4 + i;

            vertices.insert (vertices.end (), vert.begin (), vert.end ());
            indicies.insert (indicies.end (), indi.begin (), indi.end ());
        }

    vao.push_back (0);
    vbo.push_back ({ 0, vertices });
    ibo.push_back ({ 0, indicies });
    m_textures.push_back (textures);

    glGenVertexArrays (1, &vao.back ());
    glBindVertexArray (vao.back ());

    glGenBuffers (1, &vbo.back ().first);
    glBindBuffer (GL_ARRAY_BUFFER, vbo.back ().first);
    glBufferData (GL_ARRAY_BUFFER, sizeof (Vertex) * vbo.back ().second.size (), vbo.back ().second.data (),
                  GL_STATIC_DRAW);

    glGenBuffers (1, &ibo.back ().first);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ibo.back ().first);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (Index) * ibo.back ().second.size (), ibo.back ().second.data (),
                  GL_STATIC_DRAW);

    glVertexAttribPointer (0, 4, GL_FLOAT, 0, sizeof (Vertex), (void *)offsetof (Vertex, position));
    glEnableVertexAttribArray (0);

    glVertexAttribPointer (1, 4, GL_FLOAT, 0, sizeof (Vertex), (void *)offsetof (Vertex, tintColor));
    glEnableVertexAttribArray (1);

    glVertexAttribPointer (2, 2, GL_FLOAT, 0, sizeof (Vertex), (void *)offsetof (Vertex, texCoord));
    glEnableVertexAttribArray (2);

    glBindVertexArray (vao[currentBuffer]);
    glBindBuffer (GL_ARRAY_BUFFER, vbo[currentBuffer].first);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ibo[currentBuffer].first);
}

void
Glass::destroyBuffer (unsigned int bufferIndex)
{
    Pair<unsigned int, Vector<Vertex>> &x_vbo = vbo[bufferIndex];
    Pair<unsigned int, Vector<Index>> &x_ibo = ibo[bufferIndex];

    glDeleteBuffers (1, &x_vbo.first);
    glDeleteBuffers (1, &x_ibo.first);

    vbo.erase (vbo.begin () + bufferIndex);
    ibo.erase (ibo.begin () + bufferIndex);

    m_textures.erase (m_textures.begin () + bufferIndex);

    if (!(currentBuffer < vbo.size () && currentBuffer < vbo.size ()))
        currentBuffer = 0;
}

void
Glass::drawSegment (unsigned int bufferIndex, unsigned int segmentIndex)
{
    m_textures[bufferIndex][segmentIndex].bind ();
    glUniform1i (glGetUniformLocation (shader.id (), "g_Sampler"), 0);

    glBindBuffer (GL_ARRAY_BUFFER, vbo[bufferIndex].first);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ibo[bufferIndex].first);
    glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void *)(segmentIndex * 6));
}

void
Glass::drawBuffer (unsigned int bufferIndex)
{
    glBindVertexArray (vao[bufferIndex]);

    glBindBuffer (GL_ARRAY_BUFFER, vbo[bufferIndex].first);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ibo[bufferIndex].first);

    for (unsigned int i = 0; i < m_textures.size (); i++)
        {
            drawSegment (bufferIndex, i);
        }
}
}

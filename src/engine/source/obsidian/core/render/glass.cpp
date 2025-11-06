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

#ifdef TESTING_BASE
    {
        Vector<Rectangle> rects = { { { 100.0f, 100.0f }, { 200.0f, 200.0f }, { 1.0f, 0.0f, 0.0f, 0.50f } } };
        Vector<Rectangle> rects2 = { { { 200.0f, 0.0f }, { 200.0f, 200.0f }, { 0.0f, 1.0f, 0.0f, 0.5f } } };
        Vector<Rectangle> rects3 = { { { 0.0f, 200.0f }, { 200.0f, 200.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } } };
        Vector<Rectangle> rects4
            = { { { 0.0f, 0.0f }, { 200.0f, 200.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { "textures/toaster.png" } } };
        createBuffer (rects);
        createBuffer (rects2);
        createBuffer (rects3);
        createBuffer (rects4);

        view = glm::translate (view, glm::vec3 (0.0f, 0.0f, 0.0f));
        proj = glm::orthoLH (
            // Left, Right
            0.0f, (float)Application::get ().window ().getWidth (),
            // Up, Down
            0.0f, (float)Application::get ().window ().getHeight (),
            // Near, Far
            -1.0f, 1.0f);

        buffer[0].transform = glm::translate (buffer[0].transform, Vector3 (600.0f, 0.0f, 0.0f));
    }

#endif
}

void
Glass::onDetach ()
{
    std::for_each (vao.begin (), vao.end (), [] (unsigned int &id) { glDeleteVertexArrays (1, &id); });
    glBindVertexArray (0);

    std::for_each (buffer.begin (), buffer.end (),
                   [] (Buffer &buffer)
                       {
                           glDeleteBuffers (1, &buffer.vbo.first);
                           glDeleteBuffers (1, &buffer.ibo.first);
                       });

    glBindBuffer (GL_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
}

void
Glass::onUpdate (float delta)
{
    shader.use ();

    glClearColor (0.25f, 0.25f, 0.25f, 0.25f);
    glClear (GL_COLOR_BUFFER_BIT);

    if (buffer.size ())
        {
            static float offset = 0;

            for (int i = 0; i < buffer.size (); i++)
                {
                    Matrix4 mvp = proj * view * buffer[i].transform;
                    glUniformMatrix4fv (glGetUniformLocation (shader.id (), "g_MVP"), 1, GL_FALSE, &mvp[0][0]);
                    drawBuffer (i);
                }
        }
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

    Buffer tempBuffer = { { 0, vertices }, { 0, indicies } };
    tempBuffer.textures.insert (tempBuffer.textures.end (), textures.begin (), textures.end ());
    buffer.push_back (tempBuffer);

    vao.push_back (0);

    glGenVertexArrays (1, &vao.back ());
    glBindVertexArray (vao.back ());

    glGenBuffers (1, &buffer.back ().vbo.first);
    glBindBuffer (GL_ARRAY_BUFFER, buffer.back ().vbo.first);
    glBufferData (GL_ARRAY_BUFFER, sizeof (Vertex) * buffer.back ().vbo.second.size (), buffer.back ().vbo.second.data (),
                  GL_STATIC_DRAW);

    glGenBuffers (1, &buffer.back ().ibo.first);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, buffer.back ().ibo.first);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (Index) * buffer.back ().ibo.second.size (),
                  buffer.back ().ibo.second.data (), GL_STATIC_DRAW);

    glVertexAttribPointer (0, 4, GL_FLOAT, 0, sizeof (Vertex), (void *)offsetof (Vertex, position));
    glEnableVertexAttribArray (0);

    glVertexAttribPointer (1, 4, GL_FLOAT, 0, sizeof (Vertex), (void *)offsetof (Vertex, tintColor));
    glEnableVertexAttribArray (1);

    glVertexAttribPointer (2, 2, GL_FLOAT, 0, sizeof (Vertex), (void *)offsetof (Vertex, texCoord));
    glEnableVertexAttribArray (2);

    glBindVertexArray (vao.back ());
    glBindBuffer (GL_ARRAY_BUFFER, buffer.back ().vbo.first);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, buffer.back ().ibo.first);
}

void
Glass::destroyBuffer (unsigned int bufferIndex)
{
    Pair<unsigned int, Vector<Vertex>> &x_vbo = buffer[bufferIndex].vbo;
    Pair<unsigned int, Vector<Index>> &x_ibo = buffer[bufferIndex].ibo;

    glDeleteVertexArrays (1, &vao[bufferIndex]);
    glDeleteBuffers (1, &x_vbo.first);
    glDeleteBuffers (1, &x_ibo.first);

    buffer.erase (buffer.begin () + bufferIndex);
}

void
Glass::drawSegment (unsigned int bufferIndex, unsigned int segmentIndex)
{
    buffer[bufferIndex].textures[segmentIndex].bind ();
    glUniform1i (glGetUniformLocation (shader.id (), "g_Sampler"), 0);

    glBindBuffer (GL_ARRAY_BUFFER, buffer[bufferIndex].vbo.first);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, buffer[bufferIndex].ibo.first);
    glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void *)(segmentIndex * 6));
}

void
Glass::drawBuffer (unsigned int bufferIndex)
{
    glBindVertexArray (vao[bufferIndex]);

    glBindBuffer (GL_ARRAY_BUFFER, buffer[bufferIndex].vbo.first);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, buffer[bufferIndex].ibo.first);

    for (unsigned int i = 0; i < buffer.size (); i++)
        {
            drawSegment (bufferIndex, i);
        }
}
}

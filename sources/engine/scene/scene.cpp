#include "scene.hpp"

namespace kusengine
{

void
Scene::create()
{
    float x1 = -0.1, y1 = -0.1;
    float x2 = 0.1, y2 = -0.1;
    float x3 = 0, y3 = 0.1;

    std::vector<UniversalVertex> vertices;
    std::vector<uint32_t> indices;

    uint32_t ind = 0;

    m_mesh_storage.setVertices(MeshType::RECTANGLE, {
                                                        {-1, -1, 0.3, 1,   0.5},
                                                        {1,  -1, 0.1, 1,   0.8},
                                                        {1,  1,  0.6, 0.2, 0.5},
                                                        {-1, 1,  0.3, 0,   1  }
    });
    m_mesh_storage.setIndices(MeshType::RECTANGLE, {ind + 0, ind + 1, ind + 2,
                                                    ind + 2, ind + 3, ind + 0});

    ind += 4;

    for (float x = -1; x <= 1; x += 0.2)
    {
        for (float y = -1; y <= 1; y += 0.3)
        {
            UniversalVertex vertex;
            vertex.setPosition(x1 + x, y1 + y).setColor(0.2, 0.6, 0.0);
            vertices.emplace_back(vertex);
            indices.emplace_back(ind);
            ind++;
            ////////////////////////////////////
            vertex.setPosition(x2 + x, y2 + y).setColor(0.9, 0.1, 0.3);
            vertices.emplace_back(vertex);
            indices.emplace_back(ind);
            ind++;
            ////////////////////////////////////
            vertex.setPosition(x3 + x, y3 + y).setColor(1.0, 0.5, 1.0);
            vertices.emplace_back(vertex);
            indices.emplace_back(ind);
            ind++;
            //////////////////////////////////
        }
    }
    m_mesh_storage.setVertices(MeshType::TRIANGLE, vertices);
    m_mesh_storage.setIndices(MeshType::TRIANGLE, indices);

    ///////////////////////////
    // Rectangle

    m_mesh_storage.fillBuffers();
}

void
Scene::draw(const vk::CommandBuffer& command_buffer) const
{
    m_mesh_storage.draw(command_buffer);
}
}; // namespace kusengine

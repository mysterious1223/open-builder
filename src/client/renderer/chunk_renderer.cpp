#include "chunk_renderer.h"

#include "../world/chunk/chunk_mesh.h"
#include "camera.h"

#include <iostream>

namespace client {
    ChunkRenderer::ChunkRenderer()
        : m_solidBlockShader("chunk")
    {
        m_texture.create("grass.png");
    }

    void ChunkRenderer::process(const ChunkMeshObjects &mesh)
    {

        m_solidChunkRenders.push_back(mesh.solid.getRenderInfo());
    }

    void ChunkRenderer::render(const Camera &camera)
    {
        m_texture.bind();
        // Solid blocks first
        m_solidBlockShader.prepare(camera);
        for (auto &chunk : m_solidChunkRenders) {
            chunk.bindAndDraw();
        }

        m_solidChunkRenders.clear();
    }

    ChunkRenderer::ChunkShader::ChunkShader(const char *programName)
        : program(programName, programName)
    {
        program.use();
        locationCameraMatrix =
            program.getUniformLocation("projectionViewMatrix");
    }

    void ChunkRenderer::ChunkShader::prepare(const Camera &camera)
    {
        program.use();
        loadMatrix4(locationCameraMatrix,
                            camera.getProjectionViewMatrix());
    }
} // namespace client

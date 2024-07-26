#pragma once

#include "core/rendering/VertexBuffer.hpp"

namespace Lypo {
    class OpenGlVertexBuffer : public VertexBuffer {
    public:
        OpenGlVertexBuffer(float *vertices, uint32_t size);

        ~OpenGlVertexBuffer();

        void Bind() const override;

        void Unbind() const override;

    private:
        uint32_t _BufferID;
    };

}
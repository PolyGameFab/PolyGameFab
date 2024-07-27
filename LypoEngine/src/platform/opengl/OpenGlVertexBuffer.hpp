#pragma once

#include "core/rendering/VertexBuffer.hpp"
#include "core/rendering/BufferUtils.h"

namespace Lypo {
    class OpenGlVertexBuffer : public VertexBuffer {
    public:
        OpenGlVertexBuffer(float *vertices, uint32_t size);

        ~OpenGlVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual const BufferLayout& GetLayout() const override { return layout_; }
        virtual void SetLayout(const BufferLayout& layout) override { layout_ = layout; }

    private:
        uint32_t bufferID_;
        BufferLayout layout_;
    };

}
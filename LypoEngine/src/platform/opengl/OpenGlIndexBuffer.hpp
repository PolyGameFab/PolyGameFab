#pragma once

#include "core/rendering/IndexBuffer.hpp"

namespace Lypo {
    class OpenGlIndexBuffer : public IndexBuffer {
    public:
        OpenGlIndexBuffer(uint32_t *indices, uint32_t count);

        ~OpenGlIndexBuffer();

        void bind() const override;

        void unbind() const override;

        virtual uint32_t getCount() const { return count_; }

    private:
        uint32_t bufferID_;
        uint32_t count_;
    };
}
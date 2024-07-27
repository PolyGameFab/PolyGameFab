#pragma once

#include "lypch.h"
#include "core/rendering/VertexArray.hpp"



namespace Lypo {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const { return vertexBuffers_; }
        virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return indexBuffer_; }
    private:
        uint32_t rendererID_;
        std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers_;
        std::shared_ptr<IndexBuffer> indexBuffer_;
    };

}
#pragma once

#include "lypch.h"
#include "core/rendering/VertexArray.hpp"



namespace Lypo {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return vertexBuffers_; }
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return indexBuffer_; }
    private:
        uint32_t _RendererID;
        std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers_;
        std::shared_ptr<IndexBuffer> indexBuffer_;
    };

}
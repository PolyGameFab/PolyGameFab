#include "OpenGlVertexArray.hpp"

#include <glad/glad.h>

namespace Lypo {
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case Lypo::ShaderDataType::Float:
                return GL_FLOAT;
            case Lypo::ShaderDataType::Float2:
                return GL_FLOAT;
            case Lypo::ShaderDataType::Float3:
                return GL_FLOAT;
            case Lypo::ShaderDataType::Float4:
                return GL_FLOAT;
            case Lypo::ShaderDataType::Mat3:
                return GL_FLOAT;
            case Lypo::ShaderDataType::Mat4:
                return GL_FLOAT;
            case Lypo::ShaderDataType::Int:
                return GL_INT;
            case Lypo::ShaderDataType::Int2:
                return GL_INT;
            case Lypo::ShaderDataType::Int3:
                return GL_INT;
            case Lypo::ShaderDataType::Int4:
                return GL_INT;
            case Lypo::ShaderDataType::Bool:
                return GL_BOOL;
        }

        //TODO: log error: Unknown ShaderDataType
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        glCreateVertexArrays(1, &_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &_RendererID);
    }

    void OpenGLVertexArray::Bind() const {
        glBindVertexArray(_RendererID);
    }

    void OpenGLVertexArray::Unbind() const {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) {
        if (vertexBuffer->GetLayout().GetElements().size() == 0) {
            //TODO: log error: VertexBuffer has no layout
        }

        glBindVertexArray(_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto &layout = vertexBuffer->GetLayout();
        for (const auto &element: layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void *) element.Offset);
            index++;
        }
        _VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(_RendererID);
        indexBuffer->Bind();

        _IndexBuffer = indexBuffer;
    }
}
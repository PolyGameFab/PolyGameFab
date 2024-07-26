
#include "OpenGlVertexBuffer.hpp"
#include <glad/glad.h>

namespace Lypo {

    OpenGlVertexBuffer::OpenGlVertexBuffer(float *vertices, uint32_t size) {
        glGenBuffers(1, &_BufferID);
        glBindBuffer(GL_ARRAY_BUFFER, _BufferID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGlVertexBuffer::~OpenGlVertexBuffer() {
        glDeleteBuffers(1, &_BufferID);
    }
    
    void OpenGlVertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, _BufferID);
    }

    void OpenGlVertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}
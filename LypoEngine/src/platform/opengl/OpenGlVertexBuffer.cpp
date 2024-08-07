
#include "OpenGlVertexBuffer.hpp"
#include <glad/glad.h>

namespace Lypo {

    OpenGlVertexBuffer::OpenGlVertexBuffer(float *vertices, uint32_t size) {
        glGenBuffers(1, &bufferID_);
        glBindBuffer(GL_ARRAY_BUFFER, bufferID_);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGlVertexBuffer::~OpenGlVertexBuffer() {
        glDeleteBuffers(1, &bufferID_);
    }
    
    void OpenGlVertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, bufferID_);
    }

    void OpenGlVertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}
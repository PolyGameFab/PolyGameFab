
#include "OpenGlIndexBuffer.hpp"
#include "glad/glad.h"

namespace Lypo {
    OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t *indices, uint32_t count) {
        glGenBuffers(1, &_BufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _BufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
    }

    OpenGlIndexBuffer::~OpenGlIndexBuffer() {
        glDeleteBuffers(1, &_BufferID);
    }

    void OpenGlIndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _BufferID);
    }

    void OpenGlIndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
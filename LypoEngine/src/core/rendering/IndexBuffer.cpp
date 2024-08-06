
#include "Renderer.hpp"
#include "IndexBuffer.hpp"
#include "platform/opengl/OpenGlIndexBuffer.hpp"

namespace Lypo {
    IndexBuffer* IndexBuffer::create(uint32_t * indices, uint32_t count)
    {
        switch (Renderer::getApi())
        {
            case RendererAPI::None:   LYPO_CORE_ERROR("RendererAPI::None is not supported") return nullptr;
            case RendererAPI::OpenGL:  return new OpenGlIndexBuffer(indices, count);
        }

        LYPO_CORE_ERROR("This API is not supported");
        return nullptr;
    }
}

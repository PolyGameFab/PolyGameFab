
#include "Renderer.hpp"
#include "IndexBuffer.hpp"
#include "platform/opengl/OpenGlIndexBuffer.hpp"

namespace Lypo {
    IndexBuffer* IndexBuffer::Create(uint32_t * vertices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:   /*TODO Log ERROR RendererAPI::None is not supported */ return nullptr;
            case RendererAPI::OpenGL:  return new OpenGlIndexBuffer(vertices, count);
        }

        /*TODO Log ERROR:  This API is not supported */
        return nullptr;
    }
}

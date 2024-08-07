
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "platform/opengl/OpenGlVertexBuffer.hpp"

namespace Lypo {
	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::getApi())
		{
            case RendererAPI::None:   LYPO_CORE_ERROR("RendererAPI::None is not supported") return nullptr;
            case RendererAPI::OpenGL:  return new OpenGlVertexBuffer(vertices, size);
		}

        LYPO_CORE_ERROR("This API is not supported");
		return nullptr;
	}
}

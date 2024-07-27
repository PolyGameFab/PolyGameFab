
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "platform/opengl/OpenGLVertexBuffer.hpp"

namespace Lypo {
	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::getApi())
		{
            case RendererAPI::None:   /*TODO Log ERROR RendererAPI::None is not supported */ return nullptr;
            case RendererAPI::OpenGL:  return new OpenGlVertexBuffer(vertices, size);
		}

		/*TODO Log ERROR:  This API is not supported */
		return nullptr;
	}
}

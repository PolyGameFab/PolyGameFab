
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "platform/opengl/OpenGLVertexBuffer.hpp"

namespace Lypo {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
            case RendererAPI::None:   /*TODO Log ERROR RendererAPI::None is not supported */ return nullptr;
            case RendererAPI::OpenGL:  return new OpenGlVertexBuffer(vertices, size);
		}

		/*TODO Log ERROR:  This API is not supported */
		return nullptr;
	}
}

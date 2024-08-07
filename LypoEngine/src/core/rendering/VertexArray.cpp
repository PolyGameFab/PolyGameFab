

#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "platform/opengl/OpenGlVertexArray.hpp"

namespace Lypo {

    VertexArray *VertexArray::create() {
        switch (Renderer::getApi()) {
            case RendererAPI::None:    LYPO_CORE_ERROR("RendererAPI::None is not supported") return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLVertexArray();
        }

        LYPO_CORE_ERROR("This API is not supported");
        return nullptr;
    }

}

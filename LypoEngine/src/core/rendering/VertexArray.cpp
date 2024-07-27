

#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "platform/opengl/OpenGLVertexArray.hpp"

namespace Lypo {

    VertexArray *VertexArray::create() {
        switch (Renderer::getApi()) {
            case RendererAPI::None:    /*TODO: Log error: None is not supported*/ return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLVertexArray();
        }

        /*TODO: Log error: API is not supported*/
        return nullptr;
    }

}

#include "Texture.h"

#include "Renderer.hpp"
#include "platform/opengl/OpenGlTexture2D.h"


namespace Lypo {

    std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::getApi())
        {
            case RendererAPI::None:    LYPO_CORE_ERROR("RendererAPI::None is not supported") return nullptr;
            case RendererAPI::OpenGL:  return std::make_shared<OpenGlTexture2D>(path);
        }

        LYPO_CORE_ERROR("This API is not supported");
        return nullptr;
    }

}

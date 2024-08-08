//
// Created by mathe on 05/08/2024.
//

#include "OpenGlTexture2D.h"

#include <glad/glad.h>

#include "stb_image.h"

#include <iostream>
#include <filesystem>


namespace Lypo{
    OpenGlTexture2D::OpenGlTexture2D(const std::string& path)
            : path_(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);


        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;


        if(!data){
            LYPO_CORE_ERROR("Failed to load image!");
        }

        width_ = width;
        height_ = height;

        glCreateTextures(GL_TEXTURE_2D, 1, &rendererID_);
        glTextureStorage2D(rendererID_, 1, GL_RGB8, width_, height_);

        glTextureParameteri(rendererID_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(rendererID_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(rendererID_, 0, 0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGlTexture2D::~OpenGlTexture2D()
    {
        glDeleteTextures(1, &rendererID_);
    }

    void OpenGlTexture2D::bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, rendererID_);
    }

}


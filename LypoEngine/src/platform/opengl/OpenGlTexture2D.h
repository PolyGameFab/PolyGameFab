//
// Created by mathe on 05/08/2024.
//
#pragma once

#include "core/rendering/Texture.h"
#include "lypch.h"

namespace Lypo {

    class OpenGlTexture2D : public Texture2D
    {
    public:
        OpenGlTexture2D(const std::string& path);
        virtual ~OpenGlTexture2D();

        virtual uint32_t getWidth() const override { return width_;  }
        virtual uint32_t getHeight() const override { return height_; }

        virtual void bind(uint32_t slot = 0) const override;
    private:
        std::string path_;
        uint32_t width_, height_;
        uint32_t rendererID_;
    };
}


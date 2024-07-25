#pragma once

#include "../../core/window.h"
#include "../../core/templates.h"

#include <GLFW/glfw3.h>

#include <string>

namespace platform 
{
    namespace linux
    {
        class LinuxWindow : public core::Window
        {
        public:
            LinuxWindow(const std::string& title, const uint32_t& width, const uint32_t& height, const core::WindowFlags& flag = core::WindowFlags::DEFAULT) noexcept;
            LinuxWindow(const core::WindowProperties& properties) noexcept;
            virtual ~LinuxWindow() noexcept override;

            void onUpdate() override;

            uint32_t getWidth() const override;
            uint32_t getHeight() const override;

            void setVSync(bool enabled) override;
            bool isVSync() const override; 

            virtual void* getNativeWindow() const;
        private:
            virtual void initialize(const core::WindowProperties& properties) noexcept;
            virtual void shutdown() noexcept;
        private:
            inline static uint8_t counter_ = 0;
            
            GLFWwindow* window_;
            GLFWmonitor* monitor_ = nullptr;
            const GLFWvidmode* mode_ = nullptr;
            
            typedef struct LinuxData
            {
                std::string title_;
                uint32_t width_, height_;
                bool vSync_;
            } data;

            data data_;
        };
    }
}
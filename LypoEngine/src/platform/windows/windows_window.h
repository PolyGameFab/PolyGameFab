#pragma once

#include "../../core/window.h"
#include "../../core/templates.h"

#include <GLFW/glfw3.h>

#include <string>

namespace platform 
{
    namespace windows
    {
        class WindowsWindow : public core::Window
        {
        public:
            WindowsWindow(const std::string& title, const uint32_t& width, const uint32_t& height) noexcept;
            WindowsWindow(const core::WindowProperties& properties) noexcept;
            virtual ~WindowsWindow() noexcept override;

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
            
            typedef struct Data
            {
                std::string title_;
                uint32_t width_, height_;
                bool vSync_;
            } data;

            data data_;
        };
    }
}
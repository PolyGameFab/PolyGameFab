#pragma once

#include "../../core/window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <string>
#include <cstdint>

namespace platform 
{
    namespace windows
    {
        class WindowsWindow : public core::Window
        {
        public:
            WindowsWindow(const std::string& title, const uint32_t& width, const uint32_t& height, const core::WindowFlags& flag = core::WindowFlags::DEFAULT) noexcept;
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
            GLFWwindow* window_ = nullptr;
            GLFWmonitor* monitor_ = nullptr;
            const GLFWvidmode* mode_ = nullptr;
            
            typedef struct WindowsData
            {
                std::string title_;
                uint32_t width_, height_;
                bool vSync_;
            } data;

            data data_;
        };
    }
}
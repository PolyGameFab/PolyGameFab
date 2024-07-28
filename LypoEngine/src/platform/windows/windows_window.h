//
// Created by GuillaumeIsCoding on 7/26/2024.
//
#pragma once

#include "core/window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <cstdint>

namespace platform 
{
        /**
         * @brief Windows concrete class of core::Window
         */
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

            void* getNativeWindow() const;
        private:
            void initialize(const core::WindowProperties& properties) noexcept;
            void shutdown() noexcept;
        private:
            GLFWwindow* window_ = nullptr;
            GLFWmonitor* monitor_ = nullptr;
            const GLFWvidmode* mode_ = nullptr;
            
            struct WindowsData
            {
                std::string title;
                uint32_t width, height;
                bool vSync;
            };

            WindowsData data_;
        };
}
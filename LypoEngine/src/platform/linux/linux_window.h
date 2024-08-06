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
         * @brief Linux concrete class of core::Window
         */
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

            void* getNativeWindow() const;
        private:
            void initialize() noexcept;
            void shutdown() noexcept;
        private:
            std::unique_ptr<DataImpl> p_data_impl_ = nullptr;
        };
}
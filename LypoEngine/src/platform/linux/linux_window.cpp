//
// Created by GuillaumeIsCoding on 7/26/2024.
//
#include "linux_window.h"

#include "platform/glfw/inputs/glfw_input_manager.h"

namespace platform
{
        LinuxWindow::LinuxWindow(const std::string& title, const uint32_t& width, const uint32_t& height, const core::WindowFlags& flag) noexcept : LinuxWindow(core::WindowProperties(title, width, height, flag)) {}
        
        LinuxWindow::LinuxWindow(const core::WindowProperties& properties) noexcept
        {
            initialize(properties);
        }

        LinuxWindow::~LinuxWindow() noexcept
        {
            shutdown();
        }

        void LinuxWindow::initialize(const core::WindowProperties& properties) noexcept
        {
            data_.title = properties.title;
            data_.width = properties.width;
            data_.height = properties.height;
            
            int result = glfwInit();

            switch (properties.flag)
            {
            case core::WindowFlags::FULLSCREEN:
                monitor_ = glfwGetPrimaryMonitor();
            case core::WindowFlags::DEFAULT:
                window_ = glfwCreateWindow(data_.width, data_.height, data_.title.c_str(), monitor_, NULL);
                break;
            case core::WindowFlags::WINDOWED_FULLSCREEN:
                window_ = glfwCreateWindow(data_.width, data_.height, data_.title.c_str(), monitor_, NULL);
                monitor_ = glfwGetPrimaryMonitor();
                mode_ = glfwGetVideoMode(monitor_);
                glfwSetWindowMonitor(window_, monitor_, 0, 0, mode_->width, mode_->height, mode_->refreshRate);
                break;
            }
            
            if (!window_)
            {
                std::cout << "Error while initializing the window" << std::endl;
                return;
            }

            glfwMakeContextCurrent(window_);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Error in glad load" << std::endl;
                return;
            }

            /* Creates InputManager */
            auto im = Lypo::GlfwInputManager(window_);
            /* Set the key callback */
            glfwSetKeyCallback(window_, im.key_callback);

            glfwSetWindowUserPointer(window_, &data_);
            setVSync(true);
        }

        void LinuxWindow::shutdown() noexcept
        {
            glfwDestroyWindow(window_);
            glfwTerminate();
        }

        void LinuxWindow::onUpdate()
        {
            glfwSwapBuffers(window_);

            glfwPollEvents();
        }

        void LinuxWindow::setVSync(bool enabled)
        {
            glfwSwapInterval(enabled ? 1 : 0);
            data_.vSync = enabled;
        }

        bool LinuxWindow::isVSync() const 
        {
            return data_.vSync;
        }

        uint32_t LinuxWindow::getWidth() const 
        {
            return data_.width;
        }

        uint32_t LinuxWindow::getHeight() const 
        {
            return data_.height;
        }

        void* LinuxWindow::getNativeWindow() const
        {
            return window_;
        }
}
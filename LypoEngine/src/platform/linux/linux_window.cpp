//
// Created by GuillaumeIsCoding on 7/26/2024.
//
#include "linux_window.h"

namespace platform
{
    namespace linux
    {
        LinuxWindow::LinuxWindow(const std::string& title, const uint32_t& width, const uint32_t& height, const core::WindowFlags& flag) noexcept : LinuxWindow(core::WindowProps(title, width, height, flag)) {}
        
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
            data_.title_ = properties.title_;
            data_.width_ = properties.width_;
            data_.height_ = properties.height_;
            
            int result = glfwInit();

            switch (properties.flag_)
            {
            case core::WindowFlags::FULLSCREEN:
                monitor_ = glfwGetPrimaryMonitor();
            case core::WindowFlags::DEFAULT:
                window_ = glfwCreateWindow(data_.width_, data_.height_, data_.title_.c_str(), monitor_, NULL);
                break;
            case core::WindowFlags::WINDOWED_FULLSCREEN:
                window_ = glfwCreateWindow(data_.width_, data_.height_, data_.title_.c_str(), monitor_, NULL);
                monitor_ = glfwGetPrimaryMonitor();
                mode_ = glfwGetVideoMode(monitor_);
                glfwSetWindowMonitor(window_, monitor_, 0, 0, mode_->width, mode_->height, mode_->refreshRate);
                break;
            }
            glfwMakeContextCurrent(window_);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Error in glad load" << std::endl;
                return;
            }

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
            glfwPollEvents();
        }

        void LinuxWindow::setVSync(bool enabled)
        {
            if (enabled) glfwSwapInterval(1);
            else glfwSwapInterval(0);
            data_.vSync_ = enabled;
        }

        bool LinuxWindow::isVSync() const 
        {
            return data_.vSync_;
        }

        uint32_t LinuxWindow::getWidth() const 
        {
            return data_.width_;
        }

        uint32_t LinuxWindow::getHeight() const 
        {
            return data_.height_;
        }

        void* LinuxWindow::getNativeWindow() const
        {
            return window_;
        }
    }
}
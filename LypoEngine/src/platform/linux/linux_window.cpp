#include "linux_window.h"

namespace platform
{
    namespace linux
    {
        LinuxWindow::LinuxWindow(const std::string& title, const uint32_t& width, const uint32_t& height) noexcept : LinuxWindow(core::WindowProps(title, width, height)) {}
        
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
            
            if (counter_ == 0)
            {
                int result = glfwInit();
            }

            {
                window_ = glfwCreateWindow(data_.width_, data_.height_, data_.title_.c_str(), NULL, NULL);
                ++counter_;
            }  

            glfwSetWindowUserPointer(window_, &data_);
            setVSync(true);
        }

        void LinuxWindow::shutdown() noexcept
        {
            glfwDestroyWindow(window_);
            --counter_;

            if(counter_ == 0)
            {
                glfwTerminate();
            }
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
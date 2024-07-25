#include "windows_window.h"

namespace platform
{
    namespace windows
    {
        WindowsWindow::WindowsWindow(const std::string& title, const uint32_t& width, const uint32_t& height) noexcept : WindowsWindow(core::WindowProps(title, width, height)) {}
        
        WindowsWindow::WindowsWindow(const core::WindowProperties& properties) noexcept
        {
            initialize(properties);
        }

        WindowsWindow::~WindowsWindow() noexcept
        {
            shutdown();
        }

        void WindowsWindow::initialize(const core::WindowProperties& properties) noexcept
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

        void WindowsWindow::shutdown() noexcept
        {
            glfwDestroyWindow(window_);
            --counter_;

            if(counter_ == 0)
            {
                glfwTerminate();
            }
        }

        void WindowsWindow::onUpdate()
        {
            glfwPollEvents();
        }

        void WindowsWindow::setVSync(bool enabled)
        {
            if (enabled) glfwSwapInterval(1);
            else glfwSwapInterval(0);
            data_.vSync_ = enabled;
        }

        bool WindowsWindow::isVSync() const 
        {
            return data_.vSync_;
        }

        uint32_t WindowsWindow::getWidth() const 
        {
            return data_.width_;
        }

        uint32_t WindowsWindow::getHeight() const 
        {
            return data_.height_;
        }

        void* WindowsWindow::getNativeWindow() const
        {
            return window_;
        }
    }
}
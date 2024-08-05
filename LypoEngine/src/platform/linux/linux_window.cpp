//
// Created by GuillaumeIsCoding on 7/26/2024.
//
#include "linux_window.h"

namespace core
{
    struct Window::DataImpl
        {
            DataImpl(const std::string& title, const uint32_t& width, const uint32_t& height, const core::WindowFlags& flag, bool vSync, 
                            GLFWwindow* window = nullptr, GLFWmonitor* monitor = nullptr, const GLFWvidmode* mode = nullptr)
                            : title(title), width(width), height(height), flag(flag), vSync(vSync), window(window), monitor(monitor), mode(mode) {}
            std::string title;
            uint32_t width, height;
            bool vSync;
            core::WindowFlags flag;
            GLFWwindow* window;
            GLFWmonitor* monitor;
            const GLFWvidmode* mode;
        };
}

namespace platform
{

        LinuxWindow::LinuxWindow(const core::WindowProperties& properties) noexcept : LinuxWindow(properties.title, properties.width, properties.height, properties.flag) {}

        LinuxWindow::LinuxWindow(const std::string& title, const uint32_t& width, const uint32_t& height, const core::WindowFlags& flag) noexcept 
            : p_data_impl_(std::make_unique<LinuxWindow::DataImpl>(title, width, height, flag, false, nullptr, nullptr, nullptr))
        {
            initialize();
        }
        
        LinuxWindow::~LinuxWindow() noexcept
        {
            shutdown();
        }

        void LinuxWindow::initialize() noexcept
        {  
            if (!glfwInit())
            {
                LYPO_CORE_ERROR("Unable to initialize glfw");
                return ;
            }

            switch (p_data_impl_->flag)
            {
                    case core::WindowFlags::FULLSCREEN:
                        p_data_impl_->monitor = glfwGetPrimaryMonitor();
                    case core::WindowFlags::DEFAULT:
                        p_data_impl_->window = glfwCreateWindow(p_data_impl_->width, p_data_impl_->height, p_data_impl_->title.c_str(), p_data_impl_->monitor, NULL);
                        break;
                    case core::WindowFlags::WINDOWED_FULLSCREEN:
                        p_data_impl_->window = glfwCreateWindow(p_data_impl_->width, p_data_impl_->height, p_data_impl_->title.c_str(), p_data_impl_->monitor, NULL);
                        p_data_impl_->monitor = glfwGetPrimaryMonitor();
                        p_data_impl_->mode = glfwGetVideoMode(p_data_impl_->monitor);
                        glfwSetWindowMonitor(p_data_impl_->window, p_data_impl_->monitor, 0, 0, p_data_impl_->mode->width, p_data_impl_->mode->height, p_data_impl_->mode->refreshRate);
                        break;
            }

            if (!p_data_impl_->window)
            {
                LYPO_CORE_ERROR("Unable to initialize the window");
                return;
            }

            glfwMakeContextCurrent(p_data_impl_->window);

            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            {
                LYPO_CORE_ERROR("Unable to load glad");
                return;
            }

            glfwSetWindowUserPointer(p_data_impl_->window, &p_data_impl_);
            setVSync(true);
        }

        void LinuxWindow::shutdown() noexcept
        { 
            glfwDestroyWindow(p_data_impl_->window);
            glfwTerminate();
        }

        void LinuxWindow::onUpdate()
        {
            /* Swap front and back buffers */
            glfwSwapBuffers(p_data_impl_->window);

            glfwPollEvents();
        }

        void LinuxWindow::setVSync(bool enabled)
        {
            glfwSwapInterval(enabled ? 1 : 0);
            p_data_impl_->vSync = enabled;
        }

        bool LinuxWindow::isVSync() const 
        {
            return p_data_impl_->vSync;
        }

        uint32_t LinuxWindow::getWidth() const 
        {
            return p_data_impl_->width;
        }

        uint32_t LinuxWindow::getHeight() const 
        {
            return p_data_impl_->height;
        }

        void* LinuxWindow::getNativeWindow() const
        {
            return p_data_impl_->window;
        }
}
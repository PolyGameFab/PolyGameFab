//
// Created by GuillaumeIsCoding on 8/05/2024
//
#include "core/window.h"

#ifdef LYPO_PLATFORM_WINDOWS
#include "platform/windows/windows_window.h"
#endif
#ifdef LYPO_PLATFORM_LINUX
#include "platform/linux/linux_window.h"
#endif

namespace core
{
    std::unique_ptr<Window> Window::create(const WindowProperties& props) noexcept
    {
        return Window::create(props.title, props.width, props.height, props.flag);
    }

    std::unique_ptr<Window> Window::create(const std::string& title, const uint32_t& width, const uint32_t& height, const WindowFlags& flag) noexcept
    {
        #ifdef LYPO_PLATFORM_WINDOWS
            return std::make_unique<platform::WindowsWindow>(title, width, height, flag);
        #endif
        #ifdef LYPO_PLATFORM_LINUX
            return std::make_unique<platform::LinuxWindow>(title, width, height, flag);
        #else
            LYPO_CLIENT_ERROR("Unknown platform");
            return nullptr;
        #endif
    }
}
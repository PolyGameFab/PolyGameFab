#include "window.h"
#ifdef LYPO_PLATFORM_WINDOWS
    #include "../platform/windows/windows_window.h"
#endif
#ifdef LYPO_PLATFORM_LINUX
    #include "../platform/linux/linux_window.h"
#endif

namespace core
{
    LypoUniquePtr<Window> Window::Create(const WindowProperties& properties)
    {
        return Window::Create(properties.title_, properties.width_, properties.height_, properties.flag_);
    }

    LypoUniquePtr<Window> Window::Create(const std::string& title, const uint32_t& width, const uint32_t& height, const core::WindowFlags& flag)
    {
        #ifdef LYPO_PLATFORM_WINDOWS
            return CreateLypoUniquePtr<platform::windows::WindowsWindow>(title, width, height, flag);
        #endif
        #ifdef LYPO_PLATFORM_LINUX
            return CreateLypoUniquePtr<platform::linux::LinuxWindow>(title, width, height, flag);
        #else
            return nullptr;
        #endif
    }
}
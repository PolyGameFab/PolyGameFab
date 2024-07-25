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
        #ifdef LYPO_PLATFORM_WINDOWS
            return CreateLypoUniquePtr<platform::windows::WindowsWindow>(properties);
        #endif
        #ifdef LYPO_PLATFORM_LINUX
            return CreateLypoUniquePtr<platform::linux::LinuxWindow>(properties);
        #else
            return nullptr;
        #endif
    }
}
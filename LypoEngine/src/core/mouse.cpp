//
// Created by GuillaumeIsCoding on 7/28/2024.
//
#include "core/mouse.h"

#ifdef LYPO_PLATFORM_WINDOWS
#include "platform/windows/windows_mouse.h"
#endif
#ifdef LYPO_PLATFORM_LINUX
#include "platform/linux/linux_mouse.h"
#endif

namespace core
{
    std::unique_ptr<Mouse> Mouse::create(void* window, const MouseConfigurations& configuration)
    {
        #ifdef LYPO_PLATFORM_WINDOWS
        return std::make_unique<platform::WindowsMouse>(window, configuration);
        #endif
        #ifdef LYPO_PLATFORM_LINUX
        return std::make_unique<platform::LinuxMouse>(window, configuration);
        #else
            LYPO_CLIENT_ERROR("Unknown platform");
            return nullptr;
        #endif
    }
}
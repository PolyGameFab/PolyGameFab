//
// Created by GuillaumeIsCoding on 7/26/2024.
//
#pragma once

#include <string>
#include <cstdint>

namespace core 
{
    /**
     * @brief Flags for window creation
     */
    enum class WindowFlags
    {
        DEFAULT,
        WINDOWED_FULLSCREEN,
        FULLSCREEN
    };

    /**
     * @brief Properties for window creation
     */
    struct WindowProperties 
    {
        std::string title;
        uint32_t width, height;
        WindowFlags flag;

        inline WindowProperties() noexcept : WindowProperties("", 0, 0, WindowFlags::DEFAULT) {}
        inline WindowProperties(const std::string& title, const uint32_t& width, 
                                const uint32_t& height, const WindowFlags& flag) noexcept 
                            : title(title), width(width), height(height), flag(flag) {}
    };

    /**
     * @brief API to make the creation of an OpenGL Window easier
     */
    class Window 
    {
    public:
       /**
        * @brief Default destructor
        */
       virtual ~Window() = default;
       
       /**
        * @brief Update the state of the window
        */
       virtual void onUpdate() = 0;

       virtual uint32_t getWidth() const = 0;
       virtual uint32_t getHeight() const = 0;
       
       /**
        * @brief Set whether VSync is enabled or disabled
        * 
        * @param enabled(bool) Enable or disable VSync
        */
       virtual void setVSync(bool enabled) = 0;
       
       /**
        * @brief Check if VSync is enabled or disabled for the window
        */
       virtual bool isVSync() const = 0;

       /**
        * @brief Get the implemented platform window
        */
       virtual void* getNativeWindow() const = 0;
    };
}
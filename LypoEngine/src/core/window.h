//
// Created by GuillaumeIsCoding on 7/26/2024.
//
#pragma once

#include <string>
#include <cstdint>
#include <memory>

#include "core/console_log.h"

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
     * @brief API to make the creation of a Window easier
     */
    class Window 
    {
    public:
       /**
        * @brief Default destructor
        */
       virtual ~Window() noexcept = default;
       /**
        * @brief Updates the state of the window
        */
       virtual void onUpdate() = 0;

       virtual uint32_t getWidth() const = 0;
       virtual uint32_t getHeight() const = 0;
       
       /**
        * @brief Sets whether VSync is enabled or disabled
        * 
        * @param enabled Enable or disable VSync
        */
       virtual void setVSync(bool enabled) = 0;
       
       /**
        * @brief Checks if VSync is enabled or disabled for the window
        */
       virtual bool isVSync() const = 0;

       /**
        * @brief Gets the implemented platform window
        */
       virtual void* getNativeWindow() const = 0;

       /**
        * 
        */
       static std::unique_ptr<Window> create(const WindowProperties& props) noexcept;
       
       /**
        * 
        */
       static std::unique_ptr<Window> create(const std::string& title, const uint32_t& width, const uint32_t& height, const WindowFlags& flag = WindowFlags::DEFAULT) noexcept;
    protected:
        struct DataImpl; 
    };
}
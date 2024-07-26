//
// Created by GuillaumeIsCoding on 7/26/2024.
//
#pragma once

#include "templates.h"

#include <string>
#include <cstdint>

namespace core 
{
    /**
     * @brief Flags for window creation
     */
    typedef enum class WindowFlags
    {
        DEFAULT,
        WINDOWED_FULLSCREEN,
        FULLSCREEN
    } WFlags;

    /**
     * @brief Properties for window creation
     */
    typedef struct WindowProperties 
    {
        std::string title_;
        uint32_t width_, height_;
        WFlags flag_;

        inline WindowProperties() noexcept : WindowProperties("", 0, 0, WindowFlags::DEFAULT) {}
        inline WindowProperties(const std::string& title, const uint32_t& width, 
                                const uint32_t& height, const WindowFlags& flag) noexcept 
                            : title_(title), width_(width), height_(height), flag_(flag) {}
    } WindowProps;

    /**
     * @brief API to make the creation of an OpenGL Window easier
     */
    class Window 
    {
    public:
       /**
        * @brief Default destructor
        */
       inline virtual ~Window() = default;
       
       /**
        * @brief Update the state of the window
        */
       inline virtual void onUpdate() = 0;

       inline virtual uint32_t getWidth() const = 0;
       inline virtual uint32_t getHeight() const = 0;
       
       /**
        * @brief Set whether VSync is enabled or disabled
        * 
        * @param enabled(bool) Enable or disable VSync
        */
       inline virtual void setVSync(bool enabled) = 0;
       
       /**
        * @brief Check if VSync is enabled or disabled for the window
        */
       inline virtual bool isVSync() const = 0;

       /**
        * @brief Get the implemented platform window
        */
       virtual void* getNativeWindow() const = 0;

       /**
        * @brief Create a unique pointer for a Linux or Windows window
        * 
        * @param title(std::string) Window title
        * @param width(uint32_t) Window width
        * @param height(uint32_t) Window height
        * @param flag(WindowFlags) Window flag 
        * 
        * @overload
        */
       static LypoUniquePtr<Window> Create(const std::string& title, const uint32_t& width, const uint32_t& height, const WindowFlags& flag);

       /**
        * @brief Create a unique pointer for a Linux or Windows window
        * 
        * @param properties(WindowProperties) Window properties 
        * 
        * @overload
        */
       static LypoUniquePtr<Window> Create(const WindowProperties& properties = WindowProperties());
    };
}
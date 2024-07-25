#pragma once

#include "templates.h"
#include <string>

namespace core 
{
    typedef struct WindowProperties 
    {
        std::string _title;
        uint32_t _width, _height;

        inline WindowProperties() noexcept : WindowProperties("", 0, 0) {}
        inline WindowProperties(const std::string& title, const uint32_t& width, 
                                const uint32_t& height) noexcept 
                            : _title(title), _width(width), _height(height) {}
    } WindowProps;

    class Window 
    {
    public:
       inline virtual ~Window() = default;

       inline virtual void onUpdate() = 0;

       inline virtual uint32_t getWidth() const = 0;
       inline virtual uint32_t getHeight() const = 0;

       inline virtual void setVSync(bool enabled) = 0;
       inline virtual bool isSync() const = 0;

       virtual void* getNativeWindow() const = 0;

       static LypoUniquePtr<Window> Create(const WindowProperties& properties = WindowProperties());
    };
}
//
// Created by wstap on 7/29/2024.
//

#ifndef WINDOWEVENT_H
#define WINDOWEVENT_H
#include "Event.h"

namespace Lypo {

    class WindowEvent : public Event
    {
    public:
        EVENT_CATEGORY_TYPE(EventCategoryWindow)
    };


    class WindowResizeEvent : public WindowEvent
    {
    public:
        WindowResizeEvent(unsigned int const width, unsigned int const height)
            : width_(width), height_(height) {}

        unsigned int getWidth() const { return width_; }
        unsigned int getHeight() const { return height_; }

        EVENT_CLASS_TYPE(WindowResize)

    private:
        unsigned int width_, height_;
    };


    class WindowCloseEvent : public WindowEvent
    {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
    };

}

#endif //WINDOWEVENT_H

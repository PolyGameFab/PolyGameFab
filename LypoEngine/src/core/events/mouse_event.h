//
// Created by wstap on 7/29/2024.
//

#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H
#include "event.h"

#define MouseCode int

namespace Lypo {
    class MouseMotionEvent : public Event
    {
    public:
        EVENT_CATEGORY_TYPE(EventCategoryMouse | EventCategoryInput)
    };

    class MouseMovedEvent : public MouseMotionEvent
    {
    public:
        MouseMovedEvent(const float x, const float y)
            : mouseX_(x), mouseY_(y) {}

        float getX() const { return mouseX_; }
        float getY() const { return mouseY_; }

        EVENT_CLASS_TYPE(MouseMoved)
    private:
        float mouseX_, mouseY_;
    };

    class MouseScrolledEvent : public MouseMotionEvent
    {
    public:
        MouseScrolledEvent(const float xOffset, const float yOffset)
            : xOffset_(xOffset), yOffset_(yOffset) {}

        float getXOffset() const { return xOffset_; }
        float getYOffset() const { return yOffset_; }

        EVENT_CLASS_TYPE(MouseScrolled)
    private:
        float xOffset_, yOffset_;
    };

    class MouseButtonEvent : public Event
    {
    public:
        MouseCode GetMouseButton() const { return button_; }

        EVENT_CATEGORY_TYPE(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
    protected:
        explicit MouseButtonEvent(const MouseCode button)
            : button_(button) {}

        MouseCode button_;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        explicit MouseButtonPressedEvent(const MouseCode button)
            : MouseButtonEvent(button) {}

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        explicit MouseButtonReleasedEvent(const MouseCode button)
            : MouseButtonEvent(button) {}

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

}

#endif //MOUSEEVENT_H

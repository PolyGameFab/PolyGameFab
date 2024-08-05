//
// Created by wstap on 7/29/2024.
//

#ifndef KEYEVENT_H
#define KEYEVENT_H
#include "event.h"

#define KeyCode int

namespace Lypo {

    class KeyEvent : public Event
    {
    public:
        KeyCode getKeyCode() const { return keyCode_; }

        EVENT_CATEGORY_TYPE(EventCategoryKeyboard | EventCategoryInput)

    protected:
        explicit KeyEvent(const KeyCode keycode)
            : keyCode_(keycode) {}

        KeyCode keyCode_;

    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        explicit KeyPressedEvent(const KeyCode keycode, const bool isRepeat = false)
            : KeyEvent(keycode), isRepeat_(isRepeat) {}
        bool isRepeat() const { return isRepeat_; }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        bool isRepeat_;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(const KeyCode keycode)
            : KeyEvent(keycode) {}

        EVENT_CLASS_TYPE(KeyReleased)

    };

}


#endif //KEYEVENT_H

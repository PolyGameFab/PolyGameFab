//
// Created by wstap on 7/24/2024.
//

#ifndef EVENT_H
#define EVENT_H
#include <vector>

namespace Lypo {
    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
        CustomEvent
    };

#define BIT(x) (1 << x)

    enum EventCategory
    {
        None = 0,
        EventCategoryWindow         = BIT(0),
        EventCategoryInput          = BIT(1),
        EventCategoryKeyboard       = BIT(2),
        EventCategoryMouse          = BIT(3),
        EventCategoryMouseButton    = BIT(4),
        EventCategoryCustom         = BIT(5),
    };

// From Hazel
#define EVENT_CLASS_TYPE(type) [[nodiscard]] static EventType getStaticType() { return EventType::type; }\
                               virtual EventType getEventType() const { return getStaticType(); }\
                               virtual const char* getName() const { return #type; }

#define EVENT_CATEGORY_TYPE(category) virtual int getCategoryFlags() const override { return category; }

    class Event
    {
    public:
        virtual ~Event() = default;

        bool handled = false;

        [[nodiscard]] virtual int getCategoryFlags() const = 0;
        [[nodiscard]] virtual EventType getEventType() const = 0;
        [[nodiscard]] virtual const char* getName() const = 0;

        bool isInCategory(const EventCategory category) const
        {
            return getCategoryFlags() & category;
        }

    };

    class IEventHandler
    {
    public:
        virtual void onEvent(Event* event) = 0;
        virtual void addChild(IEventHandler* child);

        std::vector<IEventHandler*> getChildren() { return children; }

    protected:
        virtual void updateBfsPath();

        IEventHandler* parent = nullptr;
        std::vector<IEventHandler*> children;
    };
}



#endif //EVENT_H

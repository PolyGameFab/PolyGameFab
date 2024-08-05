//
// Created by wstap on 7/30/2024.
//

#ifndef EVENTBUS_H
#define EVENTBUS_H
#include <queue>

#include "real_node_example.h"
#include "event.h"

namespace Lypo {

    class EventBus : public IEventHandler {
    public:
        EventBus(const EventBus&) = delete;
        EventBus& operator=(const EventBus&) = delete;
        static EventBus& getInstance();

        void addEventListener(IEventHandler* node) { addChild(node); };

        void dispatch(Event* event);
        void onEvent(Event* event) override { dispatch(event); }

    private:
        EventBus() = default;
        ~EventBus() = default;

        // Contains the precomputed bfs traversial order to pass the events as fast as possible
        void updateBfsPath() override;
        std::vector<IEventHandler*> bfsOrder_;
    };

} // Lypo

#endif //EVENTBUS_H

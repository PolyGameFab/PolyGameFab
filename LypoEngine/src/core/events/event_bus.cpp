//
// Created by wstap on 7/30/2024.
//

#include "event_bus.h"

namespace Lypo {


    EventBus& EventBus::getInstance() {
        static EventBus instance;
        return instance;
    }

    void EventBus::dispatch(Event* event)
    {
        // Traverses the tree with the precalculated BFS order
        for(IEventHandler* eventHandler : bfsOrder_)
            // Stops only at the end of a level
            if(eventHandler != nullptr)
                eventHandler->onEvent(event);
            else
                if(event->handled) break;
    }

    void EventBus::updateBfsPath()
    {
        std::vector<IEventHandler*> result;
        std::queue<IEventHandler*> q;

        for (IEventHandler* root : children) {
            q.push(root);
        }

        while (!q.empty()) {
            const int levelSize = q.size();

            for (int i = 0; i < levelSize; ++i) {
                IEventHandler* node = q.front();
                q.pop();
                result.push_back(node);

                for (IEventHandler* child : node->getChildren()) {
                    q.push(child);
                }
            }
            // Adds a node to separate tree levels
            result.push_back(nullptr);
        }
        bfsOrder_ = result;
    }

} // Lypo
//
// Created by wstap on 7/29/2024.
//

#ifndef TREE_H
#define TREE_H
#include <iostream>

#include "event.h"

namespace Lypo {
    class RealNode : public IEventHandler
    {
    public:
        explicit RealNode(const int value)
            : value_(value) {}

        void onEvent(Event* event) override { std::cout << value_ << std::endl; }
    private:
        int value_;
    };


} // Lypo

#endif //TREE_H

//
// Created by wstap on 8/4/2024.
//

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

namespace Lypo {
    class InputManager {
    public:
        virtual ~InputManager() = default;

        virtual bool isKeyDown(int key) const = 0;
        virtual bool isKeyUp(int key) const = 0;

        virtual bool isMouseButtonDown(int button) const = 0;
        virtual bool isMouseButtonUp(int button) const = 0;

        virtual double getMouseX() const = 0;
        virtual double getMouseY() const = 0;

        virtual void update() const = 0;
    };
}
#endif //INPUTMANAGER_H

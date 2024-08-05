//
// Created by wstap on 8/3/2024.
//

#ifndef INPUTS_H
#define INPUTS_H
#include "core/inputs/input_manager.h"

#include <glad/glad.h> // Needed for GLFW/glfw3.h
#include <GLFW/glfw3.h>

namespace Lypo {
    class GlfwInputManager : public InputManager {
    public:
        GlfwInputManager(GLFWwindow* window) : window_(window) {}

        // Keyboard inputs
        bool isKeyDown(const int key) const override;
        bool isKeyUp(const int key) const override;

        // Mouse inputs
        bool isMouseButtonDown(int button) const override;
        bool isMouseButtonUp(int button) const override;

        // Mouse position
        double getMouseX() const override;
        double getMouseY() const override;

        // Event handling
        void update() const override;
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    private:
        GLFWwindow* window_;
    };
}


#endif //INPUTS_H

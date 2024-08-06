//
// Created by lapor on 7/19/2024.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/window.h"
#include "core/mouse.h"

#include <iostream>

int main(void)
{
    auto window = core::Window::create("Windows Window", 600, 700, core::WindowFlags::DEFAULT);
    auto mouse = core::Mouse::create(window->getNativeWindow());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(window->getNativeWindow())))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        /* Poll for and process events */
        double xpos, ypos;
        mouse->getPosition(xpos, ypos);
        std::cout << "Mouse Position (" << xpos << ", " << ypos << ")" << std::endl;

        if (mouse->isButtonPressed(core::ButtonValue::BUTTON_RIGHT))
        {
            std::cout << " Right mouse button pressed" << std::endl;
        }
        window->onUpdate();
    }
    return 0;
}
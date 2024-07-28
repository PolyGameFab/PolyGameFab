//
// Created by lapor on 7/19/2024.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "windows_window.h"
#include "windows_mouse.h"

#include <iostream>

int main(void)
{
    platform::WindowsWindow window = platform::WindowsWindow("Windows Window", 600, 700, core::WindowFlags::DEFAULT);
    platform::WindowsMouse mouse = platform::WindowsMouse(window.getNativeWindow());

    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(window.getNativeWindow())))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        /* Poll for and process events */
        double xpos, ypos;
        mouse.getPosition(xpos, ypos);
        std::cout << "Mouse Position (" << xpos << ", " << ypos << ")" << std::endl;

        if (mouse.isButtonPressed(core::ButtonValue::BUTTON_RIGHT))
        {
            std::cout << " Right mouse button pressed" << std::endl;
        }

        window.onUpdate();
    }
    return 0;
}
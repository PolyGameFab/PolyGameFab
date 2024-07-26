//
// Created by lapor on 7/19/2024.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "linux_window.h"

int main(void)
{
   platform::LinuxWindow window = platform::LinuxWindow("Linux Window", 600, 700, core::WindowFlags::DEFAULT);
   
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(window.getNativeWindow())))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        /* Poll for and process events */
        window.onUpdate();
    }
    return 0;
}
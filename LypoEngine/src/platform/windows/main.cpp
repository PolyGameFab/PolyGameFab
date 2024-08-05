//
// Created by lapor on 7/19/2024.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../../core/events/event_bus.h"
#include "windows_window.h"
#include "platform/opengl/opengl_shader.h"

int main(void)
{
    platform::WindowsWindow window = platform::WindowsWindow("Windows Window", 600, 700, core::WindowFlags::DEFAULT);
    Lypo::Shader *shader = new Lypo::OpenglShader("vertex.glsl", "fragment.glsl");

    auto& bus = Lypo::EventBus::getInstance();

    auto eventHandler1 = new Lypo::RealNode(1);

    auto eventHandler1_1 = new Lypo::RealNode(11);
    auto eventHandler1_2 = new Lypo::RealNode(12);
    auto eventHandler1_3 = new Lypo::RealNode(13);

    auto eventHandler1_1_1 = new Lypo::RealNode(111);
    auto eventHandler1_1_2 = new Lypo::RealNode(112);

    auto eventHandler1_2_1 = new Lypo::RealNode(121);
    auto eventHandler1_2_2 = new Lypo::RealNode(122);


    eventHandler1_1->addChild(eventHandler1_1_1);
    eventHandler1_1->addChild(eventHandler1_1_2);

    eventHandler1_1->addChild(eventHandler1_2_1);
    eventHandler1_1->addChild(eventHandler1_2_2);

    bus.addEventListener(eventHandler1);

    eventHandler1->addChild(eventHandler1_1);
    eventHandler1->addChild(eventHandler1_2);
    eventHandler1->addChild(eventHandler1_3);

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f, 0.5f, 0.0f // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    /* Make the window's context current */
    // glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Error in glad load" << std::endl;
        return -1;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


  
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(reinterpret_cast<GLFWwindow *>(window.getNativeWindow())))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        shader->bind();
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* Swap front and back buffers */

        /* Poll for and process events */
        window.onUpdate();
      
        /* Simple test to query if a specific key is pressed */
        // std::cout << im.isKeyPressed(68) << std::endl;
    }

    glfwTerminate();
    return 0;
}
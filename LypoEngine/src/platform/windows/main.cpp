//
// Created by lapor on 7/19/2024.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/rendering/VertexBuffer.hpp"
#include "core/rendering/IndexBuffer.hpp"

#include "windows_window.h"
#include "platform/opengl/opengl_shader.h"


int main(void)
{
    platform::WindowsWindow window = platform::WindowsWindow("Windows Window", 600, 700, core::WindowFlags::DEFAULT);
    Lypo::Shader *shader = new Lypo::OpenglShader("vertex.glsl", "fragment.glsl");

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

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Error in glad load" << std::endl;
        return -1;
    }

    //from learnopengl.com
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Shader creation for test
    const char *vertexShaderSource = "#version 410 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    const char *fragmentShaderSource = "#version 410 core\n"
                                       "out vec4 FragColor;\n"
                                       "\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
                                       "} ";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Array Buffer
    unsigned int vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    float vertices[3*3] = {
            -0.5f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            0.0f, -0.5f, 0.0f
    };

    Lypo::VertexBuffer::Create(vertices, sizeof(vertices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);


    //index buffer;
    unsigned int indecies[3] = {0, 1, 2};
    Lypo::IndexBuffer::Create(indecies, sizeof(indecies));


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(reinterpret_cast<GLFWwindow *>(window.getNativeWindow())))
    {
        /* Render here */
        //vertex buffer

        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */

        /* Poll for and process events */
        window.onUpdate();
    }

    glfwTerminate();
    return 0;
}
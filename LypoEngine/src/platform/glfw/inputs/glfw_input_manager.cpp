//
// Created by wstap on 8/4/2024.
//

#include "glfw_input_manager.h"

#include "core/events/event_bus.h"
#include "core/events/key_event.h"

namespace Lypo {

    bool GlfwInputManager::isKeyDown(const int key) const
    {
        return glfwGetKey(window_, key) == GLFW_PRESS;
    }

    bool GlfwInputManager::isKeyUp(const int key) const
    {
        return glfwGetKey(window_, key) == GLFW_RELEASE;
    }

    // Mouse inputs
    bool GlfwInputManager::isMouseButtonDown(int button) const
    {
        return glfwGetMouseButton(window_, button) == GLFW_PRESS;
    }

    bool GlfwInputManager::isMouseButtonUp(int button) const
    {
        return glfwGetMouseButton(window_, button) == GLFW_RELEASE;
    }

    // Mouse position
    double GlfwInputManager::getMouseX() const
    {
        double xpos, ypos;
        glfwGetCursorPos(window_, &xpos, &ypos);
        return xpos;
    }

    double GlfwInputManager::getMouseY() const
    {
        double xpos, ypos;
        glfwGetCursorPos(window_, &xpos, &ypos);
        return ypos;
    }

    // Poll events
    void GlfwInputManager::update() const
    {
        glfwPollEvents();
    }


    void GlfwInputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Lypo::EventBus& bus = Lypo::EventBus::getInstance();
        std::cout << "--------key_callback----------" << std::endl;
        std::cout   << "Key: "      << key << std::endl
                    << "Scancode: " << scancode << std::endl
                    << "Action: "   << action << std::endl
                    << "Mods: "     << mods << std::endl;

        switch (action)
        {
            case GLFW_PRESS:
            {
                Lypo::KeyPressedEvent event(key, false);
                bus.dispatch(&event);
                break;
            }
            case GLFW_RELEASE:
            {
                Lypo::KeyReleasedEvent event(key);
                bus.dispatch(&event);
                break;
            }
            case GLFW_REPEAT:
            {
                Lypo::KeyPressedEvent event(key, true);
                bus.dispatch(&event);
                break;
            }
            default:
                break;
        }
    }
}

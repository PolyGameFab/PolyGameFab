//
// Created by GuillaumeIsCoding on 7/28/2024.
//
#include "windows_mouse.h"

namespace platform
{
	WindowsMouse::WindowsMouse(void* window, const core::MouseConfigurations& configuration) noexcept
	{
		initialize(window, configuration);
	}

	void WindowsMouse::initialize(void* window, const core::MouseConfigurations& configuration) noexcept
	{
		window_ = static_cast<GLFWwindow*>(window);

		setConfiguration(configuration);

		glfwSetCursorPosCallback(window_, WindowsMouse::positionCallback);
		glfwSetMouseButtonCallback(window_, WindowsMouse::buttonCallback);
		glfwSetScrollCallback(window_, WindowsMouse::scrollCallback);
	}

	void WindowsMouse::positionCallback(GLFWwindow* window, double x_position, double y_position) noexcept
	{
		WindowsMouse::data_.x_position = x_position * WindowsMouse::data_.sensitivity;
		WindowsMouse::data_.y_position = y_position * WindowsMouse::data_.sensitivity;
	}

	void WindowsMouse::scrollCallback(GLFWwindow* window, double x_offset, double y_offset) noexcept
	{
		WindowsMouse::data_.x_offset += x_offset * WindowsMouse::data_.sensitivity;
		WindowsMouse::data_.y_offset += y_offset * WindowsMouse::data_.sensitivity;
	}

	void WindowsMouse::buttonCallback(GLFWwindow* window, int button_value, int action, int mods) noexcept
	{
		if (button_value >= static_cast<int>(core::ButtonValue::BUTTON_1) && button_value < static_cast<int>(core::ButtonValue::BUTTON_8)) WindowsMouse::data_.buttons[button_value] = (action == GLFW_PRESS);
	}

	void WindowsMouse::setSensitivity(const float& sensitivity)
	{
		WindowsMouse::data_.sensitivity = (WindowsMouse::data_.sensitivity != sensitivity) ? sensitivity : WindowsMouse::data_.sensitivity;
	}

	void WindowsMouse::setConfiguration(const core::MouseConfigurations& configuration)
	{
		switch (configuration)
		{
		case core::MouseConfigurations::LOCK:
			glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			break;
		case core::MouseConfigurations::HIDDEN:
			glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			break;
		default:
			glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		}
	}

	void WindowsMouse::getPosition(double& x_position, double& y_position)
	{
		x_position = WindowsMouse::data_.x_position;
		y_position = WindowsMouse::data_.y_position;
	}

	bool WindowsMouse::isButtonPressed(const core::ButtonValue& button_value) const
	{
		return WindowsMouse::data_.buttons[static_cast<int>(button_value)];
	}
}
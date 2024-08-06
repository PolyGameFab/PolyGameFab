//
// Created by GuillaumeIsCoding on 7/28/2024.
//
#include "windows_mouse.h"

namespace core
{
	struct Mouse::DataImpl
	{
		DataImpl() : x_position(0.0), y_position(0.0), x_offset(0.0), y_offset(0.0), sensitivity(1.0f) {}
		
		double x_position, y_position;
		double x_offset, y_offset;
		float sensitivity;
		bool buttons[8] = {false};
		GLFWwindow* window;
	};
}

namespace platform
{
	std::unique_ptr<WindowsMouse::DataImpl> WindowsMouse::p_data_impl_ = std::make_unique<WindowsMouse::DataImpl>();

	WindowsMouse::WindowsMouse(void* window, const core::MouseConfigurations& configuration) noexcept
	{
		initialize(window, configuration);
	}

	void WindowsMouse::initialize(void* window, const core::MouseConfigurations& configuration) noexcept
	{
		p_data_impl_->window = static_cast<GLFWwindow*>(window);

		setConfiguration(configuration);

		glfwSetCursorPosCallback(p_data_impl_->window, WindowsMouse::positionCallback);
		glfwSetMouseButtonCallback(p_data_impl_->window, WindowsMouse::buttonCallback);
		glfwSetScrollCallback(p_data_impl_->window, WindowsMouse::scrollCallback);
	}

	void WindowsMouse::positionCallback(GLFWwindow* window, double x_position, double y_position) noexcept
	{
		WindowsMouse::p_data_impl_->x_position = x_position * WindowsMouse::p_data_impl_->sensitivity;
		WindowsMouse::p_data_impl_->y_position = y_position * WindowsMouse::p_data_impl_->sensitivity;
	}

	void WindowsMouse::scrollCallback(GLFWwindow* window, double x_offset, double y_offset) noexcept
	{
		WindowsMouse::p_data_impl_->x_offset += x_offset * WindowsMouse::p_data_impl_->sensitivity;
		WindowsMouse::p_data_impl_->y_offset += y_offset * WindowsMouse::p_data_impl_->sensitivity;
	}

	void WindowsMouse::buttonCallback(GLFWwindow* window, int button_value, int action, int mods) noexcept
	{
		if (button_value >= static_cast<int>(core::ButtonValue::BUTTON_1) && button_value < static_cast<int>(core::ButtonValue::BUTTON_8)) WindowsMouse::p_data_impl_->buttons[button_value] = (action == GLFW_PRESS);
	}

	void WindowsMouse::setSensitivity(const float& sensitivity)
	{
		WindowsMouse::p_data_impl_->sensitivity = (WindowsMouse::p_data_impl_->sensitivity != sensitivity) ? sensitivity : WindowsMouse::p_data_impl_->sensitivity;
	}

	void WindowsMouse::setConfiguration(const core::MouseConfigurations& configuration)
	{
		switch (configuration)
		{
		case core::MouseConfigurations::LOCK:
			glfwSetInputMode(p_data_impl_->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			break;
		case core::MouseConfigurations::HIDDEN:
			glfwSetInputMode(p_data_impl_->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			break;
		default:
			glfwSetInputMode(p_data_impl_->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		}
	}

	void WindowsMouse::getPosition(double& x_position, double& y_position)
	{
		x_position = WindowsMouse::p_data_impl_->x_position;
		y_position = WindowsMouse::p_data_impl_->y_position;
	}

	bool WindowsMouse::isButtonPressed(const core::ButtonValue& button_value) const
	{
		return WindowsMouse::p_data_impl_->buttons[static_cast<int>(button_value)];
	}
}
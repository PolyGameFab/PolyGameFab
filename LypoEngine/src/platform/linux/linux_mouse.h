//
// Created by GuillaumeIsCoding on 7/28/2024.
//
#pragma once

#include "core/mouse.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace platform
{
	/**
	 * @brief Linux concrete class of core::Mouse
	 */
	class LinuxMouse : public core::Mouse
	{
	public:
		LinuxMouse(void* window, const core::MouseConfigurations& configuration = core::MouseConfigurations::DEFAULT) noexcept;
		virtual ~LinuxMouse() noexcept override = default;

		void setSensitivity(const float& sensitivity) override;
		void setConfiguration(const core::MouseConfigurations& configuration) override;

		void getPosition(double& x_position, double& y_position) override;

		bool isButtonPressed(const core::ButtonValue& value) const override;
	private:
		void initialize(void* window, const core::MouseConfigurations& configuration) noexcept;

		static void positionCallback(GLFWwindow* window, double x_position, double y_position) noexcept;
		static void scrollCallback(GLFWwindow* window, double x_offset, double y_offset) noexcept;
		static void buttonCallback(GLFWwindow* window, int button, int action, int mods) noexcept;
	private:
		struct MouseData
		{
			double x_position, y_position;
			double x_offset, y_offset;
			double sensitivity;
			bool buttons[8] = { false };

			MouseData() : x_position(0.0), y_position(0.0), x_offset(0.0), y_offset(0.0), sensitivity(1.0f) {}
		};

		GLFWwindow* window_ = nullptr;

		inline static MouseData data_ = LinuxMouse::MouseData();
	};
}
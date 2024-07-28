//
// Created by GuillaumeIsCoding on 7/28/2024.
//
#pragma once

namespace core
{
	enum class MouseConfigurations
	{
		DEFAULT,
		LOCK,
		HIDDEN,
	};

	enum class ButtonValue
	{
		BUTTON_1,
		BUTTON_2,
		BUTTON_3,
		BUTTON_4,
		BUTTON_5,
		BUTTON_6,
		BUTTON_7,
		BUTTON_8,
		BUTTON_LAST = BUTTON_8,
		BUTTON_LEFT = BUTTON_1,
		BUTTON_RIGHT = BUTTON_2,
		BUTTON_MIDDLE = BUTTON_3
	};

	class Mouse
	{
	public:
		virtual ~Mouse() noexcept = default;

		virtual void setSensitivity(const float& sensitivity) = 0;
		virtual void setConfiguration(const core::MouseConfigurations& configuration) = 0;
		virtual void getPosition(double& x_position, double& y_position) = 0;

		virtual bool isButtonPressed(const core::ButtonValue& button_value) const = 0;
	};
}
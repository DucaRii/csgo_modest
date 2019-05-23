#pragma once

#include "controls.hpp"

namespace shared::gui
{
	void render();
	void handle_input();

	controls::c_control* get_focus();
	void update_focus( controls::c_control* control );
}
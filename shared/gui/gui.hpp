#pragma once
#include "../math/math.hpp"

namespace shared::gui
{
	enum e_gui_element_type
	{
		UNKNOWN,
		TOGGLE,
		SLIDER,
		SELECT
	};

	struct gui_element_t
	{
		int m_type = UNKNOWN;
		std::string_view m_label = "";

		struct gui_toggle_element_t
		{
			bool* m_value_ptr;
			std::string_view m_enabled_str = "Enabled";
			std::string_view m_disabled_str = "Disabled";

		} m_toggle;

		struct gui_slider_element_t
		{
			float* m_value_ptr = nullptr;
			float m_min_value = 0;
			float m_max_value = 100;
			std::string_view m_display_format = "{:.0f}%";

		} m_slider;

		struct gui_select_element_t
		{
			int* m_value_ptr = nullptr;
			std::vector<std::string_view> m_options = { "None" };
			std::string_view m_display_format = "{}";

		} m_select;
	};

	struct render_functions_t
	{
		std::function<void( const math::vec2_t pos, const math::vec2_t size, const col_t& color )> m_fill_rect;
		std::function<void( const math::vec2_t pos, const math::vec2_t size, const col_t& color )> m_rect;
		std::function<void( const math::vec2_t start, const math::vec2_t end, const col_t& color )> m_line;
		std::function<void( const math::vec2_t& pos, const col_t& color, std::string_view text )> m_text;
		std::function<math::vec2_t( std::string_view text )> m_text_size;
	};

	render_functions_t& get_functions();

	bool begin( std::string_view title );
	void end();

	void process_input();

	void toggle( std::string_view label, bool* value_ptr, std::string_view enabled_str = "Enabled", std::string_view disabled_str = "Disabled" );
	void slider( std::string_view label, float* value_ptr, float min_value, float max_value, std::string_view display_format = "{:.0f}%" );
	void select( std::string_view label, int* value_ptr, const std::vector<std::string_view>& options = { "None" }, std::string_view display_format = "{}" );

	void toggle();
	bool is_open();
}
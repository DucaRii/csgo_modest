#pragma once

#include "../math/datatypes/vec2_t.hpp"
#include "../color/col_t.hpp"

namespace shared::gui::controls
{
	enum e_control_state
	{
		IDLE,
		HOVERED,
		ACTIVE
	};

	class c_group
	{
	public:
	};

	class c_control
	{
	public:
		c_control() = default;
		~c_control() = default;

		void init( c_group* parent );

		virtual void render( math::vec2_t& group_pos ) = 0;
		virtual void handle_input() = 0;

		virtual void setup_style() = 0;

		void set_name( std::string_view name );
		std::string_view get_name();

		void set_size( const math::vec2_t& size );
		math::vec2_t get_size();

		void set_state( const int state );
		int get_state();

		void add_dependency( std::function<bool()> func );
		std::vector<std::function<bool()>>& get_dependencies();
		bool should_render();

		void set_parent( c_group* parent );
		c_group* get_parent();
	private:
		math::vec2_t m_pos = {};
		math::vec2_t m_size = {};

		int m_state = 0;

		std::string_view m_name = "";
		math::vec2_t m_name_size = {};

		c_group* m_parent = nullptr;

		std::vector<std::function<bool()>> m_dependencies = {};
	};
	
	class c_checkbox : public c_control
	{
	public:
	};
}
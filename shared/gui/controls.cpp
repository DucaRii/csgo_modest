#include "../shared.hpp"

namespace shared::gui::controls
{
	void c_control::init( c_group* window )
	{
		m_parent = window;

		setup_style();
	}

	void c_control::add_dependency( std::function<bool()> func )
	{
		m_dependencies.push_back( func );
	}

	std::vector<std::function<bool()>>& c_control::get_dependencies()
	{
		return m_dependencies;
	}

	bool c_control::should_render()
	{
		bool is_ok = true;
		for ( const auto& func : m_dependencies )
		{
			if ( func() )
				continue;

			is_ok = false;
			break;
		}

		return is_ok;
	}

	void c_control::set_parent( c_group* parent )
	{
		m_parent = parent;
	}

	c_group* c_control::get_parent()
	{
		return m_parent;
	}

	void c_control::set_name( std::string_view name )
	{
		m_name = name;
	}

	std::string_view c_control::get_name()
	{
		return m_name;
	}

	void c_control::set_size( const math::vec2_t& size )
	{
		m_size = size;
	}

	math::vec2_t c_control::get_size()
	{
		return m_size;
	}

	void c_control::set_state( const int state )
	{
		m_state = state;
	}

	int c_control::get_state()
	{
		return m_state;
	}
}
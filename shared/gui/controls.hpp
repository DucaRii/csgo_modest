#pragma once

namespace shared::gui::controls
{
	class c_control
	{
	public:
		virtual void render( math::vec2_t& pos ) = 0;
		virtual void handle_input() = 0;

		virtual void setup_style() = 0;

		virtual bool should_skip()
		{
			return false;
		};

		inline void set_id( const int id )
		{
			m_id = id;
		}

		inline int get_id()
		{
			return m_id;
		}

		inline void set_size( math::vec2_t& size )
		{
			m_size = size;
		}

		inline math::vec2_t get_size()
		{
			return m_size;
		}

		inline void set_pos( math::vec2_t& pos )
		{
			m_pos = pos;
		}

		inline math::vec2_t get_pos()
		{
			return m_pos;
		}

		inline void set_active( bool in )
		{
			m_is_active = in;
		}

		inline bool get_active()
		{
			return m_is_active;
		}

		inline void push_action( float cur_time )
		{
			m_last_action = cur_time;
		}

		inline void reset_action()
		{
			m_last_action = std::numeric_limits<float>::max();
		}
	protected:
		math::vec2_t m_size = {};
		math::vec2_t m_pos = {};

		int m_id = 0;

		float m_last_action = 0.f;

		bool m_is_active = false;

		std::string_view m_name = "";
		math::vec2_t m_name_size = {};
	};

	class c_tab : public c_control
	{
	public:
		c_tab( std::string_view name );

		void render( math::vec2_t& pos );
		void handle_input();

		void setup_style();

		c_control* add( std::shared_ptr<c_control> control );
	private:
		struct style_t
		{
			col_t m_col_text;
			col_t m_col_text_hover;

			col_t m_col_inner;

			col_t m_col_line_active;
			col_t m_col_line;

			int m_window_padding;
		} m_style;

		int m_skip_id;

		int m_max_controls;

		int m_active_control_id = 0;

		std::vector<std::shared_ptr<c_control>> m_items = {};
	};

	class c_checkbox : public c_control
	{
	public:
		c_checkbox( std::string_view name, config::item_t* var );

		void render( math::vec2_t& pos );
		void handle_input();

		void setup_style();
	private:
		void render_checkbox();

		struct style_t
		{
			col_t m_col_text;
			col_t m_col_text_hover;

			col_t m_col_checkbox;
			col_t m_col_checkbox_active;
			col_t m_col_checkbox_inner;
			col_t m_col_checkbox_outline;

			int m_inner_padding;

			int m_checkbox_width;
		} m_style;

		config::item_t* m_var = nullptr;
	};

	class c_separator : public c_control
	{
	public:
		c_separator( std::string_view name );

		void render( math::vec2_t& pos );
		void handle_input();

		void setup_style();

		bool should_skip()
		{
			return true;
		}
	private:
		struct style_t
		{
			col_t m_col_text;

			col_t m_col_separator;

			int m_inner_padding;
		} m_style;
	};

	class c_combo : public c_control
	{
	public:
		c_combo( std::string_view name, config::item_t* var, std::vector<std::string_view> items );

		void render( math::vec2_t& pos );
		void handle_input();

		void setup_style();
	private:
		void render_combobox();
		void render_preview();

		struct style_t
		{
			col_t m_col_text;
			col_t m_col_text_hover;

			col_t m_col_combobox_inner;
			col_t m_col_combobox_outline;

			col_t m_col_combobox_popup;

			int m_inner_padding;

			int m_combobox_width;
		} m_style;

		std::vector<std::string_view> m_items = {};
		std::vector<int> m_item_widths = {};

		config::item_t* m_var = nullptr;
	};

	class c_slider : public c_control
	{
	public:
		c_slider( std::string_view name, config::item_t* var, float min, float max, float step = 1.f );

		void render( math::vec2_t& pos );
		void handle_input();

		void setup_style();
	private:
		void handle_slide();
		void render_slider();

		struct style_t
		{
			col_t m_col_text;
			col_t m_col_text_hover;

			col_t m_col_slider;
			col_t m_col_slider_inner;
			col_t m_col_slider_outline;

			int m_inner_padding;

			int m_slider_width;
		} m_style;

		float m_min;
		float m_max;

		bool m_did_increase;

		float m_step;

		config::item_t* m_var = nullptr;
	};
}
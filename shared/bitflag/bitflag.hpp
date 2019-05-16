#pragma once

namespace shared
{
	struct bitflag_t
	{
		bitflag_t() = default;
		bitflag_t( uint32_t flags ) : m_flags( flags ) {}

		~bitflag_t() = default;

		uint32_t m_flags{};

		inline bool has_flag( uint32_t flag )
		{
			return m_flags & flag;
		}

		inline void add_flag( uint32_t flag )
		{
			m_flags |= flag;
		}

		inline  void remove_flag( uint32_t flag )
		{
			m_flags &= ~flag;
		}
	};
}
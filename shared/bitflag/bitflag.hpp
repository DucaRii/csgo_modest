#pragma once

namespace shared
{
	struct bitflag_t
	{
		/// <summary>
		/// Creates a default bitflag object
		/// </summary>
		bitflag_t() = default;

		/// <summary>
		/// Creates a bitflag object with the given flags
		/// </summary>
		bitflag_t( uintptr_t flags ) : m_flags( flags ) {}

		/// <summary>
		/// Destroys the bitflag object
		/// </summary>
		~bitflag_t() = default;

		/// <summary>
		/// Stored flags
		/// </summary>
		uintptr_t m_flags{};

		/// <summary>
		/// Checks whether the given flag is present in the stored flags
		/// </summary>
		/// <param name="flag">Flag that will be checked</param>
		/// <returns>Returns true if the flag is present in the stored flags</returns>
		inline bool has_flag( uintptr_t flag )
		{
			return m_flags & flag;
		}

		/// <summary>
		/// Adds the given flag to the stored flags
		/// </summary>
		/// <param name="flag">Flag that will be added</param>
		inline void add_flag( uintptr_t flag )
		{
			m_flags |= flag;
		}

		/// <summary>
		/// Removes the given flag to the stored flags
		/// </summary>
		/// <param name="flag">Flag that will be removed</param>
		inline void remove_flag( uintptr_t flag )
		{
			m_flags &= ~flag;
		}

		/// <summary>
		/// Checks if there are no flags stored
		/// </summary>
		/// <returns>True if no flags stored</returns>
		inline bool is_empty()
		{
			return !m_flags;
		}
	};
}
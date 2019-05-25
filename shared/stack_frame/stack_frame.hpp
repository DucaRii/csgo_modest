#pragma once

namespace shared
{
	struct stack_frame_t
	{
		/// <summary>
		/// Current frame pointer
		/// </summary>
		address_t m_fp;

		/// <summary>
		/// Current return address
		/// </summary>
		address_t m_ret;

		/// <summary>
		/// Default constructor
		/// </summary>
		stack_frame_t() = default;

		/// <summary>
		/// Sets up the frame pointer address
		/// </summary>
		/// <param name="ret">Address of return address</param>
		stack_frame_t( void* ret ) : m_fp{} { setup( uintptr_t( ret ) ); }

		/// <summary>
		/// Sets up the frame pointer address
		/// </summary>
		/// <param name="ret">Address of return address</param>
		stack_frame_t( uintptr_t ret ) : m_fp{} { setup( ret ); }

		~stack_frame_t() = default;

		/// <summary>
		/// Sets up the frame pointer address
		/// </summary>
		/// <param name="ret">Address of return address</param>
		void setup( uintptr_t ret )
		{
			/// Frame pointer = address of return address - sizeof( void* )
			m_fp = address_t( ret - sizeof( uintptr_t ) );

			/// Store address of return address
			/// Deref once to get to the actual return address
			m_ret = address_t( ret ).get();
		}

		/// <summary>
		/// Retrieves the stored frame pointer address
		/// </summary>
		/// <returns>Current frame pointer</returns>
		uintptr_t get_frame_pointer()
		{
			return m_fp;
		}

		/// <summary>
		/// Retrieves the return address
		/// </summary>
		/// <returns>Current return address</returns>
		uintptr_t get_return_address()
		{
			return m_ret;
		}

		/// <summary>
		/// Walks up one stackframe
		/// </summary>
		void previous()
		{
			m_fp.self_get();
		}

		/// <summary>
		/// Gets a variable address relative to the frame pointer
		/// </summary>
		/// <param name="offset">The variable offset, negative for local variables and positive for arguments</param>
		template< typename t = uintptr_t >
		t get_var( std::ptrdiff_t offset )
		{
			return m_fp.offset( offset ).cast<t>();
		}
	};
}

#define INIT_STACKFRAME() auto stack_frame = shared::stack_frame_t( uintptr_t( _AddressOfReturnAddress() ) );
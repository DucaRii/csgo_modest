#pragma once

namespace shared
{
	struct stack_frame_t
	{
		address_t m_fp;

		stack_frame_t() = default;
		stack_frame_t( void* ret ) { setup( uintptr_t( ret ) ); }
		stack_frame_t( uintptr_t ret ) { setup( ret ); }

		~stack_frame_t() = default;

		void setup( uintptr_t ret )
		{
			/// Frame pointer = address of return address - sizeof( void* )
			m_fp = address_t( ret - sizeof( uintptr_t ) );
		}

		uintptr_t get_frame_pointer()
		{
			return m_fp;
		}

		uintptr_t get_return_address()
		{
			/// AddressOfReturnAddress points to the return address
			/// so it's gotta be dereferenced once
			return m_fp.offset( sizeof( uintptr_t ) ).get();
		}

		void previous()
		{
			m_fp = m_fp.get();
		}

		address_t get_var( std::ptrdiff_t offset )
		{
			return address_t( m_fp.offset( offset ) );
		}
	};
}

#define INIT_STACKFRAME() auto stack_frame = shared::stack_frame_t( uintptr_t( _AddressOfReturnAddress() ) );
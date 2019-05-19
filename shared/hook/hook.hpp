#pragma once

#include "../mem/mem.hpp"
#include "../mem_protect/mem_protect.hpp"

namespace shared::hook
{
	struct hook_t
	{
		hook_t() = default;
		hook_t( uintptr_t ptr ) : m_vtable( reinterpret_cast< uintptr_t** >( ptr ) ), m_table_length( 0 ), m_orig( nullptr ), m_replace( nullptr ) {};
		hook_t( void* ptr ) : m_vtable( reinterpret_cast< uintptr_t** >( ptr ) ), m_table_length( 0 ), m_orig( nullptr ), m_replace( nullptr ) {};
		hook_t( void** ptr ) : m_vtable( reinterpret_cast< uintptr_t** >( ptr ) ), m_table_length( 0 ), m_orig( nullptr ), m_replace( nullptr ) {};
		hook_t( address_t ptr ) : m_vtable( ptr.as<uintptr_t**>() ), m_table_length( 0 ), m_orig( nullptr ), m_replace( nullptr ) {};

		~hook_t()
		{
			unhook();
		}

		bool init()
		{
			if ( !m_vtable )
				return false;

			INIT_MEM_PROTECT_RW( m_vtable, sizeof( uintptr_t ) );

			/// Store old vtable
			m_orig = *m_vtable;

			m_table_length = mem::get_vtable_length( m_orig );

			/// Either faulty vtable or function fail
			if ( !m_table_length )
				return false;

			/// Allocate new vtable ( +1 for RTTI )
			m_replace = std::make_unique<uintptr_t[]>( m_table_length + 1 );

			/// instantiate all values with 0
			std::memset( m_replace.get(),
						 NULL,
						 m_table_length * sizeof( uintptr_t ) + sizeof( uintptr_t ) );

			/// The following two memcpy's could be just made 
			/// into 1 call but for demonstration purposes
			/// I'll leave it like that

			/// Copy old table
			/// Skip first 4 bytes to later insert RTTI there
			std::memcpy( &m_replace[ 1 ],
						 m_orig,
						 m_table_length * sizeof( uintptr_t ) );

			/// Copy RTTI
			std::memcpy( m_replace.get(),
						 &m_orig[ -1 ],
						 sizeof( uintptr_t ) );

			/// Apply new vtable, again skipping the first 4
			/// bytes since that's where the RTTI is now located
			*m_vtable = &m_replace[ 1 ];

			return true;
		}

		template< typename t >
		void hook( const uint16_t index, t replace_function )
		{
			/// Is index out of bounds?
			if ( index < 0 || index > m_table_length )
				return;

			m_replace[ index + 1 ] = reinterpret_cast< uintptr_t >( replace_function );
		}

		template< typename t >
		t get_original( const uint16_t index )
		{
			/// Is index out of bounds?
			if ( index < 0 || index > m_table_length )
				return nullptr;

			return reinterpret_cast< t >( m_orig[ index ] );
		}

		/// Unhook specific index
		void unhook( const uint16_t index )
		{
			/// Is index out of bounds?
			if ( index < 0 || index > m_table_length )
				return;

			m_replace[ index + 1 ] = m_orig[ index ];
		}

		/// Completely restore old vtable
		void unhook()
		{
			/// Check if it was already restored
			if ( !m_orig )
				return;

			INIT_MEM_PROTECT_RW( m_vtable, sizeof( uintptr_t ) );

			*m_vtable = m_orig;

			/// Prevent double unhook
			m_orig = nullptr;
		}

		uintptr_t** m_vtable;

		uint16_t m_table_length;

		uintptr_t* m_orig;
		std::unique_ptr<uintptr_t[]> m_replace;
	};
}
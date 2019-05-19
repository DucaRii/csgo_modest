#pragma once

#include "../mem/mem.hpp"

namespace shared::hook
{
	struct hook_t
	{
		hook_t() = default;
		hook_t( uintptr_t ptr ) : m_ptr( ptr ), m_table_length( 0 ), m_backup( nullptr ), m_replace( nullptr ) {};
		hook_t( void* ptr ) : m_ptr( ptr ), m_table_length( 0 ), m_backup( nullptr ), m_replace( nullptr ) {};
		hook_t( address_t ptr ) : m_ptr( ptr ), m_table_length( 0 ), m_backup( nullptr ), m_replace( nullptr ) {};

		bool init()
		{
			if ( !m_ptr )
				return false;

			/// Store old vtable
			m_backup = m_ptr.to<uintptr_t*>();
			m_table_length = mem::get_vtable_length( m_backup ) + 1;

			/// Either faulty vtable or function fail
			if ( !m_table_length )
				return false;

			/// Allocate new vtable
			m_replace = std::make_unique<uint32_t[]>( m_table_length + 1 );

			/// Copy old table ( include 4 extra bytes for RTTI )
			std::memcpy( m_replace.get(),
						 reinterpret_cast< void* >( m_backup - sizeof( uint32_t ) ),
						 m_table_length * sizeof( uint32_t ) );

			/// Adjust memory page to include RTTI
			DWORD old_flags;
			auto old_ptr = m_ptr.as<uintptr_t*>();
			VirtualProtect( old_ptr, sizeof( uintptr_t ), PAGE_READWRITE, &old_flags );

			old_ptr = m_ptr.as<uintptr_t*>();
			m_ptr.get() = reinterpret_cast< uint32_t >( m_replace.get() ) + sizeof( uint32_t );

			/// Backup
			VirtualProtect( old_ptr, sizeof( uintptr_t ), old_flags, &old_flags );
		}

		template< typename t >
		void hook( uint16_t index, t replace_function )
		{
			/// Is index out of bounds?
			if ( index < 0 || index > m_table_length )
				return;

			m_replace.get()[ index + 1 ] = reinterpret_cast< uintptr_t >( replace_function );
		}

		template< typename t >
		t get_original( const uint16_t index )
		{
			return reinterpret_cast< t >( m_backup.offset( 0x4 * index ) );
		}

		address_t m_ptr;

		uint16_t m_table_length;

		address_t m_backup;
		std::unique_ptr<uint32_t[]> m_replace;
	};
}
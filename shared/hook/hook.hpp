#pragma once

#include "../mem/mem.hpp"
#include "../mem_protect/mem_protect.hpp"

namespace shared::hook
{
	struct hook_t
	{
		/// <summary>
		/// Creates default hook object
		/// </summary>
		hook_t() = default;

		/// <summary>
		/// Sets up a hook with given object pointer
		/// </summary>
		/// <param name="ptr">Address of object from desired vtable</param>
		hook_t( uintptr_t ptr ) : m_vtable( reinterpret_cast< uintptr_t** >( ptr ) ), m_table_length( 0 ), m_orig( nullptr ), m_replace( nullptr ) {};

		/// <summary>
		/// Sets up a hook with given object pointer
		/// </summary>
		/// <param name="ptr">Address of object from desired vtable</param>
		hook_t( void* ptr ) : m_vtable( reinterpret_cast< uintptr_t** >( ptr ) ), m_table_length( 0 ), m_orig( nullptr ), m_replace( nullptr ) {};

		/// <summary>
		/// Sets up a hook with given object pointer
		/// </summary>
		/// <param name="ptr">Address of object from desired vtable</param>
		hook_t( address_t ptr ) : m_vtable( ptr.cast<uintptr_t**>() ), m_table_length( 0 ), m_orig( nullptr ), m_replace( nullptr ) {};

		/// <summary>
		/// Sets up hook and replaces the vtable with new one
		/// </summary>
		/// <returns>Returns true if hooks was successfully initialized
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

		/// <summary>
		/// Hooks a given index
		/// </summary>
		/// <param name="index">
		/// Index of the function that should be replaced.
		/// Keep in mind that you have to +1 the index since 
		/// In the new vtable the RTTI is stored at the first index
		/// and thus all indexes are shifted by 1 
		/// </param>
		/// <param name="replace_function">The function which will be called instead of the original</param>
		template< typename t >
		void hook( const uint16_t index, t replace_function )
		{
			/// Is index out of bounds?
			if ( index < 0 || index > m_table_length )
				throw std::out_of_range( fmt::format( "hook_t::hook - Trying to hook at faulty index {} while max index is {}", index, m_table_length ) );

			m_replace[ index + 1 ] = reinterpret_cast< uintptr_t >( replace_function );
		}

		/// <summary>
		/// Gets a pointer to the original function with a given index
		/// </summary>
		/// <param name="index">Index of the function that should be retrieved</param>
		/// <returns>Returns the function pointer casted into a given function type</returns>
		template< typename t >
		t get_original( const uint16_t index )
		{
			/// Is index out of bounds?
			if ( index < 0 || index > m_table_length )
				throw std::out_of_range( fmt::format( "hook_t::get_original - Trying to get original function of hook at faulty index {} while max index is {}", index, m_table_length ) );

			return reinterpret_cast< t >( m_orig[ index ] );
		}

		/// <summary>
		/// Unhooks specific index
		/// </summary>
		/// <param name="index">Index of the function that should be unhooked</param>
		void unhook( const uint16_t index )
		{
			/// Is index out of bounds?
			if ( index < 0 || index > m_table_length )
				throw std::out_of_range( fmt::format( "hook_t::unhook - Trying to unhook at faulty index {} while max index is {}", index, m_table_length ) );

			m_replace[ index + 1 ] = m_orig[ index ];
		}

		/// <summary>
		/// Restore old vtable and thus unhook all functions
		/// </summary>
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

		/// <summary>
		/// The vtable that is being modified
		/// </summary>
		uintptr_t** m_vtable;

		/// <summary>
		/// Amount of all functions within the vtable
		/// </summary>
		uint16_t m_table_length;

		/// <summary>
		/// Pointer to the original vtable
		/// </summary>
		uintptr_t* m_orig;

		/// <summary>
		/// New custom vtable
		/// </summary>
		std::unique_ptr<uintptr_t[]> m_replace;
	};
}
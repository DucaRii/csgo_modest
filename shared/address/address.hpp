#pragma once

#include "../bitflag/bitflag.hpp"

namespace shared
{
	class address_t
	{
	public:
		/// <summary>
		/// Inner pointer
		/// </summary>
		uintptr_t m_ptr;

		/// <summary>
		/// Creates a NULL address object
		/// </summary>
		address_t() : m_ptr{} {};

		/// <summary>
		/// Creates an address object with the given pointer
		/// </summary>
		/// <param name="ptr">The address on which the object will be based on</param>
		address_t( uintptr_t ptr ) : m_ptr( ptr ) {};

		/// <summary>
		/// Creates an address object with the given pointer
		/// </summary>
		/// <param name="ptr">The address on which the object will be based on</param>
		address_t( uintptr_t* ptr ) : m_ptr( uintptr_t( ptr ) ) {};

		/// <summary>
		/// Creates an address object with the given pointer
		/// </summary>
		/// <param name="ptr">The address on which the object will be based on</param>
		address_t( const void* ptr ) : m_ptr( uintptr_t( ptr ) ) {};

		/// <summary>
		/// Destroys the address object
		/// </summary>
		~address_t() = default;

		/// <summary>
		/// Whenever an address object is being passed into a function but it requires
		/// a uintptr this function will be called
		/// </summary>
		inline operator uintptr_t() const
		{
			return m_ptr;
		}

		/// <summary>
		/// Whenever an address object is being passed into a function but it requires
		/// a void* this function will be called
		/// </summary>
		inline operator void* ( )
		{
			return reinterpret_cast< void* >( m_ptr );
		}

		/// <summary>
		/// Returns the inner pointer
		/// </summary>
		/// <returns>Inner pointer</returns>
		inline uintptr_t get_inner() const
		{
			return m_ptr;
		}

		/// <summary>
		/// Compares the inner pointer with the given address
		/// </summary>
		/// <param name=in>Address that will be compared</param>
		/// <returns>True if the addresses match</returns>
		template< typename t = address_t >
		inline bool compare( t in ) const
		{
			return m_ptr == uintptr_t( in );
		}

		/// Actions performed on self

		/// <summary>
		/// Deref inner pointer
		/// </summary>
		/// <param name="in">Times the pointer will be deref'd</param>
		/// <returns>Current address object</returns>
		inline address_t& self_get( uint8_t in = 1 )
		{
			m_ptr = get<uintptr_t>( in );

			return *this;
		}

		/// <summary>
		/// Add offset to inner pointer
		/// </summary>
		/// <param name="in">Offset that will be added</param>
		/// <returns>Current address object</returns>
		inline address_t& self_offset( ptrdiff_t offset )
		{
			m_ptr += offset;

			return *this;
		}

		/// <summary>
		/// Follows a relative JMP instruction
		/// </summary>
		/// <param name="offset">Offset at which the function address is</param>
		/// <returns>Address object</returns>
		template< typename t = address_t >
		inline address_t & self_rel( std::ptrdiff_t offset = 0 )
		{
			m_ptr = rel( offset );
		}

		/// <summary>
		/// Set inner pointer to given value
		/// </summary>
		/// <param name="in">Offset that will be added</param>
		/// <returns>Current address object</returns>
		template< typename t = address_t >
		inline address_t & set( t in )
		{
			m_ptr = uintptr_t( in );

			return *this;
		}

		/// Const actions

		/// <summary>
		/// Returns a casted version of the inner pointer
		/// </summary>
		/// <returns>Current address object</returns>
		template< typename t = uintptr_t >
		inline t cast()
		{
			return t( m_ptr );
		}

		/// <summary>
		/// Deref inner pointer
		/// </summary>
		/// <param name="in">Times the pointer will be deref'd</param>
		/// <returns>Current address object</returns>
		template< typename t = address_t >
		inline t get( uint8_t in = 1 )
		{
			uintptr_t dummy = m_ptr;

			while ( in-- )
				/// Check if pointer is still valid
				if ( dummy )
					dummy = *reinterpret_cast< uintptr_t* >( dummy );

			return t( dummy );
		}

		/// <summary>
		/// Add offset to inner pointer
		/// </summary>
		/// <param name="in">Offset that will be added</param>
		/// <returns>Address object</returns>
		template< typename t = address_t >
		inline t offset( ptrdiff_t offset )
		{
			return t( m_ptr + offset );
		}

		/// <summary>
		/// Follows a relative JMP instruction
		/// </summary>
		/// <param name="offset">Offset at which the function address is</param>
		/// <returns>Address object</returns>
		template< typename t = address_t >
		inline t rel( std::ptrdiff_t offset = 0 )
		{
			/// Example:
			/// E9 ? ? ? ?
			/// The offset has to skip the E9 (JMP) instruction
			/// Then deref the address coming after that to get to the function
			/// Since the relative JMP is based on the next instruction after the address it has to be skipped

			/// Base address is the address that follows JMP ( 0xE9 ) instruction
			uintptr_t base = m_ptr + offset;

			/// Store the function pointer
			auto rel_jump = *reinterpret_cast< uintptr_t* >( base );

			/// The JMP is based on the instruction after the address
			/// so the address size has to be added
			base += sizeof( uintptr_t );

			/// Now finally do the JMP by adding the function address
			base += rel_jump;

			return t( base );
		}
	};
}
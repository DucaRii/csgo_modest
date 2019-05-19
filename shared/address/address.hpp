#pragma once

#include "../bitflag/bitflag.hpp"

namespace shared
{
	class address_t
	{
	public:
		uintptr_t m_ptr;

		address_t() : m_ptr{} {};
		address_t( uintptr_t ptr ) : m_ptr( ptr ) {};
		address_t( void* ptr ) : m_ptr( uintptr_t( ptr ) ) {};

		~address_t() = default;

		inline operator uintptr_t() const
		{
			return m_ptr;
		}

		inline operator void* ( ) const
		{
			return reinterpret_cast< void* >( m_ptr );
		}

		/// Cast address and deref
		template< typename t = address_t >
		__forceinline t to() const
		{
			return *( t* )( m_ptr );
		}

		/// Cast address
		template< typename t = address_t >
		inline t as() const
		{
			return ( t )( m_ptr );
		}

		/// Add to address
		template< typename t = address_t >
		inline t offset( std::ptrdiff_t offset ) const
		{
			return ( t )( m_ptr + offset );
		}

		/// Dereference address x times
		template< typename t = address_t >
		inline t get( uint8_t derefs = 1 )
		{
			uintptr_t dummy = m_ptr;

			while ( derefs-- && is_safe( dummy ) )
				dummy = *reinterpret_cast< uintptr_t* >( dummy );

			return ( t )dummy;
		}

		/// Set address to value
		template< typename t = address_t >
		inline void set( t val )
		{
			*reinterpret_cast< t* >( m_ptr ) = val;
		}

		/// Get relative offset
		template< typename t = address_t >
		inline t rel( std::ptrdiff_t offset = 0 )
		{
			uintptr_t out;
			uint32_t rel;

			out = m_ptr + offset;

			rel = *reinterpret_cast< uint32_t* >( out );
			if ( !rel )
				return t{};

			out = ( out + 0x4 ) + rel;

			return ( t )( out );
		}

		/// Check if address is valid
		inline static bool is_safe( address_t address )
		{
			static MEMORY_BASIC_INFORMATION32 mbi{};

			if ( !address
				 || address < 0x10000
				 || address > 0xFFE00000
				 || !VirtualQuery( address, ( PMEMORY_BASIC_INFORMATION )& mbi, sizeof( mbi ) ) )
				return false;

			if ( !mbi.AllocationBase
				 || mbi.State != MEM_COMMIT
				 || mbi.Protect == PAGE_NOACCESS
				 || mbi.Protect & PAGE_GUARD )
				return false;

			return true;
		}
	};
}
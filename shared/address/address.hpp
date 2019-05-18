#pragma once

namespace shared
{
	struct address_t
	{
		address_t() = default;
		address_t( uintptr_t ptr ) : m_ptr( ptr ) {};
		address_t( void* ptr ) : m_ptr( uintptr_t( ptr ) ) {};

		~address_t() = default;

		inline operator uintptr_t()
		{
			return m_ptr;
		}

		/// Cast address and deref
		template< typename t = address_t >
		__forceinline t to() const
		{
			return *reinterpret_cast< t* >( m_ptr );
		}

		/// Cast address
		template< typename t = address_t >
		inline t as() const
		{
			return reinterpret_cast< t >( m_ptr );
		}

		/// Add to address
		template< typename t = address_t >
		inline t offset( std::ptrdiff_t offset ) const
		{
			return static_cast< t >( m_ptr + offset );
		}

		/// Dereference address x times
		template< typename t = address_t >
		inline t get( uint8_t derefs = 1 )
		{
			uintptr_t dummy = m_ptr;

			while ( derefs-- && mem::is_safe_address( dummy ) )
				dummy = *reinterpret_cast< uintptr_t* >( dummy );

			return dummy;
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

			return reinterpret_cast< t >( out );
		}

		uintptr_t m_ptr;
	};
}
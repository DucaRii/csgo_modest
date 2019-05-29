#pragma once

namespace shared
{
	struct mem_protect_t
	{
		/// <summary>
		/// Creates a protection object with the given arguments
		/// </summary>
		/// <param name="address">The address which should be affected</param>
		/// <param name="size">The size of the memory which should be affected</param>
		/// <param name="flags">The new flags of the memory</param>
		mem_protect_t( LPVOID address, uint32_t size, DWORD flags ) : m_address( address ), m_size( size ), m_flags( 0 )
		{
			if ( !VirtualProtect( m_address, m_size, flags, &m_flags ) )
				throw std::system_error( GetLastError(), std::system_category(), "Failed to protect the specified page-region" );
		}

		/// <summary>
		/// Destroys the protection object and automatically restores old flags
		/// </summary>
		~mem_protect_t()
		{
			VirtualProtect( m_address, m_size, m_flags, &m_flags );
		}

		/// <summary>
		/// Address of affected memory
		/// </summary>
		LPVOID m_address;

		/// <summary>
		/// Size of affected memory
		/// </summary>
		uint32_t m_size;

		/// <summary>
		/// Old proctection flags
		/// </summary>
		DWORD m_flags;
	};

#define INIT_MEM_PROTECT_RW( address, size ) auto protect = mem_protect_t( address, size, PAGE_READWRITE );
#define INIT_MEM_PROTECT_R( address, size ) auto protect = mem_protect_t( address, size, PAGE_READONLY );
#define INIT_MEM_PROTECT_W( address, size ) auto protect = mem_protect_t( address, size, PAGE_WRITECOPY );
#define INIT_MEM_PROTECT( address, size, flags ) auto protect = mem_protect_t( address, size, flags );
}
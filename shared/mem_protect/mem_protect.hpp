#pragma once

namespace shared
{
	class mem_protect
	{
	public:
		mem_protect( LPVOID address, uint32_t size, DWORD flags ) : m_address( address ), m_size( size ), m_flags( 0 )
		{
			VirtualProtect( m_address, m_size, flags, &m_flags );
		}

		~mem_protect()
		{
			VirtualProtect( m_address, m_size, m_flags, &m_flags );
		}

	private:
		LPVOID m_address;
		uint32_t m_size;
		DWORD m_flags;
	};

#define INIT_MEM_PROTECT_RW( address, size ) auto protect = mem_protect( address, size, PAGE_READWRITE );
#define INIT_MEM_PROTECT_R( address, size ) auto protect = mem_protect( address, size, PAGE_READONLY );
#define INIT_MEM_PROTECT_W( address, size ) auto protect = mem_protect( address, size, PAGE_WRITECOPY );
#define INIT_MEM_PROTECT( address, size, flags ) auto protect = mem_protect( address, size, flags );
}
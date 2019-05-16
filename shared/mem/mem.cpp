#include "../shared.hpp"

namespace shared::mem
{
	bool is_safe_address( address_t address )
	{
		/// Check for nullptr
		if ( !address )
			return false;

		/// Check if it's within relevant area
		if ( address < 0x1000 ||
			 address > 0xFFE0000 )
			return false;

		/// Get memory info
		static MEMORY_BASIC_INFORMATION32 info{};
		if ( !VirtualQuery( address.as<void*>(), reinterpret_cast< PMEMORY_BASIC_INFORMATION >(&info), sizeof(info)))
			return false;

		/// Check for base address pointer
		if ( !info.AllocationBase )
			return false;

		/// Check if page has been allocated memory
		if ( ! bitflag_t( info.State ).has_flag( MEM_COMMIT ) )
			return false;

		/// Check if we have access to the page memory
		if ( info.Protect == PAGE_NOACCESS
			 || bitflag_t( info.Protect ).has_flag( PAGE_GUARD ) )
			return false;

		/// Nice address
		return true;
	}
}
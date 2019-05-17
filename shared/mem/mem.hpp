#pragma once

namespace shared::mem
{
	address_t find_ida_sig( const char* mod, const char* sig );
	address_t find_ida_sig( const char* mod, const std::vector< const char* >& sigs );

	inline address_t call_vfunc( address_t table, uint16_t index );

	inline uint32_t get_vtable_length( address_t table );

	inline bool is_safe_address( address_t address );
}
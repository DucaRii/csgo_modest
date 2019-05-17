#pragma once

namespace shared::mem
{
	address_t find_ida_sig( const std::string& mod, const std::string& sig );
	address_t find_ida_sig( const std::string& mod, const std::vector< const std::string& > sigs );

	inline address_t call_vfunc( address_t table, uint16_t index );

	inline uint32_t get_vtable_length( address_t table );

	inline bool is_safe_address( address_t address );
}
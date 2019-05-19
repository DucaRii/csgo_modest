#pragma once

namespace shared::mem
{
	address_t find_ida_sig( const char* mod, const char* sig );
	address_t find_ida_sig( const char* mod, const std::vector< const char* >& sigs );

	address_t call_vfunc( address_t table, uint16_t index );

	uint32_t get_vtable_length( address_t table );
}

#define MEMBER_FUNC_ARGS(...) ( this, __VA_ARGS__ ); }
#define VFUNC( index, func, sig ) auto func { return shared::mem::call_vfunc( this, index ).as< sig >() MEMBER_FUNC_ARGS
#define CUSTOM_VFUNC( func, sig, addr ) auto func { return addr.as< sig >() MEMBER_FUNC_ARGS
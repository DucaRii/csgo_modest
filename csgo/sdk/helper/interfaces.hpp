#pragma once

namespace interfaces
{
	uintptr_t* get( const char* interface_name );
	uintptr_t* get( const char* mod_name, const char* interface_name );
}
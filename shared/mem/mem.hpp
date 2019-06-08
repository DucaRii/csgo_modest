#pragma once

namespace shared::mem
{
	/// <summary>
	/// Tries to find a ida style signature in the given module
	/// </summary>
	/// <param name="mod">Module in which the signature will be searched</param>
	/// <param name="sig">The ida style signature that will be searched for</param>
	/// <returns>Address, if it was found</returns>
	address_t find_ida_sig( const char* mod, const char* sig );

	/// <summary>
	/// Tries to find multiple ida style signature in the given module
	/// </summary>
	/// <param name="mod">Module in which the signature will be searched</param>
	/// <param name="sig">The ida style signatures that will be searched for</param>
	/// <returns>Address, if it was found</returns>
	address_t find_ida_sig( const char* mod, const std::vector< const char* >& sigs );

	/// <summary>
	/// Tries to find a fizz style signature in the given module
	/// </summary>
	/// <param name="mod">Module in which the signature will be searched</param>
	/// <param name="sig">The fizz style signature that will be searched for</param>
	/// <returns>Address, if it was found</returns>
	address_t find_fizz_sig( const char* mod, const char* sig );

	/// <summary>
	/// Tries to find multiple fizz style signature in the given module
	/// </summary>
	/// <param name="mod">Module in which the signature will be searched</param>
	/// <param name="sig">The fizz style signatures that will be searched for</param>
	/// <returns>Address, if it was found</returns>
	address_t find_fizz_sig( const char* mod, const std::vector< const char* >& sigs );

	/// <summary>
	/// Will get a vfunc from a given vtable + index
	/// </summary>
	/// <param name="table">Pointer of which the vtable will be retrieved and searched (not the actual vtable)</param>
	/// <param name="index">Index of the virtual function</param>
	/// <returns>Address of the virtual function, if it was found</returns>
	address_t get_vfunc( address_t table, uint16_t index );

	/// <summary>
	/// Will get the length of a given vtable
	/// </summary>
	/// <param name="table">Pointer of which the vtable will be retrieved and searched</param>
	/// <returns>Amount of virtual functions found</returns>
	uint32_t get_vtable_length( address_t table );

	/// <summary>
	/// Will get all loaded modules from the current process
	/// </summary>
	/// <returns>Modules</returns>
	std::vector<std::wstring>& get_loaded_modules();
}

#define NOINLINE __declspec( noinline )

#define MEMBER_FUNC_ARGS(...) ( this, __VA_ARGS__ ); }
#define VFUNC( index, func, sig ) auto func { return shared::mem::get_vfunc( this, index ).cast< sig >() MEMBER_FUNC_ARGS
#define CUSTOM_VFUNC( func, sig, addr ) auto func { return addr.cast< sig >() MEMBER_FUNC_ARGS
#define OFFSET( type, func, offset ) type& func() { return *reinterpret_cast< type* >( reinterpret_cast< uintptr_t >( this ) + offset.cast() ); }
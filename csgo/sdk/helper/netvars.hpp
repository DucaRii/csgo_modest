#pragma once

namespace netvars
{
	void init();

	uint16_t get( uint32_t table, uint32_t field );
	uint16_t get( std::string_view table, std::string_view field );

	uint16_t find_in_datamap( datamap_t* map, uint32_t name );
}

#define DATAMAPVAR(funcname, type, datamapname) type& funcname() \
{ \
	static auto offset = netvars::find_in_datamap( this->get_pred_desc_map(), CT_HASH( datamapname ) ); \
    return *reinterpret_cast< type* >( uintptr_t( this ) + offset ); \
}

#define NETVAR( type, func, table, var ) type& func() \
{\
	static auto offset = netvars::get( CT_HASH( table ), CT_HASH( var ) );\
	return *reinterpret_cast< type* >( reinterpret_cast< uintptr_t >( this ) + offset );\
}

#define NETVARADD( type, func, table, var, add ) type& func() \
{\
	static auto offset = netvars::get( CT_HASH( table ), CT_HASH( var ) );\
	return *reinterpret_cast< type* >( reinterpret_cast< uintptr_t >( this ) + offset + add );\
}

#define PNETVAR( type, func, table, var ) type* func() \													 \
{ \
	static auto offset = netvars::get( CT_HASH( table ), CT_HASH( var ) ); \
	return reinterpret_cast< type* >( reinterpret_cast< uintptr_t >( this ) + offset ); \
}

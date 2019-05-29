#include "../../csgo.hpp"

/// credits to deadcell for some shit here

namespace netvars
{
	struct netvar_t
	{
		netvar_t() : m_ptr{ }, m_offset{ } { }

		RecvProp* m_ptr;
		uint16_t m_offset;
	};

	std::unordered_map<uint32_t, std::unordered_map<uint32_t, netvar_t>> m_offsets;

	void init()
	{
		/// Nothing we can do if the interface wasn't initialized
		if ( !ctx::csgo.client )
			throw std::runtime_error( "netvars::init - client pointer not valid" );

		if ( auto client_class_list = ctx::csgo.client->GetAllClasses() )
		{
			const std::function<void( const char*, RecvTable*, size_t )> store = [ & ]( const char* name, RecvTable * table, size_t offset = 0 )
			{
				uint32_t var = 0, base = HASH( name );

				RecvProp* prop;
				RecvTable* child;

				/// Go through all props
				for ( int i = 0; i < table->m_nProps; ++i )
				{
					/// Current prop
					prop = &table->m_pProps[ i ];
					child = prop->m_pDataTable;

					/// This table has more props in it
					if ( child && child->m_nProps > 0 )
						store( name, child, prop->m_Offset + offset );

					/// Insert var
					var = HASH( prop->m_pVarName );
					if ( !m_offsets[ base ][ var ].m_offset )
					{
						m_offsets[ base ][ var ].m_ptr = prop;
						m_offsets[ base ][ var ].m_offset = static_cast< uint16_t >( prop->m_Offset + offset );
					}
				}
			};

			for ( ; client_class_list; client_class_list = client_class_list->m_pNext )
				store( client_class_list->m_pRecvTable->m_pNetTableName, client_class_list->m_pRecvTable, 0 );
		}
	}

	uint16_t get( uint32_t table, uint32_t field )
	{
		return m_offsets[ table ][ field ].m_offset;
	}

	/// Wrapper function that gets the hashes of the strings and
	/// then calls the hash get functio
	uint16_t get( std::string_view table, std::string_view field )
	{
		return m_offsets[ HASH( table.data() ) ][ HASH( field.data() ) ].m_offset;
	}

	uint16_t find_in_datamap( datamap_t * map, uint32_t name )
	{
		while ( map )
		{
			for ( auto i = 0; i < map->dataNumFields; i++ )
			{
				if ( map->dataDesc[ i ].fieldName == nullptr )
					continue;

				if ( name == HASH( map->dataDesc[ i ].fieldName ) )
					return map->dataDesc[ i ].fieldOffset[ TD_OFFSET_NORMAL ];

				if ( map->dataDesc[ i ].fieldType == FIELD_EMBEDDED )
				{
					if ( map->dataDesc[ i ].td )
					{
						unsigned int offset;

						if ( ( offset = find_in_datamap( map->dataDesc[ i ].td, name ) ) != 0 )
							return offset;
					}
				}
			}
			map = map->baseMap;
		}
		return 0u;
	}
}
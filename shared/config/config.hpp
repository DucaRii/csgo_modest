#pragma once

#include "../hash/hash.hpp"

namespace shared::config
{
	struct item_t
	{
		item_t() = default;
		item_t( const hash_t name, const hash_t type, const std::any var )
			: m_name( name ), m_type( type ), m_var( var )
		{};

		~item_t() = default;

		/// <summary>
		/// Cast the inner variable to the desired type and returns it
		/// </summary>
		/// <returns>Casted variable</returns>
		template< typename t >
		t& get()
		{
			return *reinterpret_cast< t* >( std::any_cast< t >( &m_var ) );
		}

		/// <summary>
		/// Sets the inner variable to the desired value
		/// </summary>
		/// <param name="val">Value that the variable will be set to</param>
		template< typename t >
		void set( t val )
		{
			m_var.emplace<t>( val );
		}

		hash_t m_name;
		hash_t m_type;
		std::any m_var;
	};

	/// <summary>
	/// Returns the registered config items vector
	/// </summary>
	/// <returns>Registered config items</returns>
	std::vector<item_t>& get_items();

	/// <summary>
	/// Adds a new config item into the vector
	/// </summary>
	/// <param name="name">Identifier of the variable ( has to be unique )</param>
	/// <param name="type">Type of the varialble</param>
	/// <param name="def">Default value of the variable</param>
	/// <returns>Index of the item in the vector</returns>
	template< typename t >
	uint32_t add_item( const hash_t name, const hash_t type, const t def )
	{
		get_items().push_back( item_t( name, type, std::make_any<t>( def ) ) );

		return get_items().size() - 1u;
	}

	/// <summary>
	/// Gets config item variable from vector index
	/// </summary>
	/// <param name="index">Index of the config item</param>
	/// <returns>Config item variable</returns>
	template< typename t >
	t& get( const uint32_t index )
	{
		return get_items().at( index ).get<t>();
	}

	/// <summary>
	/// Gets config item from vector index
	/// </summary>
	/// <param name="index">Index of the config item</param>
	/// <returns>Config item</returns>
	item_t& get_item( const uint32_t index );
	int does_item_exist( const hash_t name );

	/// <summary>
	/// Saves current config
	/// </summary>
	void save();

	/// <summary>
	/// Loads current config
	/// </summary>
	void load();

	/// <summary>
	/// Sets the name of the current config file
	/// </summary>
	/// <param name="config">Name of config file</param>
	void set_config_file( const std::string_view config );

	/// <summary>
	/// Gets the name of the current config file
	/// </summary>
	/// <returns>Name of the config file</returns>
	std::string_view get_config_file();

	/// <summary>
	/// Sets the name of the current config directory
	/// </summary>
	/// <param name="config">Name of config directory</param>
	void set_config_directory( const std::string_view name );

	/// <summary>
	/// Gets the current config directory
	/// </summary>
	/// <returns>Name of the config directory</returns>
	std::string_view get_config_directory();
}

#define ADD_CFG_ITEM( type, name, def ) const uint32_t name = shared::config::add_item<type>( CT_HASH( #name ), CT_HASH( #type ), def );
#define ADD_CFG_ITEM_VEC( type, datatype, size, name, def ) const uint32_t name = shared::config::add_item<std::vector<datatype>>( CT_HASH( #name ), CT_HASH( #type ), shared::misc::create_filled_vector<datatype, size>( def ) );
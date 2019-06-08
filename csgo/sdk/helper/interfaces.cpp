#include "../../csgo.hpp"

namespace interfaces
{
	/// https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/tier1/interface.h#L72
	using InstantiateInterfaceFn = void* ( __cdecl* )( );
	struct InterfaceReg
	{
		InstantiateInterfaceFn	m_CreateFn;
		const char* m_pName;

		InterfaceReg* m_pNext; // For the global list.
		static InterfaceReg* s_pInterfaceRegs;
	};

	std::unordered_map< uint32_t,
		std::vector< std::pair< const char*, address_t >>>& get_interface_map()
	{
		static std::unordered_map< uint32_t,
			std::vector< std::pair< const char*, address_t >>> interfaces{};

		return interfaces;
	}

	bool build_interface_list()
	{
		auto& interface_map = get_interface_map();

		if ( interface_map.empty() )
		{
			for ( auto mod : mem::get_loaded_modules() )
			{
				auto module_address = GetModuleHandleW( mod.c_str() );
				if ( !module_address )
					continue;

				/// Find internal CreateInterface function and walk the context
				auto create_interface_fn = address_t( uintptr_t( GetProcAddress( module_address, "CreateInterface" ) ) );
				if ( !create_interface_fn )
					continue;

				/// This is what the function looks like, we want to get the JMP
				/// instruction and follow it
				/// .text:108C25F0 55                                push    ebp
				/// .text:108C25F1 8B EC                             mov     ebp, esp
				/// .text:108C25F3 5D                                pop     ebp
				/// .text:108C25F4 E9 87 FF FF FF                    jmp     sub_108C2580    ; Jump
				///                ^ This is the JMP instruction

				/// We will follow that jump and get the interface_reg_list
				/// .text : 108C2580 55                                push    ebp
				///	.text : 108C2581 8B EC                           mov     ebp, esp
				///	.text : 108C2583 56                              push    esi
				///	.text : 108C2584 8B 35 64 CA 14 13               mov     esi, interface_reg_list
				///                        ^_________^ Get this address ( interface_reg_list )

				auto list =
					create_interface_fn.self_find_opcode( 0xE9 ) /// Find JMP opcode
					.self_jmp() /// Jump to relative function
					.self_find_opcode( 0x35, 0x1 ).get< InterfaceReg* >( 2 ); /// Find opcode where interface_reg_list is moved and add 0x1 to get to the address

				if ( !list )
					continue;

				auto& entry = interface_map[ HASH( misc::to_utf8( mod ).c_str() ) ];

				/// Continue to walk the list until it's no longer valid
				while ( list )
				{
					entry.push_back( std::make_pair( list->m_pName, uintptr_t( list->m_CreateFn() ) ) );

					list = list->m_pNext;
				}
			}
		}

		return !interface_map.empty();
	}

	uintptr_t* get( const char* interface_name )
	{
		/// Was the interface list built successfully?
		if ( !build_interface_list() )
			return nullptr;

		auto& interface_map = get_interface_map();

		/// Loop through all logged interfaces
		for ( auto& entry : interface_map )
		{
			if ( entry.second.empty() )
				return nullptr;

			for ( auto& cur : entry.second )
			{
				if ( std::string( cur.first ).find( interface_name ) != std::string::npos )
				{
					LOG( fmt::format( "Found interface: {}", cur.first ) );

					return cur.second.cast<uintptr_t*>();
				}
			}
		}

		/// No valid interface found
		return nullptr;
	}

	uintptr_t* get( const char* mod_name, const char* interface_name )
	{
		/// Was the interface list built successfully?
		if ( !build_interface_list() )
			return nullptr;

		auto& interface_map = get_interface_map();

		/// Get all logged interfaces for this module
		auto& entry = interface_map[ HASH( mod_name ) ];
		if ( entry.empty() )
			return nullptr;

		for ( auto& cur : entry )
		{
			if ( std::string( cur.first ).find( interface_name ) != std::string::npos )
			{
				LOG( fmt::format( "Found interface: {}", cur.first ) );

				return cur.second.cast<uintptr_t*>();
			}
		}

		/// No valid interface found
		return nullptr;
	}
}
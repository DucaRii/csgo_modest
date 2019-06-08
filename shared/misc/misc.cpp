#include "../shared.hpp"

namespace shared::misc
{
	std::string to_utf8( std::wstring_view wstr )
	{
		if ( wstr.empty() )
			return std::string();

		int size_needed = WideCharToMultiByte( CP_UTF8, 0, &wstr[ 0 ], static_cast< int >( wstr.size() ), NULL, 0, NULL, NULL );

		std::string out( size_needed, 0 );
		WideCharToMultiByte( CP_UTF8, 0, &wstr[ 0 ], static_cast< int >( wstr.size() ), &out[ 0 ], size_needed, NULL, NULL );

		return out;
	}

	std::wstring to_unicode( std::string_view str )
	{
		if ( str.empty() )
			return std::wstring();

		int size_needed = MultiByteToWideChar( CP_UTF8, 0, &str[ 0 ], static_cast< int >( str.size() ), NULL, 0 );

		std::wstring out( size_needed, 0 );
		MultiByteToWideChar( CP_UTF8, 0, &str[ 0 ], static_cast< int >( str.size() ), &out[ 0 ], size_needed );

		return out;
	}
}
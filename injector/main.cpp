#include "../shared/shared.hpp"

#include <TlHelp32.h>
#include <iostream>
#include <thread>

/// Simple loadlibrary injector

#define DLL_NAME "csgo_modest.dll"
#define PROCESS_NAME L"csgo.exe"

/// Usage: Either just start the program
///        and it will inject DLL_NAME ( if found )
///        Or you drop a file onto the program and
///        it will inject that file

/// <summary>
/// Loops through all processes and searches for the provided process
/// </summary>
/// <param name="name">Process name to search for</param>
/// <returns>Process ID, 0 if not found</returns>
uint32_t get_process_info( const wchar_t* name )
{
	auto snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

	if ( snapshot == INVALID_HANDLE_VALUE )
		return false;

	auto entry = PROCESSENTRY32{ sizeof( PROCESSENTRY32 ) };

	if ( Process32First( snapshot, &entry ) )
	{
		do
		{
			if ( !wcscmp( entry.szExeFile, name ) )
			{
				CloseHandle( snapshot );
				return entry.th32ProcessID;
			}
		} while ( Process32Next( snapshot, &entry ) );
	}

	CloseHandle( snapshot );
	return 0;
}

/// <summary>
/// Injects a .dll file utilizing kernel32's LoadLibrary function and mapping it into the process
/// </summary>
/// <param name="arg_number">Argument number provided with the call of the function</param>
/// <param name="arguments">Arguments provided with the call of the function</param>
/// <returns>Success of function</returns>
BOOL main( int arg_number, char* arguments[] )
{
	HANDLE process_handle;
	LPVOID path_alloc;
	HANDLE remote_thread;

	auto cleanup = [ & ]() -> void
	{
		if ( path_alloc )
			VirtualFreeEx( process_handle, path_alloc, 0, MEM_RELEASE );

		if ( remote_thread )
			CloseHandle( remote_thread );

		if ( process_handle )
			CloseHandle( process_handle );
	};

	try
	{
		auto file_path = std::wstring( L"" );

		/// Check if the program was called with a custom name
		/// arg number 1 = current file path
		/// arg number 2 = destination file path
		if ( arg_number == 2 )
		{
			file_path = std::filesystem::canonical( arguments[ 1 ] ).wstring();
		}
		else
		{
			file_path = std::filesystem::canonical( DLL_NAME ).wstring();
		}

		/// Check for file existance ( No need for this really since
		/// canonical will handle that but whatever )
		if ( !std::filesystem::exists( file_path ) )
			throw std::runtime_error( "Failed to find target file" );

		/// Check if process exists
		auto process_id = get_process_info( PROCESS_NAME );
		if ( !process_id )
			throw std::runtime_error( "Target process isn't open" );

		/// Now get a handle to the process
		process_handle = OpenProcess( PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD, FALSE, process_id );
		if ( !process_handle )
			throw std::runtime_error( "Failed to open process handle" );

		/// Finally inject the file into the target process

		/// Allocate memory in target process for our file path
		path_alloc = VirtualAllocEx( process_handle, NULL, file_path.size() * 2, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE );
		if ( !path_alloc )
			throw std::runtime_error( "Failed to allocate memory for file path" );

		/// Write the file path into the allocated memory
		if ( !WriteProcessMemory( process_handle, path_alloc, file_path.c_str(), file_path.size() * 2, nullptr ) )
			throw std::runtime_error( "Failed to write dll path into process" );

		/// Now load the dll by calling LoadLIbrary in the target process
		/// with our allocated file path
		remote_thread = CreateRemoteThread( process_handle, NULL, NULL, reinterpret_cast< LPTHREAD_START_ROUTINE >( LoadLibraryW ), path_alloc, NULL, NULL );
		if ( !remote_thread )
			throw std::runtime_error( "Failed to open remote thread" );

		WaitForSingleObject( remote_thread, INFINITE );

		std::cout << "Successfully injected!" << std::endl;

		/// Cleanup memory/handles
		cleanup();

		std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );;
	}
	catch ( const std::runtime_error & err )
	{
		/// Cleanup memory/handles
		cleanup();

		MessageBoxA( NULL, err.what(), "Error", MB_OK | MB_ICONERROR );

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
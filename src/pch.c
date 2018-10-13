// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"

// In general, ignore this file, but keep it around if you are using pre-compiled headers.
#if defined( _WIN32 )
#include "windows.h"

void OutputDbgStr( char* format, ... )
{
	char buffer[ 1024 ];	// Maximum debug output string size.
    va_list args;
    va_start( args, format );

	vsnprintf( buffer, 1024, format, args );
    va_end( args );
	OutputDebugString( buffer );
}
#else
#include <stdarg.h>
void OutputDebugStr( char* format, ... )
{
    va_list args;
    va_start( args, format );

	vfprintf( stderr, format, args );
    va_end( args );
}
#endif

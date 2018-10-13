// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

#include "data.h"
#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include "baseband.h"
#include "bitbuffer.h"
#include "data.h"
#include "util.h"
#if !defined( _WIN32 )
#include <stdarg.h>
#endif

//	And everybody needs the r_device definition.
typedef struct {
	unsigned protocol_num; // fixed sequence number, assigned in main()
	char name[256];
	unsigned int modulation;
	float short_limit;
	float long_limit;
	float reset_limit;
	float gap_limit;
	float sync_width;
	float tolerance;
	int (*json_callback)(bitbuffer_t *bitbuffer);
	unsigned int disabled;
	unsigned demod_arg;	// Decoder specific optional argument
	char **fields;			// List of fields this decoder produces; required for CSV output. NULL-terminated.
} r_device;

/* Supported modulation types */
#define	OOK_PULSE_MANCHESTER_ZEROBIT	3	// Manchester encoding. Hardcoded zerobit. Rising Edge = 0, Falling edge = 1
#define	OOK_PULSE_PCM_RZ		4			// Pulse Code Modulation with Return-to-Zero encoding, Pulse = 0, No pulse = 1
#define	OOK_PULSE_PPM_RAW		5			// Pulse Position Modulation. No startbit removal. Short gap = 0, Long = 1
#define	OOK_PULSE_PWM_PRECISE	6			// Pulse Width Modulation with precise timing parameters
#define	OOK_PULSE_PWM_RAW		7			// DEPRECATED; Pulse Width Modulation. Short pulses = 1, Long = 0
#define	OOK_PULSE_PIWM_RAW     	8			// Level shift for each bit. Short interval = 1, Long = 0
#define	OOK_PULSE_PIWM_DC      	11			// Level shift for each bit. Short interval = 1, Long = 0
#define	OOK_PULSE_DMC       	9			// Level shift within the clock cycle.
#define	OOK_PULSE_PWM_OSV1		10			// Pulse Width Modulation. Oregon Scientific v1

#define	FSK_DEMOD_MIN_VAL		16			// Dummy. FSK demodulation must start at this value
#define	FSK_PULSE_PCM			16			// FSK, Pulse Code Modulation
#define	FSK_PULSE_PWM_RAW		17			// FSK, Pulse Width Modulation. Short pulses = 1, Long = 0
#define FSK_PULSE_MANCHESTER_ZEROBIT 18		// FSK, Manchester encoding

#ifdef _WIN32
	#include <io.h>
	#include <fcntl.h>
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT _WIN32_WINNT_VISTA
	#endif
	#pragma warning( disable : 4244 4090 4305 4267 )
	#pragma comment( lib, "Ws2_32" )
	// Some defines to use proper POSIX function names.
	// These MUST come after the io.h and fcntl.h includes.
	#define access _access
	#define strdup	_strdup
	#define putenv _putenv
	#if defined( x64 )
		#if defined( _DEBUG )
			#pragma comment( lib, "..\\rtlsdr_libs\\x64\\debug\\rtlsdr" )
		#else
			#pragma comment( lib, "..\\rtlsdr_libs\\x64\\release\\rtlsdr" )
		#endif
	#else
		#if defined( _DEBUG )
			#pragma comment( lib, "..\\rtlsdr_libs\\x86\\debug\\rtlsdr" )
		#else
			#pragma comment( lib, "..\\rtlsdr_libs\\x86\\release\\rtlsdr" )
		#endif
	#endif
#endif

extern int debug_output;
extern float sample_file_pos;
void data_acquired_handler(data_t *data);

#endif //PCH_H

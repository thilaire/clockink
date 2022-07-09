/* pure C logger (with macros)
   able to log to serial or to Otii Arc (used for power consumption measurement)

	logInit(bauds, OtiiMode, OtiiRX, OtiiTX);
	logInfo(msg);
	logOtii(msg);
	logDebug(msg);

	Four levels exit:
	- 0: no debug (no messages)
	- 1: `Info` for general messages
	- 2: `Otii` for messages sent to Otii Arc
	- 3:  `debug` for debug (low level) messages
*/


#include <HardwareSerial.h>

#define NO_LOG 		0
#define INFO_LOG	1
#define OTII_LOG	2
#define DEBUG_LOG	3

#ifndef VERBOSITY
#define VERBOSITY INFO_LOG
#endif


/* Info messages (and init) */
#if VERBOSITY >= INFO_LOG
	HardwareSerial OtiiSerial(1);
	#define logInit(a,b,c,d) OtiiSerial.begin(a, b, c, d); Serial.begin(a)
	#define logInfo(msg) Serial.println("INFO: " # msg)
#else
	#define logInit(msg)
	#define logInfo(msg)
#endif

/* OTII messages */
#if VERBOSITY >= OTII_LOG
	#define logOtii(msg) OtiiSerial.println(msg); Serial.println("OTII: " # msg)
#else
	#define logOtii(msg)
#endif

/* Debug messages */
#if VERBOSITY >= DEBUG_LOG
	#define logDebug(msg) Serial.println("DEBUG: " # msg)
#else
	#define logDebug(msg)
#endif




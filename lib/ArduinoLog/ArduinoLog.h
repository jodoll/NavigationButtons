/*
    _   ___ ___  _   _ ___ _  _  ___  _    ___   ___
   /_\ | _ \   \| | | |_ _| \| |/ _ \| |  / _ \ / __|
  / _ \|   / |) | |_| || || .` | (_) | |_| (_) | (_ |
 /_/ \_\_|_\___/ \___/|___|_|\_|\___/|____\___/ \___|

  Log library for Arduino
  version 1.1.1
  https://github.com/thijse/Arduino-Log

Licensed under the MIT License <http://opensource.org/licenses/MIT>.

*/
#pragma once
#include <inttypes.h>
#include <stdarg.h>

// Non standard: Arduino.h also chosen if ARDUINO is not defined. To facilitate use in non-Arduino test environments
#ifndef ARDUINO
#define DISABLE_LOGGING
class Print{};
#elif ARDUINO < 100
	#include "WProgram.h"
#else
	#include "Arduino.h"
#endif

// PGM stubs to facilitate use in non-Arduino test environments
#ifndef PGM_P
#define PGM_P  const char *
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define PSTR(str) (str)
#define F(string_literal) (reinterpret_cast<const __FlashStringHelper *>(PSTR(string_literal)))
#endif
typedef void (*printfunction)(Print*, int);


// *************************************************************************
//  Uncomment line below to fully disable logging, and reduce project size
// ************************************************************************
//#define DISABLE_LOGGING

#define LOG_LEVEL_SILENT  0
#define LOG_LEVEL_FATAL   1
#define LOG_LEVEL_ERROR   2
#define LOG_LEVEL_WARNING 3
#define LOG_LEVEL_INFO    4
#define LOG_LEVEL_NOTICE  4
#define LOG_LEVEL_TRACE   5
#define LOG_LEVEL_VERBOSE 6

#define CR "\n"
#define LOGGING_VERSION 1_0_4

/**
 * Logging is a helper class to output informations over
 * RS232. If you know log4j or log4net, this logging class
 * is more or less similar ;-) <br>
 * Different loglevels can be used to extend or reduce output
 * All methods are able to handle any number of output parameters.
 * All methods print out a formated string (like printf).<br>
 * To reduce output and program size, reduce loglevel.
 * 
 * Output format string can contain below wildcards. Every wildcard
 * must be start with percent sign (\%)
 * 
 * ---- Wildcards
 * 
 * %s	replace with an string (char*)
 * %c	replace with an character
 * %d	replace with an integer value
 * %l	replace with an long value
 * %x	replace and convert integer value into hex
 * %X	like %x but combine with 0x123AB
 * %b	replace and convert integer value into binary
 * %B	like %x but combine with 0b10100011
 * %t	replace and convert boolean value into "t" or "f"
 * %T	like %t but convert into "true" or "false"
 * 
 * ---- Loglevels
 * 
 * 0 - LOG_LEVEL_SILENT     no output
 * 1 - LOG_LEVEL_FATAL      fatal errors
 * 2 - LOG_LEVEL_ERROR      all errors
 * 3 - LOG_LEVEL_WARNING    errors and warnings
 * 4 - LOG_LEVEL_INFO       errors, warnings and notices
 * 4 - LOG_LEVEL_NOTICE     Same as INFO, kept for backward compatibility
 * 5 - LOG_LEVEL_TRACE      errors, warnings, notices, traces
 * 6 - LOG_LEVEL_VERBOSE    all
 */

class Logging
{
public:
	/**
	 * default Constructor
	 */
	Logging()
#ifndef DISABLE_LOGGING
		: _level(LOG_LEVEL_SILENT),
   		  _showLevel(true),
		  _logOutput(NULL)
#endif
	{

	}

	/**
	 * Initializing, must be called as first. Note that if you use
	 * this variant of Init, you need to initialize the baud rate
	 * yourself, if printer happens to be a serial port.
	 * 
	 * \param level - logging levels <= this will be logged.
	 * \param printer - place that logging output will be sent to.
	 * \return void
	 *
	 */
	void begin(int level, Print *output, bool showLevel = true);

	/**
	 * Set the log level.
	 * 
	 * \param level - The new log level.
	 * \return void
	 */
	void setLevel(int level);

	/**
	 * Get the log level.
	 *
	 * \return The current log level.
	 */
	int getLevel() const;

	/**
	 * Set whether to show the log level.
	 * 
	 * \param showLevel - true if the log level should be shown for each log
	 *                    false otherwise.
	 * \return void
	 */
	void setShowLevel(bool showLevel);

	/**
	 * Get whether the log level is shown during logging
	 * 
	 * \return true if the log level is be shown for each log
	 *         false otherwise.
	 */
	bool getShowLevel() const;

	/**
	 * Sets a function to be called before each log command.
	 * 
	 * \param f - The function to be called
	 * \return void
	 */
	void setPrefix(printfunction f);

	/**
     * clears prefix.
     *
     * \return void
     */
	void clearPrefix();

	/**
	 * Sets a function to be called after each log command.
	 * 
	 * \param f - The function to be called
	 * \return void
	 */
	void setSuffix(printfunction f);

	/**
     * clears suffix.
     *
     * \return void
     */
	void clearSuffix();

	/**
	 * Output a fatal error message. Output message contains
	 * F: followed by original message
	 * Fatal error messages are printed out at
	 * loglevels >= LOG_LEVEL_FATAL
	 * 
	 * \param msg format string to output
	 * \param ... any number of variables
	 * \return void
	 */
  template <class T, typename... Args> void fatal(T msg, Args... args){
#ifndef DISABLE_LOGGING
    printLevel(LOG_LEVEL_FATAL, false, msg, args...);
#endif
  }

  template <class T, typename... Args> void fatalln(T msg, Args... args){
#ifndef DISABLE_LOGGING
    printLevel(LOG_LEVEL_FATAL, true, msg, args...);
#endif
  }

	/**
	 * Output an error message. Output message contains
	 * E: followed by original message
	 * Error messages are printed out at
	 * loglevels >= LOG_LEVEL_ERROR
	 * 
	 * \param msg format string to output
	 * \param ... any number of variables
	 * \return void
	 */
  template <class T, typename... Args> void error(T msg, Args... args){
#ifndef DISABLE_LOGGING
    printLevel(LOG_LEVEL_ERROR, false, msg, args...);
#endif
  }
  
   template <class T, typename... Args> void errorln(T msg, Args... args){
#ifndef DISABLE_LOGGING
    printLevel(LOG_LEVEL_ERROR, true, msg, args...);
#endif
  } 
	/**
	 * Output a warning message. Output message contains
	 * W: followed by original message
	 * Warning messages are printed out at
	 * loglevels >= LOG_LEVEL_WARNING
	 * 
	 * \param msg format string to output
	 * \param ... any number of variables
	 * \return void
	 */
  template <class T, typename... Args> void warning(T msg, Args...args){
#ifndef DISABLE_LOGGING
    printLevel(LOG_LEVEL_WARNING, false, msg, args...);
#endif
  }
  
   template <class T, typename... Args> void warningln(T msg, Args...args){
#ifndef DISABLE_LOGGING
    printLevel(LOG_LEVEL_WARNING, true, msg, args...);
#endif
  } 

	/**
	 * Output a notice message. Output message contains
	 * N: followed by original message
	 * Notice messages are printed out at
	 * loglevels >= LOG_LEVEL_NOTICE
	 * 
	 * \param msg format string to output
	 * \param ... any number of variables
	 * \return void
	 */
  template <class T, typename... Args> void notice(T msg, Args...args){
#ifndef DISABLE_LOGGING
    printLevel(LOG_LEVEL_NOTICE, false, msg, args...);
#endif
  }
  
  template <class T, typename... Args> void noticeln(T msg, Args...args){
#ifndef DISABLE_LOGGING
    printLevel(LOG_LEVEL_NOTICE, true, msg, args...);
#endif
  }  

  template <class T, typename... Args> void info(T msg, Args...args) {
#ifndef DISABLE_LOGGING
	  printLevel(LOG_LEVEL_INFO, false, msg, args...);
#endif
  }

  template <class T, typename... Args> void infoln(T msg, Args...args) {
#ifndef DISABLE_LOGGING
	  printLevel(LOG_LEVEL_INFO, true, msg, args...);
#endif
  }

	/**
	 * Output a trace message. Output message contains
	 * N: followed by original message
	 * Trace messages are printed out at
	 * loglevels >= LOG_LEVEL_TRACE
	 * 
	 * \param msg format string to output
	 * \param ... any number of variables
	 * \return void
	*/
  template <class T, typename... Args> void trace(T msg, Args... args){
#ifndef DISABLE_LOGGING
    printLevel(LOG_LEVEL_TRACE, false, msg, args...);
#endif
  }

  template <class T, typename... Args> void traceln(T msg, Args... args){
#ifndef DISABLE_LOGGING
    printLevel(LOG_LEVEL_TRACE, true, msg, args...);
#endif
	}

	/**
	 * Output a verbose message. Output message contains
	 * V: followed by original message
	 * Debug messages are printed out at
	 * loglevels >= LOG_LEVEL_VERBOSE
	 * 
	 * \param msg format string to output
	 * \param ... any number of variables
	 * \return void
	 */
  template <class T, typename... Args> void verbose(T msg, Args... args){
#ifndef DISABLE_LOGGING
    printLevel(LOG_LEVEL_VERBOSE, false, msg, args...);
#endif
  }

  template <class T, typename... Args> void verboseln(T msg, Args... args){
#ifndef DISABLE_LOGGING
    printLevel(LOG_LEVEL_VERBOSE, true, msg, args...);
#endif
  }

private:
#ifndef DISABLE_LOGGING
	void print(const char *format, va_list args);

	void print(const __FlashStringHelper *format, va_list args);

	void print(const Printable& obj, va_list args)
	{
		_logOutput->print(obj);
	}

	void printFormat(const char format, va_list *args);

	template <class T> void printLevel(int level, bool cr, T msg, ...)
	{
		if (level > _level)
		{
			return;
		}
		if (level < LOG_LEVEL_SILENT) 
		{
			level = LOG_LEVEL_SILENT;
		}
			

		if (_prefix != NULL)
		{
			_prefix(_logOutput, level);
		}

		if (_showLevel) {
			static const char levels[] = "FEWITV";
			_logOutput->print(levels[level - 1]);
			_logOutput->print(": ");
		}

		va_list args;
		va_start(args, msg);
		print(msg, args);

		if(_suffix != NULL)
		{
			_suffix(_logOutput, level);
		}
		if (cr)
		{
		    _logOutput->print(CR);
		}
	}

	int _level;
	bool _showLevel;
	Print* _logOutput;

	printfunction _prefix = NULL;
	printfunction _suffix = NULL;
#endif
};

extern Logging Log;
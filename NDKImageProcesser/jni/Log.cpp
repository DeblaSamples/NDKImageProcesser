/*
 * Log.cpp
 *
 *  Created on: 2015-01-31
 *      Author: Cocoonshu
 */

#include "Log.h"
#include "string.h"

void __print_method(const char* methodName) {
#if PRINT_METHOD_DEBUG
	Log_i("[Native][CoPlayer][%s]", methodName);
#endif
}

void __print_method_format(const char* methodName, const char *fmt, ...) {
#if PRINT_METHOD_DEBUG
	int    fmtLength          = strlen(fmt);
	char   methodLogFmt[]     = "[Native][NDKProcesser][%s] ";
	int    methodLogFmtLength = strlen(methodLogFmt);
	char*  logstr             = new char[fmtLength + methodLogFmtLength + 1];

	memset(logstr, 0, fmtLength + methodLogFmtLength + 1);
	strcat(logstr, methodLogFmt);
	strcat(logstr, fmt);

	va_list params;
	va_start(params, fmt);
	Log_i(logstr, methodName, params);
	va_end(params);
#endif
}


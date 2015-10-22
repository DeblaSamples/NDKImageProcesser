/*
 * Log.h
 *
 *  Created on: 2015-01-31
 *      Author: Cocoonshu
 */

#ifndef LOG_H
#define LOG_H

#include <jni.h>
#include "android/log.h"
#define  Log_i(...)             __android_log_print(ANDROID_LOG_INFO,  "NDKProcesser", __VA_ARGS__)
#define  Log_w(...)             __android_log_print(ANDROID_LOG_WARN,  "NDKProcesser", __VA_ARGS__)
#define  Log_e(...)             __android_log_print(ANDROID_LOG_ERROR, "NDKProcesser", __VA_ARGS__)
#define  Log_method_format(...) __print_method_format(__func__, __VA_ARGS__)
#define  Log_method()           __print_method(__func__)

void __print_method(const char* methodName);
void __print_method_format(const char* methodName, const char *fmt, ...);

#endif

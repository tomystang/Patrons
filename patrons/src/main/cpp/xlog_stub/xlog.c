//
// Created by tomystang on 2022/6/7.
//

#include <stdbool.h>
#include <unistd.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdatomic.h>
#include "xlog.h"

#define UNLIKELY(cond) __builtin_expect(!!(cond), 0)

#define XLOG_SO_MISSING_MASK 0x1
#define XLOG_SO_LOADED_MASK 0x2
static atomic_char s_xlog_status = ATOMIC_VAR_INIT(0);

static void* s_xlog_handle = NULL;
static bool (*s_xlogger_IsEnabledFor_impl)(TLogLevel) = NULL;
static void (*s_xlogger_VPrint_impl)(const XLoggerInfo*, const char*, va_list) = NULL;

static inline void* lookup_xlog_function(const char* func_name) {
    char xlog_status = atomic_load(&s_xlog_status);
    if (UNLIKELY((xlog_status & XLOG_SO_MISSING_MASK) != 0)) {
        return NULL;
    }
    if (UNLIKELY((xlog_status & XLOG_SO_LOADED_MASK) == 0)) {
        s_xlog_handle = dlopen("libwechatxlog.so", RTLD_NOW);
        if (s_xlog_handle != NULL) {
            atomic_store(&s_xlog_status, xlog_status | XLOG_SO_LOADED_MASK);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, "Patrons.LogStub", "Missing libwechatxlog.so.");
            atomic_store(&s_xlog_status, xlog_status | XLOG_SO_MISSING_MASK);
            return NULL;
        }
    }
    return dlsym(s_xlog_handle, func_name);
}


static inline bool IsEnabledFor(TLogLevel level) {
    if (UNLIKELY(s_xlogger_IsEnabledFor_impl == NULL)) {
        s_xlogger_IsEnabledFor_impl = lookup_xlog_function("xlogger_IsEnabledFor");
    }
    if (s_xlogger_IsEnabledFor_impl) {
        return s_xlogger_IsEnabledFor_impl(level);
    } else {
        return false;
    }
}

void __ComLogV(int level, const char *tag, const char* file, const char* func, int line, const char* fmt, va_list args) {
    if (UNLIKELY(s_xlogger_VPrint_impl == NULL)) {
        s_xlogger_VPrint_impl = lookup_xlog_function("xlogger_VPrint");
    }
    if (s_xlogger_VPrint_impl) {
        if (IsEnabledFor(level)) {
            struct XLoggerInfo_t info;
            info.m_level = (TLogLevel) level;
            info.m_tag = tag;
            info.m_filename = file;
            info.m_funcname = func;
            info.m_line = line;

            gettimeofday(&info.m_tv, NULL);
            info.m_pid = getpid();
            info.m_tid = gettid();
            info.m_maintid = -1;

            s_xlogger_VPrint_impl(&info, fmt, args);
        }
    } else {
        __android_log_vprint(level + 2, tag, fmt, args);
    }
}
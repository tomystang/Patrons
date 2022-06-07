//
// Created by tomystang on 2022/6/7.
//

#ifndef ABORT_KILLER_XLOG_H
#define ABORT_KILLER_XLOG_H


#include <sys/time.h>
#include <time.h>

typedef enum {
    ELevelAll = 0,
    ELevelVerbose = 0,
    ELevelDebug,    // Detailed information on the flow through the system.
    ELevelInfo,     // Interesting runtime events (startup/shutdown), should be conservative and keep to a minimum.
    ELevelWarn,     // Other runtime situations that are undesirable or unexpected, but not necessarily "wrong".
    ELevelError,    // Other runtime errors or unexpected conditions.
    ELevelFatal,    // Severe errors that cause premature termination.
    ELevelNone,     // Special level used to disable all log messages.
} TLogLevel;

typedef struct XLoggerInfo_t {
    TLogLevel m_level;
    const char* m_tag;
    const char* m_filename;
    const char* m_funcname;
    int m_line;

    struct timeval m_tv;
    intmax_t m_pid;
    intmax_t m_tid;
    intmax_t m_maintid;
} XLoggerInfo;

void __ComLogV(int level, const char *tag, const char* file, const char* func, int line, const char* fmt, va_list args);

static inline void __ComLog(int level, const char* tag, const char* file, const char* func, int line, const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	__ComLogV(level, tag, file, func, line, fmt, args);
	va_end(args);
}

#ifdef XLOGV
#undef XLOGV
#endif
#define XLOGV(tag, fmt, args...) do { __ComLog(ELevelVerbose, tag, __FILE__, __func__, __LINE__, fmt, ##args); } while (0)

#ifdef XLOGD
#undef XLOGD
#endif
#define XLOGD(tag, fmt, args...) do { __ComLog(ELevelDebug, tag, __FILE__, __func__, __LINE__, fmt, ##args); } while (0)

#ifdef XLOGI
#undef XLOGI
#endif
#define XLOGI(tag, fmt, args...) do { __ComLog(ELevelInfo, tag, __FILE__, __func__, __LINE__, fmt, ##args); } while (0)

#ifdef XLOGW
#undef XLOGW
#endif
#define XLOGW(tag, fmt, args...) do { __ComLog(ELevelWarn, tag, __FILE__, __func__, __LINE__, fmt, ##args); } while (0)

#ifdef XLOGE
#undef XLOGE
#endif
#define XLOGE(tag, fmt, args...) do { __ComLog(ELevelError, tag, __FILE__, __func__, __LINE__, fmt, ##args); } while (0)


#endif //ABORT_KILLER_XLOG_H

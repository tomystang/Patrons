package com.alibaba.android.patronus.util;

import static android.util.Log.DEBUG;
import static android.util.Log.ERROR;
import static android.util.Log.INFO;
import static android.util.Log.VERBOSE;
import static android.util.Log.WARN;

import java.util.Locale;

/**
 * Created by tomystang on 2022/6/6.
 */
public final class Log {
    private static ILogger sLogger;

    public interface ILogger {
        void println(int priority, String tag, String msg);
    }

    public static final ILogger DEFAULT_LOGGER = new ILogger() {
        @Override
        public void println(int priority, String tag, String msg) {
            android.util.Log.println(priority, tag, msg);
        }
    };

    static {
        sLogger = DEFAULT_LOGGER;
    }

    public static ILogger setLogger(ILogger logger) {
        if (sLogger == logger) {
            return logger;
        }
        final ILogger prevLogger = sLogger;
        sLogger = logger;
        return prevLogger;
    }

    public static void v(String tag, String msg) {
        if (sLogger != null) {
            sLogger.println(VERBOSE, tag, msg);
        }
    }

    public static void v(String tag, String fmt, Object... args) {
        if (sLogger != null) {
            sLogger.println(VERBOSE, tag, String.format(Locale.ENGLISH, fmt, args));
        }
    }

    public static void v(String tag, Throwable thr, String msg) {
        if (sLogger != null) {
            sLogger.println(VERBOSE, tag, msg + '\n' + android.util.Log.getStackTraceString(thr));
        }
    }

    public static void v(String tag, Throwable thr, String fmt, Object... args) {
        if (sLogger != null) {
            sLogger.println(VERBOSE, tag, String.format(Locale.ENGLISH, fmt, args) + '\n' + android.util.Log.getStackTraceString(thr));
        }
    }

    public static void d(String tag, String msg) {
        if (sLogger != null) {
            sLogger.println(DEBUG, tag, msg);
        }
    }

    public static void d(String tag, String fmt, Object... args) {
        if (sLogger != null) {
            sLogger.println(DEBUG, tag, String.format(Locale.ENGLISH, fmt, args));
        }
    }

    public static void d(String tag, Throwable thr, String msg) {
        if (sLogger != null) {
            sLogger.println(DEBUG, tag, msg + '\n' + android.util.Log.getStackTraceString(thr));
        }
    }

    public static void d(String tag, Throwable thr, String fmt, Object... args) {
        if (sLogger != null) {
            sLogger.println(DEBUG, tag, String.format(Locale.ENGLISH, fmt, args) + '\n' + android.util.Log.getStackTraceString(thr));
        }
    }

    public static void i(String tag, String msg) {
        if (sLogger != null) {
            sLogger.println(INFO, tag, msg);
        }
    }

    public static void i(String tag, String fmt, Object... args) {
        if (sLogger != null) {
            sLogger.println(INFO, tag, String.format(Locale.ENGLISH, fmt, args));
        }
    }

    public static void i(String tag, Throwable thr, String msg) {
        if (sLogger != null) {
            sLogger.println(INFO, tag, msg + '\n' + android.util.Log.getStackTraceString(thr));
        }
    }

    public static void i(String tag, Throwable thr, String fmt, Object... args) {
        if (sLogger != null) {
            sLogger.println(INFO, tag, String.format(Locale.ENGLISH, fmt, args) + '\n' + android.util.Log.getStackTraceString(thr));
        }
    }

    public static void w(String tag, String msg) {
        if (sLogger != null) {
            sLogger.println(WARN, tag, msg);
        }
    }

    public static void w(String tag, String fmt, Object... args) {
        if (sLogger != null) {
            sLogger.println(WARN, tag, String.format(Locale.ENGLISH, fmt, args));
        }
    }

    public static void w(String tag, Throwable thr, String msg) {
        if (sLogger != null) {
            sLogger.println(WARN, tag, msg + '\n' + android.util.Log.getStackTraceString(thr));
        }
    }

    public static void w(String tag, Throwable thr, String fmt, Object... args) {
        if (sLogger != null) {
            sLogger.println(WARN, tag, String.format(Locale.ENGLISH, fmt, args) + '\n' + android.util.Log.getStackTraceString(thr));
        }
    }

    public static void e(String tag, String msg) {
        if (sLogger != null) {
            sLogger.println(ERROR, tag, msg);
        }
    }

    public static void e(String tag, String fmt, Object... args) {
        if (sLogger != null) {
            sLogger.println(ERROR, tag, String.format(Locale.ENGLISH, fmt, args));
        }
    }

    public static void e(String tag, Throwable thr, String msg) {
        if (sLogger != null) {
            sLogger.println(ERROR, tag, msg + '\n' + android.util.Log.getStackTraceString(thr));
        }
    }

    public static void e(String tag, Throwable thr, String fmt, Object... args) {
        if (sLogger != null) {
            sLogger.println(ERROR, tag, String.format(Locale.ENGLISH, fmt, args) + '\n' + android.util.Log.getStackTraceString(thr));
        }
    }
}

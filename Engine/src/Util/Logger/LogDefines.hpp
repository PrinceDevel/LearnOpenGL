#pragma once

#define LOG_WARN_ENABLED 
#define LOG_INFO_ENABLED 
#define LOG_DEBUG_ENABLED
#define LOG_TRACE_ENABLED

#ifdef _CONFIG_RELEASE
#undef LOG_DEBUG_ENABLED
#undef LOG_TRACE_ENABLED
#endif

#define COLOR_DEFAULT "\u001b[0m"

#ifdef DarkModeEnabled
#define COLOR_BLACK     "\u001b[30m"        // Dark Black
#define COLOR_RED       "\u001b[31m"        // Dark Red
#define COLOR_GREEN     "\u001b[32m"        // Dark Green
#define COLOR_YELLOW    "\u001b[33m"        // Dark Yellow
#define COLOR_BLUE      "\u001b[34m"        // Dark Blue
#define COLOR_MAGENTA   "\u001b[35m"        // Dark Magenta
#define COLOR_CYAN      "\u001b[36m"        // Dark Cyan
#define COLOR_WHITE     "\u001b[37m"        // Dark White
#else
#define COLOR_BLACK     "\u001b[30;1m"      // Light Black
#define COLOR_RED       "\u001b[31;1m"      // Light Red
#define COLOR_GREEN     "\u001b[32;1m"      // Light Green
#define COLOR_YELLOW    "\u001b[33;1m"      // Light Yellow
#define COLOR_BLUE      "\u001b[34;1m"      // Light Blue
#define COLOR_MAGENTA   "\u001b[35;1m"      // Light Magenta
#define COLOR_CYAN      "\u001b[36;1m"      // Light Cyan
#define COLOR_WHITE     "\u001b[37;1m"      // Light White
#endif
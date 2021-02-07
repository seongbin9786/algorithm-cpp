#ifndef logger
#define logger

#include "trigger.hpp"

#ifndef DEBUG_MODE
#define debug(fmt, args...)
#define debugLine(fmt, args...)
#else
#define debug(fmt, args...) printf("[debug] " fmt, ##args)
#define debugLine(fmt, args...) printf("[debug] [%s %d]" fmt, __FILE__, __LINE__, ##args)
#endif

#endif

#ifndef debugopen
#define debugopen

#include "trigger.hpp"

#include <stdio.h>

#ifndef DEBUG_MODE
#define READ_TXT(args...)
#else
#define READ_TXT(filename, args...) freopen(filename, ##args) // 왜 되는거야?
#endif

#endif

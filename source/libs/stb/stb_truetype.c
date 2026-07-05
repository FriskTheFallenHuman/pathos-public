// this source file includes the implementation of stb_truetype
// having it in a separate source file allows optimizing it in debug builds (for faster load times)
// without hurting the debugability of the source files it's used in

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
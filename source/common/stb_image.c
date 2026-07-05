// this source file includes the implementation of stb_image
// having it in a separate source file allows optimizing it in debug builds (for faster load times)
// without hurting the debugability of the source files it's used in

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
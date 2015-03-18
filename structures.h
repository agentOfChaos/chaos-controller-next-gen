#include "constants.h"
typedef union {
        int val;
        char chars[sizeof(int)];
}poison;

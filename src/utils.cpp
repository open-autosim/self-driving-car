#include "utils.h"

float Utils::lerp(float a, float b, float t) {
    return a + t * (b - a);
}

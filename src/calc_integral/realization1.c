//
// Created by sakost on 27.11.2020.
//

#include <math.h>

#include "realization.h"


float SinIntegral(float A, float B, float e){
    float step = e;
    int count = (int)((B - A) / step);

    float ans = 0;
    for (int i = 0; i <= count; i++) {
        ans += step * sinf(A + (float)(i - 1) * step);
    }
    return ans;
}


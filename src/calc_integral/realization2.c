//
// Created by sakost on 27.11.2020.
//

#include "realization.h"

#include <math.h>

float SinIntegral(float A, float B, float e){
    int n = (int)((B - A) / e);

    float h = (B-A)/(float)n;

    float s = sinf(A)+sinf(B);

    for (int i = 1; i < n; i++)
        s += 2*sinf(A+(float)i*h);

    return h*s/2;
}
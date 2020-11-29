//
// Created by sakost on 27.11.2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


typedef enum {
    INTEGRAL,
    TRANSLATE_NUMBER,
} CONTEXT;

CONTEXT r = INTEGRAL;

const char* integralLibName1 = "libcalc_integral1.so";
const char* integralLibName2 = "libcalc_integral2.so";

const char* translateNumberLibName1 = "libtranslate_number1.so";
const char* translateNumberLibName2 = "libtranslate_number2.so";

float (*sinInt1)(float, float, float) = NULL;
float (*sinInt2)(float, float, float) = NULL;
char* (*translation1)(long x) = NULL;
char* (*translation2)(long x) = NULL;
char *err;

void *libHandle1 = NULL, *libHandle2 = NULL;

void loadDLibs(CONTEXT context){
    const char *name1, *name2;
    if(context == INTEGRAL){
        name1 = integralLibName1;
        name2 = integralLibName2;
    } else{
        name1 = translateNumberLibName1;
        name2 = translateNumberLibName2;
    }

    libHandle1 = dlopen(name1, RTLD_LAZY);
    if(!libHandle1){
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    libHandle2 = dlopen(name2, RTLD_LAZY);
    if(!libHandle2){
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
}

void unloadDLibs(){
    dlclose(libHandle1);
    dlclose(libHandle2);
}

void loadContext(){
    loadDLibs(r);
    if(r == TRANSLATE_NUMBER){
        sinInt1 = sinInt2 = NULL;
        translation1 = dlsym(libHandle1, "translation");
        translation2 = dlsym(libHandle2, "translation");

    } else{
        translation1 = translation2 = NULL;
        sinInt1 = dlsym(libHandle1, "SinIntegral");
        sinInt2 = dlsym(libHandle2, "SinIntegral");
    }
    if((err = dlerror())) {
        fprintf(stderr, "%s\n", err);
        exit(EXIT_FAILURE);
    }
}

void changeContext(){
    unloadDLibs();
    if(r == INTEGRAL){
        r = TRANSLATE_NUMBER;
    } else {
        r = INTEGRAL;
    }

    loadContext();
}

int main(){
    r = TRANSLATE_NUMBER;
    loadContext();

    int cmd = 0;

    while (scanf("%d", &cmd) != EOF){

        if(cmd == 0){
            changeContext();
            puts("Ok. Contract was changed");
            if(r == INTEGRAL){
                puts("Now context is integral");
            } else{
                puts("Now context is translation");
            }
            continue;
        }
        if(r == INTEGRAL){
            float a, b, c;
            if(scanf("%f %f %f", &a, &b, &c)== EOF){
                break;
            }

            if(cmd == 1){
                puts("Calculate sin(x) integral by rectangle method");
                printf("%f\n", sinInt1(a, b, c));
            } else{
                puts("Calculate sin(x) integral by trapezoidal method");
                printf("%f\n", sinInt2(a, b, c));
            }
        } else{
            long x;
            if(scanf("%ld", &x)== EOF){
                break;
            }

            char *string;
            if(cmd == 1){
                printf("Translate integer(%ld) from 10 base to 2 base\n", x);
                string = translation1(x);
            } else{
                printf("Translate integer(%ld) from 10 base to 3 base\n", x);
                string = translation2(x);
            }
            printf("%s\n", string);
            free(string);
        }
    }
    unloadDLibs();
}
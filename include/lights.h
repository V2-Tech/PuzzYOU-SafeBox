#pragma once

#include <Arduino.h>

#define L1_YL 12
#define L1_GN 11
#define L2_YL 10
#define L2_GN 9
#define L3_YL 14
#define L3_GN 15
#define L4_YL 16
#define L4_GN 17

class Lights
{
public:
    Lights(){};
    ~Lights(){};

    void begin(void);

private:
    
};
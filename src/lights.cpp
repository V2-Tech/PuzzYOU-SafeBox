#include "lights.h"

void Lights::begin(void)
{
    Serial.println(F("Lights Initialization"));

    pinMode(L1_GN, OUTPUT);
    pinMode(L1_YL, OUTPUT);
    pinMode(L2_GN, OUTPUT);
    pinMode(L2_YL, OUTPUT);
    pinMode(L3_GN, OUTPUT);
    pinMode(L3_YL, OUTPUT);
    pinMode(L4_GN, OUTPUT);
    pinMode(L4_YL, OUTPUT);

    Serial.println(F("Lights Initialization completed"));
}

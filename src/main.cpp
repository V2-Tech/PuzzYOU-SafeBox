#include <Arduino.h>
#include "safeduino.h"

// Access the singleton instances
Safeduino puzzle;

void setup()
{
  Serial.begin(19200);

  Serial.println(F("Puzzle initialization"));

  puzzle.begin();

  Serial.println(F("Puzzle initialization completed"));
}

void loop()
{
  puzzle.run();
}


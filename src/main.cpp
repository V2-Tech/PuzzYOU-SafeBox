#include <Arduino.h>
#include "safebox.h"

// Access the singleton instances
Safebox puzzle;

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


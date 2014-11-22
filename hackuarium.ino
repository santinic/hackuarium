/*
 * FishController
 * Alan Zucconi, Claudio Santini, Satan
 */
 
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

#include <IRremote.h>
#include "Arduino.h"
#include "Fish.h"
#include "fishes.h"
#include "rest.h"

void setup()
{
  //pinMode(3, OUTPUT);
  Serial.begin(9600);
  
  // Initialise fishes
  fishes[0] = new Fish(
    fish_0_up,
    fish_0_down,
    fish_0_left,
    fish_0_right,
    fish_0_stop,
    fish_0_codeLen
  );
  fishes[1] = new Fish
  (
    fish_1_up,
    fish_1_down,
    fish_1_left,
    fish_1_right,
    fish_1_stop,
    fish_1_codeLen
  );
}


void testLoop() {
      Serial.print("UP...");
    fishes[0]->command(UP, 100);
    Serial.println(" ...done!");
    
    delay(1000);
    
    Serial.print("DOWN...");
    fishes[0]->command(DOWN, 100);
    Serial.println(" ...done!");
    
    delay(1000);
    
     Serial.print("UP...");
    fishes[1]->command(UP, 100);
    Serial.println(" ...done!");
    
    delay(1000);
    
    Serial.print("DOWN...");
    fishes[1]->command(DOWN, 100);
    Serial.println(" ...done!");
    
    delay(1000);
}

void loop() 
{ 
    restLoop();   
}

#include "every.h"


void setup() {
  Serial.begin(9600);

  Serial.println("start...");
}

void loop() {
  every(3000) {
    Serial.println("3000");
  }

  every(4000) {
    Serial.println("4000");
  }
}

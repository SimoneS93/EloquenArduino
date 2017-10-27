#ifndef ELOQUENT_EVERY_H
#define ELOQUENT_EVERY_H 1


/**
 * Eloquent every
 * Execute code periodically.
 * 
 * You can have multiple timers in your loop, the only restriction is the interval be a valid identifier.
 * This means (almost) they must be numeric constants or single variables.
 * 
 * EXAMPLES:
 * 
 * void loop() {
 *    int interval = 3000;
 *    
 *    every(1000) {
 *        Serial.println("Every 1 second");
 *    }
 *    
 *    every(interval) {
 *        Serial.println("Every 3 seconds");
 *    }
 *  }
 */

// run code periodically, every $interval milliseconds
#define every(interval) static unsigned long __every__##interval = millis(); \
  if (millis() - __every__##interval >= interval && (__every__##interval = millis()))

#endif


#ifndef ELOQUENT_EVERY_H
#define ELOQUENT_EVERY_H 1


// run code periodically, every $interval milliseconds
#define every(interval) static unsigned long __every__##interval = millis(); \
  if (millis() - __every__##interval >= interval && (__every__##interval = millis()))

#endif


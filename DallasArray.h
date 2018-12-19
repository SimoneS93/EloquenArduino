/*
	DallasArray

	Handle multiple Dallas DS1820 temperature sensors with ease

	Created 19/12/2018
	By Simone Salerno

	https://github.com/SimoneS93/EloquentArduino

*/

#pragma once
#include <Arduino.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

#ifndef DALLAS_ARRAY_MAX_COUNT
#define DALLAS_ARRAY_MAX_COUNT 10
#endif


/**
 * 
 */
class DallasArray {
  public:
    DallasArray(uint8_t pin, uint8_t count = 0) : _wire(pin), _sensors(&_wire) {
      _count = count;
    }

    void begin() {
      _sensors.begin();

      if (_count == 0) {
        uint8_t address[8];
        
        while (_wire.search(address))
          _count++;
      }
    }

    uint8_t count() {
      return _count;
    }

    /**
     * You MUST call read() BEFORE any getter
     */
    void read() {
      _sensors.requestTemperatures();

      for (uint8_t i = 0; i < _count; i++)
        _readings[i] = _sensors.getTempCByIndex(i);
    }

    float at(uint8_t index) {
      return index < _count ? _readings[index] : sqrt(-1);
    }

    float getMin() {
      return reduce([](float minimum, float current) { return min(minimum, current); }, _readings[0]);
    }

    float getMax() {
      return reduce([](float maximum, float current) { return max(maximum, current); }, _readings[0]);
    }

    float getAvg() {
      return reduce([](float accumulator, float current) { return accumulator + current; }, 0) / _count;
    }

    float reduce(float (*reducer)(float reduced, float current), float initial) {
      for (uint8_t i = 0; i < _count; i++)
        initial = reducer(initial, _readings[i]);

      return initial;
    }

  private:
    uint8_t _count;
    float _readings[DALLAS_ARRAY_MAX_COUNT];
    OneWire _wire;
    DallasTemperature _sensors;
};

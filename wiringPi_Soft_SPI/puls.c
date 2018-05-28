#include "puls.h"
#include "wiringPi.h"

void tic_delay(uint32_t cycle_count)
{
  uint32_t count=0;
  for(count=0;count<cycle_count;count++)
  {
    __asm volatile ("nop");
  }
}

void pin_pulse_hi_low(uint16_t GPIO_Pin, uint32_t delay)
{
  pinMode(GPIO_Pin, OUTPUT);
  digitalWrite(GPIO_Pin, HIGH);
  tic_delay(delay);
  digitalWrite(GPIO_Pin, LOW);
  tic_delay(delay);
}

void pin_pulse_low_hi(uint16_t GPIO_Pin, uint32_t delay)
{
  pinMode(GPIO_Pin, OUTPUT);
  digitalWrite(GPIO_Pin, LOW);
  tic_delay(delay);
  digitalWrite(GPIO_Pin, HIGH);
  tic_delay(delay);
}


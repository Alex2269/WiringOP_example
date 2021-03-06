/*
 * 2018, Alex226 - gnom.
 * https://github.com/Alex2269/stm32_soft_spi
 * license GPL
*/

#include "wiringSoftSpi.h"
#include "wiringPi.h"

uint8_t clock_polar;
uint8_t clock_phase;

uint32_t _delay;
uint8_t _order;

void delay_tics(uint32_t tics)
{
  uint32_t count=0;
  for(count=0;count<tics;count++)
  {
    __asm volatile ("nop");
  }
}

void soft_spi_init(void)
{
  _delay = 2;
  clock_phase = 0;
  clock_polar = 0;
}

void soft_spi_begin(void)
{
  pinMode(MOSI, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(CLK, OUTPUT);
  pinMode(CS, OUTPUT);
}

void soft_spi_end(void)
{
  pinMode(MOSI, INPUT);
  pinMode(MISO, INPUT);
  pinMode(CLK, INPUT);
  pinMode(CS, INPUT);
}

void soft_spi_set_bit_order(uint8_t order)
{
  switch (order)
  {
    case SPI_LSB_FIRST:
    _order = SPI_LSB_FIRST;
    break;
    case SPI_MSB_FIRST:
    _order = SPI_MSB_FIRST;
    break;
  }
}

void soft_spi_set_data_mode(uint8_t mode)
{
  switch (mode)
  {
    case SPI_MODE0:
    clock_polar = 0;
    clock_phase = 0;
    break;
    case SPI_MODE1:
    clock_polar = 0;
    clock_phase = 1;
    break;
    case SPI_MODE2:
    clock_polar = 1;
    clock_phase = 0;
    break;
    case SPI_MODE3:
    clock_polar = 1;
    clock_phase = 1;
    break;
  }
}

void soft_spi_set_clock_divider(uint32_t div)
{
    _delay = div;
}

uint8_t soft_spi_transfer(uint8_t val)
{
  uint8_t out = 0;
  if (_order == SPI_MSB_FIRST)
  {
    uint8_t v2 =
    ((val & 0x01) << 7) |
    ((val & 0x02) << 5) |
    ((val & 0x04) << 3) |
    ((val & 0x08) << 1) |
    ((val & 0x10) >> 1) |
    ((val & 0x20) >> 3) |
    ((val & 0x40) >> 5) |
    ((val & 0x80) >> 7);
    val = v2;
  }
  uint32_t del = _delay >> 1;
  uint8_t bval = 0;
  for (uint8_t bit = 0; bit < 8; bit++)
  {
    clock_polar ? digitalWrite(CLK, HIGH) : digitalWrite(CLK, LOW);
    delay_tics(del);
    if (clock_phase)
    {
      bval = digitalRead(MISO);
      if (_order == SPI_MSB_FIRST)
      {
        out <<= 1;
        out |= bval;
      }
      else
      {
        out >>= 1;
        out |= bval << 7;
      }
    }
    else
    {
      (val & (1<<bit)) ? digitalWrite(MOSI, HIGH) : digitalWrite(MOSI, LOW);
    }
    delay_tics(del);
    clock_polar ? digitalWrite(CLK, LOW) : digitalWrite(CLK, HIGH);
    delay_tics(del);
    if (clock_phase)
    {
      (val & (1<<bit)) ? digitalWrite(MOSI, HIGH) : digitalWrite(MOSI, LOW);
    }
    else
    {
      bval = digitalRead(MISO);
      if (_order == SPI_MSB_FIRST)
      {
        out <<= 1;
        out |= bval;
      }
      else
      {
        out >>= 1;
        out |= bval << 7;
      }
    }
    delay_tics(del);
  }
  return out;
}

uint16_t soft_spi_transfer16(uint16_t val)
{
  uint16_t out = 0;
  if (_order == SPI_MSB_FIRST)
  {
    uint16_t v2 =
    ((val & 0x01) << 15)  |
    ((val & 0x02) << 13)  |
    ((val & 0x04) << 11)  |
    ((val & 0x08) << 9)   |
    ((val & 0x10) << 7)   |
    ((val & 0x20) << 5)   |
    ((val & 0x40) << 3)   |
    ((val & 0x80) << 1)   |
    ((val & 0x100) >> 1)  |
    ((val & 0x200) >> 3)  |
    ((val & 0x400) >> 5)  |
    ((val & 0x800) >> 7)  |
    ((val & 0x1000) >> 9) |
    ((val & 0x2000) >> 11)|
    ((val & 0x4000) >> 13)|
    ((val & 0x8000) >> 15);
    val = v2;
  }
  uint32_t del = _delay >> 1;
  uint16_t bval = 0;
  for (uint16_t bit = 0; bit < 16; bit++)
  {
    clock_polar ? digitalWrite(CLK, HIGH) : digitalWrite(CLK, LOW);
    delay_tics(del);
    if (clock_phase)
    {
      bval = digitalRead(MISO);
      if (_order == SPI_MSB_FIRST)
      {
        out <<= 1;
        out |= bval;
      }
      else
      {
        out >>= 1;
        out |= bval << 15;
      }
    }
    else
    {
      (val & (1<<bit)) ? digitalWrite(MOSI, HIGH) : digitalWrite(MOSI, LOW);
    }
    delay_tics(del);
    clock_polar ? digitalWrite(CLK, LOW) : digitalWrite(CLK, HIGH);
    delay_tics(del);
    if (clock_phase)
    {
      (val & (1<<bit)) ? digitalWrite(MOSI, HIGH) : digitalWrite(MOSI, LOW);
    }
    else
    {
      bval = digitalRead(MISO);
      if (_order == SPI_MSB_FIRST)
      {
        out <<= 1;
        out |= bval;
      }
      else
      {
        out >>= 1;
        out |= bval << 15;
      }
    }
    delay_tics(del);
  }
  return out;
}

void soft_spi_write(uint16_t val)
{
  if (_order == SPI_MSB_FIRST)
  {
    uint16_t v2 =
    ((val & 0x01) << 7) |
    ((val & 0x02) << 5) |
    ((val & 0x04) << 3) |
    ((val & 0x08) << 1) |
    ((val & 0x10) >> 1) |
    ((val & 0x20) >> 3) |
    ((val & 0x40) >> 5) |
    ((val & 0x80) >> 7);
    val = v2;
  }
  uint32_t del = _delay >> 1;
  for (uint16_t bit = 0; bit < 8; bit++)
  {
    clock_polar ? digitalWrite(CLK, HIGH) : digitalWrite(CLK, LOW);
    delay_tics(del);
    (val & (1<<bit)) ? digitalWrite(MOSI, HIGH) : digitalWrite(MOSI, LOW);
    delay_tics(del);
    clock_polar ? digitalWrite(CLK, LOW) : digitalWrite(CLK, HIGH);
    delay_tics(del);
    (val & (1<<bit)) ? digitalWrite(MOSI, HIGH) : digitalWrite(MOSI, LOW);
    delay_tics(del);
  }
}

void soft_spi_write16(uint16_t val)
{
  if (_order == SPI_MSB_FIRST)
  {
    uint16_t v2 =
    ((val & 0x01) << 15)  |
    ((val & 0x02) << 13)  |
    ((val & 0x04) << 11)  |
    ((val & 0x08) << 9)   |
    ((val & 0x10) << 7)   |
    ((val & 0x20) << 5)   |
    ((val & 0x40) << 3)   |
    ((val & 0x80) << 1)   |
    ((val & 0x100) >> 1)  |
    ((val & 0x200) >> 3)  |
    ((val & 0x400) >> 5)  |
    ((val & 0x800) >> 7)  |
    ((val & 0x1000) >> 9) |
    ((val & 0x2000) >> 11)|
    ((val & 0x4000) >> 13)|
    ((val & 0x8000) >> 15);
    val = v2;
  }
  uint32_t del = _delay >> 1;
  for (uint16_t bit = 0; bit < 16; bit++)
  {
    clock_polar ? digitalWrite(CLK, HIGH) : digitalWrite(CLK, LOW);
    delay_tics(del);
    (val & (1<<bit)) ? digitalWrite(MOSI, HIGH) : digitalWrite(MOSI, LOW);
    delay_tics(del);
    clock_polar ? digitalWrite(CLK, LOW) : digitalWrite(CLK, HIGH);
    delay_tics(del);
    (val & (1<<bit)) ? digitalWrite(MOSI, HIGH) : digitalWrite(MOSI, LOW);
    delay_tics(del);
  }
}

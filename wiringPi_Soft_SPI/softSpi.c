/*
 * pwm.c:
 *	This tests the hardware PWM channel.
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <wiringSoftSpi.h>
#include <wiringPi.h>
#include <puls.h>

//#define CS 5

int main (void)
{
  if (wiringPiSetup () == -1)
    exit (1) ;

  soft_spi_begin();
  // soft_spi_end();
  soft_spi_set_bit_order(SPI_MSB_FIRST);
  soft_spi_set_data_mode(SPI_MODE0);
  soft_spi_set_clock_divider(SPI_CLOCK_DIV2);

  while (1)
  {
    for(uint16_t i =0;i<30;i++)
    {
      digitalWrite(CS, LOW);
      soft_spi_transfer(i);
      //soft_spi_write(i);
      digitalWrite(CS, HIGH);
      //pin_pulse_low_hi(CS, SPI_CLOCK_DIV2);
      delayMicroseconds(5);
    }
    delayMicroseconds(250);
  }

  return 0 ;
}

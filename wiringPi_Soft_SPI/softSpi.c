#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <wiringSoftSpi.h>
#include <wiringPi.h>
#include <puls.h>

#include "ILI9341.h"
#include "wiringSoftSpi.h"
#include "custom/utoa.h"

#define M_PI 3.14159

void fill_text(void)
{
  ILI9341_setTextBgColor(ILI9341_BLACK);

  ILI9341_setCursor(10, 15);
  ILI9341_setTextSize(2);
  ILI9341_setTextColor(ILI9341_CYAN);
  char lb_real[16] = " bar ";
  ILI9341_writeString(lb_real);

  ILI9341_setCursor(160, 15);
  ILI9341_setTextSize(2);
  ILI9341_setTextColor(ILI9341_CYAN);
  char lb_max[16] = " Max ";
  ILI9341_writeString(lb_max);
}

int main (void)
{
  if (wiringPiSetup () == -1)
    exit (1) ;

  lcd_set_pins();
  lcd_reset();
  soft_spi_set_bit_order(SPI_MSB_FIRST);
  soft_spi_set_data_mode(SPI_MODE0);
  soft_spi_set_clock_divider(SPI_CLOCK_DIV2);
  ILI9341_begin(/*&hspi1*/);

  ILI9341_setRotation(0); // clear display & draw grid
  ILI9341_fillScreen(ILI9341_BLACK);
  ILI9341_setRotation(3);
  ILI9341_fillScreen(ILI9341_BLUE);
 
  for(uint16_t i = 5; i<320; i+=23) ILI9341_drawLine( i, 10, i, 230, ILI9341_WHITE); //draw vertical lines
  for(uint16_t i = 10; i<240; i+=22) ILI9341_drawLine( 10, i, 300, i, ILI9341_WHITE); //draw horizontal lines
  ILI9341_drawLine( 10, 119, 300, 119, ILI9341_WHITE); //draw horizontal lines    

  fill_text();

  while(1)
  {
    digitalWrite(25, 0);
    delay_tics(500000);
    //chThdSleepMilliseconds(1);
    digitalWrite(25, 1);
    delay_tics(500000);
    //chThdSleepMilliseconds(1);
  }

  return 0 ;
}

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __pins_ext_H
#define __pins_ext_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

void tic_delay(uint32_t cycle_count);
void pin_pulse_hi_low(uint16_t GPIO_Pin, uint32_t delay);
void pin_pulse_low_hi(uint16_t GPIO_Pin, uint32_t delay);

#ifdef __cplusplus
}
#endif

#endif /*__ pinoutConfig_H */

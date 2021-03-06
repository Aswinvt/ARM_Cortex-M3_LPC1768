#include <lpc17xx.h>
#include <stdint.h>

enum {INPUT=0, OUTPUT=1};
enum {LOW=0, HIGH=1};
enum {PINFUNC0,PINFUNC1,PINFUNC2,PINFUNC3};
enum { PIN0_0,PIN0_1,PIN0_2,PIN0_3,PIN0_4,PIN0_5,PIN0_6,PIN0_7,PIN0_8,PIN0_9,PIN0_10,PIN0_11,PIN0_12,PIN0_13,PIN0_14,PIN0_15,
			 PIN0_16,PIN0_17,PIN0_18,PIN0_19,PIN0_20,PIN0_21,PIN0_22,PIN0_23,PIN0_24,PIN0_25,PIN0_26,PIN0_27,PIN0_28,PIN0_29,PIN0_30,PIN0_31,

			 PIN1_0,PIN1_1,PIN1_2,PIN1_3,PIN1_4,PIN1_5,PIN1_6,PIN1_7,PIN1_8,PIN1_9,PIN1_10,PIN1_11,PIN1_12,PIN1_13,PIN1_14,PIN1_15,
			 PIN1_16,PIN1_17,PIN1_18,PIN1_19,PIN1_20,PIN1_21,PIN1_22,PIN1_23,PIN1_24,PIN1_25,PIN1_26,PIN1_27,PIN1_28,PIN1_29,PIN1_30,PIN1_31,	

			 PIN2_0,PIN2_1,PIN2_2,PIN2_3,PIN2_4,PIN2_5,PIN2_6,PIN2_7,PIN2_8,PIN2_9,PIN2_10,PIN2_11,PIN2_12,PIN2_13,PIN2_14,PIN2_15,
			 PIN2_16,PIN2_17,PIN2_18,PIN2_19,PIN2_20,PIN2_21,PIN2_22,PIN2_23,PIN2_24,PIN2_25,PIN2_26,PIN2_27,PIN2_28,PIN2_29,PIN2_30,PIN2_31,	

			 PIN3_0,PIN3_1,PIN3_2,PIN3_3,PIN3_4,PIN3_5,PIN3_6,PIN3_7,PIN3_8,PIN3_9,PIN3_10,PIN3_11,PIN3_12,PIN3_13,PIN3_14,PIN3_15,
			 PIN3_16,PIN3_17,PIN3_18,PIN3_19,PIN3_20,PIN3_21,PIN3_22,PIN3_23,PIN3_24,PIN3_25,PIN3_26,PIN3_27,PIN3_28,PIN3_29,PIN3_30,PIN3_31
		 };	

void GPIO_SetPinDir( uint8_t uipinnum, uint8_t uidirection );
void GPIO_SetPinFunc( uint8_t uipinnum , uint8_t uipinfunc);
void GPIO_SetPinVal( uint8_t uipinnum , uint8_t uipinval);
uint8_t GPIO_GetPinVal( uint8_t uipinnum );
void GPIO_delay( uint8_t uidelay );

#include "IR_emitter.h"
#include <EFM8LB1.h>
#include <stdint.h>

#ifndef SYSCLK
#define SYSCLK 24500000L // SYSCLK frequency in Hz
#endif

#define TIMER_0_FREQ 2*38000L 

#define TX_PIN P2_1

#define I_CYCLES 2*20L
#define BIT_CYCLES 2*20L

volatile unsigned int TickCount=0;
volatile uint8_t tx_data=0;
volatile unsigned int tx_active = 0;
volatile unsigned int bit_pos = 0;

void Timer0_ISR (void) interrupt INTERRUPT_TIMER0{
	SFRPAGE=0x0;
	// Timer 0 in 16-bit mode doesn't have auto reload, so reload here
	TMR0=0x10000L-(SYSCLK/(TIMER_0_FREQ));

	if(!P0_4){
		TX_PIN = !TX_PIN;
	} else {
		TX_PIN = 0;
	}
	// if(tx_active == 0){
	// 	TX_PIN = 0;
	// 	TickCount = 0;
	// 	bit_pos = 0;
	// } else {
	// 	if(TickCount < I_CYCLES){
	// 		TX_PIN = !TX_PIN;
	// 		TickCount++;
	// 	} else {
	// 		if(bit_pos >= /*sizeof(tx_data)**/8){// All bits have been sent
	// 				tx_active = 0;
	// 		}
	// 		TX_PIN = 0;
	// 		if(TickCount >= (2*I_CYCLES + ((tx_data >> bit_pos) & 0x1)*BIT_CYCLES)){
	// 			bit_pos++;
	// 			TickCount = 0;
	// 		}else {
	// 			TickCount++;
	// 		}
	// 	}
	// }
}



void IR_emitter_init(){
	// Configure the pin used for LED output: P2.1 (pin 16 of LQFP32 package)
	P2MDOUT |= 0b_0000_0010;

	//XBR0 = 0X00;
	//XBR1 = 0X00;
	//XBR2 = 0x40; // Enable crossbar and weak pull-ups

	// Initialize timer 0 for periodic interrupts
	TR0=0;
	TF0=0;
	CKCON0|=0b_0000_0100; // Timer 0 uses the system clock
	TMOD&=0xf0;
	TMOD|=0x01; // Timer 0 in mode 1: 16-bit timer

	TMR0=0x10000L-(SYSCLK/(TIMER_0_FREQ)); // Initialize reload value
	ET0=1; // Enable Timer0 interrupts
	TR0=1; // Start Timer0
}

int send_data(uint8_t s_data){
	// if(tx_active){
	// 	return 1; 
	// }
	// tx_data = s_data;
	// tx_active = 1;
	// return 0;

	//usart_putchar(s_data & 0xFF);
}


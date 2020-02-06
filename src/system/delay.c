#include <stdint.h>
#include <addresses/timer.h>
#include <mmio/mmio.h>
#include <system/delay.h>
#include <system/cpu_clock.h>

void delay_cycles(uint32_t cycles){
	uint32_t timer_now, timer_leave;
	timer_leave = mmio_get32(TIMER_CLO) + cycles;
	while( (timer_now = mmio_get32(TIMER_CLO)) < timer_leave ){}
}

void delay_micros(uint32_t micros){
	delay_cycles(micros * CPU_CLOCK_FREQ_MHZ / DELAY_CYCLES_COUNT);
}	

void delay_millis(uint32_t millis){
	delay_cycles(millis * CPU_CLOCK_FREQ_KHZ / DELAY_CYCLES_COUNT);
}

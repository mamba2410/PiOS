#include <stdint.h>
#include <addresses/timer.h>
#include <mmio/mmio.h>
#include <system/delay.h>
#include <system/cpu_clock.h>


/*
 * Delay for a given number of clock cycles
 * Actually waits for real-time clock cycles, not process cycles
 * so if the process switches whilst waiting, then returns, the delay will
 * still include the switched cycles as well
 */
void delay_cycles(uint32_t cycles){
	uint32_t timer_now, timer_leave;
	timer_leave = mmio_get32(TIMER_CLO) + cycles;	// What timer reg value should we quit at?
	while(1){										// Wait
		timer_now = mmio_get32(TIMER_CLO);			// What timer val is it now?
		if( timer_now >= timer_leave ) return;		// If we are at or over where we should be, stop
		//cycles--;									// If not, do something to pass the time, could add a schedule call here
	}
}

/*
 * Delay for a given number of microseconds, not that precise but it's good enough
 */
void delay_micros(uint32_t micros){
	delay_cycles(micros * (uint32_t)(CPU_CLOCK_FREQ / 1e6));
}	

/*
 * Delay for a given number of milliseconds, not that precise but it's good enough
 */
void delay_millis(uint32_t millis){
	delay_cycles(millis * (uint32_t)(CPU_CLOCK_FREQ / 1e3));
}

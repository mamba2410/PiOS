#ifndef CPU_CLOCK_H
#define CPU_CLOCK_H

/*
 * I don't actually know the clock speed precisely.
 * The website advertises the 3B as 1.2GHz but I don't know what mine is running at
 * I have been doing this by experiment and I seem to be a factor of 1000 out and I don't know why
 * It seems to be between 1.0 MHz and 1.2MH with a printf to serial at 115200 baud
 * There might be a way to set the clock frequency with the config.txt but I don't know
 * how strictly the system sticks to that
 */
//#define CPU_CLOCK_FREQ		1200000000	// 1.2GHz
#define CPU_CLOCK_FREQ		1000000	// 1.0GHz

#endif /* CPU_CLOCK_H */

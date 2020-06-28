#include <stdint.h>
#include <stdarg.h>
#include <serial/printf.h>
#include <serial/uart0.h>
#include <serial/mini_uart.h>

static char *putc_str = (char*)0;
static uint16_t putc_str_end = 0;

/*
 * Convert unsigned long int to string
 */
static void uint64_to_str(uint64_t num, uint8_t base, uint8_t upper_case, char *buffer){
	uint64_t n = 0;		// Not sure, number of digits?
	uint64_t d = 1;		// Divider for the digit, like 100, 10, 1 etc

	while( num/d >= base ) d *= base;	// Get the largest digit, then count down

	while( d ){					// While the digit is not zero
		char digit = num/d;		// Get most significant digit
		num %= d; 				// Can discard that digit now
		d /= base;				// Can also drop the divider by one digit

		if( n || digit > 0 || !d ){
			// Convert digit number to ascii character code then increment buffer position
			// If upper case, add 'A', else (if lower case) add 'a' and make sure to correct for 
			// A being equal to decimal 10
			*buffer++ = digit + (digit<10? '0': (upper_case? 'A':'a')-10);
			n++;	// Increment the number of digits
		}
	}
	*buffer = 0;	// Null terminate the string
}


/*
 * Convert signed long int to string
 */
static void int64_to_str(int64_t num, char *buffer){
	if(num < 0){				// If number is negative
		num *= (int64_t)(-1);	// Make it positive
		*buffer++ = '-';		// Put a negative sign in front
	}

	// Same logic as unsigned now
	// Only want decimal this time, so base=10 and upper case doesn't matter
	uint64_to_str(num, 10, 0, buffer);
}


/*
 * Convert an ascii character to a digit
 * Only supports up to base 16, can increase range to 'z' and 'Z' for base 36
 */
static int8_t char_to_digit(char c){
			if( c >= '0' && c <= '9' ) return c-'0';
	else	if( c >= 'a' && c <= 'f' ) return c-'a'+10;
	else	if( c >= 'A' && c <= 'F' ) return c-'A'+10;
	else	return -1;
}


/*
 * Convert ascii string to integer?
 */
static char str_to_int32(char c, char **str_pointer, uint8_t base, uint32_t *num_pointer){
	char *p = *str_pointer;		// Get first character of string
	int8_t digit;				// Reserve temporary digit variable

	while( (digit = char_to_digit(c)) >= 0 ){	// While digit gives no error
		if(digit > base) break;					// If digit is invalid, stop everything
		(*num_pointer) = (*num_pointer)*base + digit;	// Multiply number by the base and add the digit
		c = *p++;								// Character is next part of the string, then increment pointer
	}
	*str_pointer = p;	// Replace string with remanining string
	return c;			// Return character that was rejected
}


/*
 * Prints a string n characters long
 */
static void put_n_characters(uint8_t n, char fill, char *buffer, void(*putc)(char)){
	char *p = buffer;
	char c;
	while( *p++ && n > 0 ) n--;				// Get the number of fill characters to use
	while( n-- > 0 ) (*putc)(fill);			// Print the required fill characters
	while( (c = *buffer++) ) (*putc)(c);	// Print the rest of the string
}


/*
 * Format the string with the arguments
 * prints string to uart
 */
void _format(char *format, va_list va, void(*putc)(char)){
	char buffer[12];	// have a buffer string
	char c;

	// Loop through characters that arent null
	while( (c = *format++) ){
		if( c != '%'){
#ifdef NEWLINE_CARRIAGE_RETURN
			if(c == '\n') (*putc)('\r');	// If the character is newline, also print carriage return
#endif /* NEWLINE_CARRIAGE_RETURN */
			(*putc)(c);					// If the character isn't special, print it
		} else{
			char fill = ' ';
			uint32_t number_length = 0;
			
			c = *(format++);	// Move on to the next character, ie skip the '%'
			if( c == '0' ){		// If the format starts with 0, set the fill character to zero and move on
				fill = '0';
				c = *(format++);
			}
			if( (c >= '0') && (c <= '9') )	// if the character is a number
				c = str_to_int32(c, &format, 10, &number_length);	// get the number of characters the string should be, as well as increment the string pointer

			switch(c){					// What am I printing?
				case  0 : goto abort;	//if null, quit
				case 'u': {				// printing unsigned int
					uint64_to_str(va_arg(va, uint64_t), 10, 0, buffer);	// convert first argument to unsigned int string and put it in buffer
					put_n_characters(number_length, fill, buffer, putc);		// print the buffer
					break;
				 }
				case 'd': {				// printing signed decimal
					int64_to_str(va_arg(va, int64_t), buffer);			// Convert to signed int string and put in buffer
					put_n_characters(number_length, fill, buffer, putc);		// print buffer
					break;
				}
				case 'x':				// printing lower case hex
				case 'X': {				// printing upper case hex
					uint64_to_str(va_arg(va, uint64_t), 16, (c=='X'), buffer);	// Convert to upper/lower case hex string
					put_n_characters(number_length, fill, buffer, putc);
					break;
				}
				case 'c': {				// printing a character
					(*putc)((char)va_arg(va, uint32_t));		// Print the character in the arguments
					break;
				}
				case 's': {				// printing a string
					put_n_characters(number_length, fill, va_arg(va, char*), putc);	// print the string given
					break;
				}
				case '%': {				// printing a literal '%'
					(*putc)(c);		// Just put the %
				}
				default: break;
			}
		}
	}

	abort:;	// Label for aborting the function
}

/*
 * ===================================
 *
 */

static void sprintf_putc(char c){
	putc_str[putc_str_end++] = c;
}




/*
 * printf for the uart
 */
void printf(char *format, ...){
	va_list va;
	va_start(va, format);
#ifdef PRINTF_UART0
	_format(format, va, &uart0_putc);
#else
	_format(format, va, &mini_uart_putc);
#endif /* PRINTF_UART0 */
	va_end(va);
}

void sprintf(char *str, char *format, ...){
	va_list va;
	va_start(va, format);
	putc_str = str;
	putc_str_end = 0;
	_format(format, va, &sprintf_putc);
	sprintf_putc('\0');
	va_end(va);
}


/*
 * Convert unsigned int to string
 * Don't need this cause it's exactly the same as uint64_t but with different data types
 * Can sacrifice code space for ram space for now
 */
//static void uint32_to_str(uint32_t num, uint8_t base, uint8_t upper_case, char *bf){}


/*
 * Convert signed int to string
 * Don't need this cause it's exactly the same as uint64_t but with different data types
 * Can sacrifice code space for ram space for now
 */
//static void int32_to_str(int32_t num, char *bf){}


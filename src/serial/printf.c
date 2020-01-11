#include <serial/printf.h>
#include <serial/mini_uart.h>
#include <stdint.h>
#include <stdarg.h>

/*
 * Convert unsigned long int to string
 */
static void uint64_to_str(uint64_t num, uint8_t base, uint8_t upper_case, char *buffer){
	uint64_t n = 0;		// Not sure, number of digits?
	uint64_t d = 1;		// Divider for the digit, like 100, 10, 1 etc

	// Get the largest digit needed to represent, then count down
	while( num/d >= base ) d *= base;

	// While the digit is not zero
	while( d ){
		char digit = num/d;		// Get most significant digit
		num %= d; 				// Can discard that digit now
		d /= base;				// Can also drop the divider by one digit

		if( n || digit > 0 || !d ){
			// Convert digit number to ascii character code then increment buffer position
			// If upper case, add 'A', else (if lower case) add 'a' and make sure to correct for 
			// A being equal to decimal 10
			*buffer++ = digit + (digit<10? '0': (upper_case? 'A':'a')-10);
			// Increment the number of digits?
			n++;
		}
	}
	// Null terminate the string
	*buffer = 0;
}

/*
 * Convert signed long int to string
 */
static void int64_to_str(int64_t num, char *buffer){
	// If number is negative
	if(num < 0){	
		num *= (int64_t)(-1);			// Make it positive
		*buffer++ = '-';	// Put a negative sign in front
	}

	// Same logic as unsigned now
	// Only want decimal this time, so base=10 and upper case doesn'y matter
	uint64_to_str(num, 10, 0, buffer);
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

	// While digit gives no error
	while( (digit = char_to_digit(c)) >= 0 ){
		if(digit > base) break;		// If digit is invalid, stop everything
		(*num_pointer) = (*num_pointer)*base + digit;	// Multiply number by the base and add the digit
		c = *p++;		// Character is next part of the string, then increment pointer
	}
	*str_pointer = p;	// Replace string with remanining string
	return c;			// Return character that was rejected
}

/*
 * Prints a string n characters long
 */
static void put_n_characters(uint8_t n, char fill, char *buffer){
	char *p = buffer;
	char c;
	while( *p++ && n > 0 ) n--;						// Counting how many characters are already in the string, leaving the number of fill characters
	while( n-- > 0 ) mini_uart_putc(fill);			// Print the required fill characters
	while( (c = *buffer++) ) mini_uart_putc(c);		// Print the rest of the string
}


/*
 * Format the string with the arguments
 * prints string to mini_uart
 */
void mini_uart_format(char *format, va_list va){
	char buffer[12];	// have a buffer string
	char c;

	// Loop through characters that arent null
	while( (c = *format++) ){
		if( c != '%') mini_uart_putc(c);		// If the character isn't special, print it
		else{
			char fill = ' ';
			uint32_t number_length = 0;
			
			c = *(format++);	// Move on to the next character, ie skip the '%'
			if( c == '0' ){		// If the format starts with 0, set the fill character to zero and move on
				fill = '0';
				c = *(format++);
			}
			if( (c >= '0') && (c <= '9') )	// if the character is a number
				c = str_to_int32(c, &format, 10, &number_length);	// get the number of characters the string should be, as well as increment the string pointer

			switch(c){	// What am I printing?
				case  0 : goto abort; //if null, quit
				case 'u': {		// printing unsigned int
					uint64_to_str(va_arg(va, uint64_t), 10, 0, buffer);	// convert first argument to unsigned int string and put it in buffer
					put_n_characters(number_length, fill, buffer);		// print the buffer
					break;
				 }
				case 'd': {		// printing signed decimal
					int64_to_str(va_arg(va, int64_t), buffer);			// Convert to signed int string and put in buffer
					put_n_characters(number_length, fill, buffer);		// print buffer
					break;
				}
				case 'x':		// printing lower case hex
				case 'X': {		// printing upper case hex
					uint64_to_str(va_arg(va, uint64_t), 16, (c=='X'), buffer);	// Convert to upper/lower case hex string
					put_n_characters(number_length, fill, buffer);
					break;
				}
				case 'c': {		// printing a character
					mini_uart_putc((char)va_arg(va, uint32_t));		// Print the character in the arguments
					break;
				}
				case 's': {		// printing a string
					put_n_characters(number_length, fill, va_arg(va, char*));	// print the string given
					break;
				}
				case '%': {		// printing a literal '%'
					mini_uart_putc(c);
				}
				default: break;
			}
		}
	}

	// Abort the function
	abort:;
}


/*
 * printf for the mini uart
 */
void mini_uart_printf(char *format, ...){
	va_list va;
	va_start(va, format);
	mini_uart_format(format, va);
	va_end(va);
}





















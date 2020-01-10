

// Function to zero out the memory in the section starting at x0
// And with size x1
// Make the label visible to anybody
.global zero_memory
zero_memory:
	// Store the contents of the zero register into 
	// The address pointed to by x0
	// And offset x0 by +8
	str		xzr,	[x0],	#8
	// Decrement the size by 8
	subs	x1,		x1,		#8
	// Loop back around
	b.gt	zero_memory
	// Return to where you came from
	ret

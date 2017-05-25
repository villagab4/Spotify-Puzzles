#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/** This is a solution to the Spotify Reversed Binary Numbers puzzle.
 *  @author Gabe Villasana
 *  @email: villagab4@gmail.com
 *  @date:  May 25, 2017 
 */

int reverseBinary(int input) {

	// The floor of the log function will determine
	// how many bits are used, which will ease the 
	// masking process.

	int floorLog = (int) (log10(input) / log10(2));

	// Initial will be the masking binary number which 
	// contains the same number of bits as the input.
	// Initial will have a 1 in the first bit, and a 1
	// in the last bit. All other bits will contain 0.

	int initial = (int) pow(2, floorLog) + 1;

	// Keeps track of how many iterations the loop should run through.

	int numIterations = floorLog;

	// Allows for modification with shifts without ruining proper comparison.

	int temp = initial;

	// Each iteration will reduce the masking binary number
	// by 2 bits so as to maintain consistency and compare
	// proper values. Shift is used to determine necessary binary shifts.
	// Update shift to ensure comparing proper bits.
	// For example, initial may start as 10001, then after one iteration,
	// initial will be modified to 01010 --> 1010. 

	for (int shift = 0; shift < numIterations - shift; shift++) {

		// First check: input has 1 at comparing bits, if fails -> no swap needed.
		// Second conditional: input has 0 at comparing bits, if fails -> no swap needed.
		// If both conditionals pass, then separate values at comparing bits -> swap needed.

		if ( ( input != (input | initial) ) && ( input != ( input & ~initial ) ) ) {
			
			input ^= 1 << (numIterations - shift); //toggle bit at front
			
			input ^= 1 << (shift); //toggle bit at back
			
		}

		// Update initial to properly compare next bits.

		temp = (temp / 4 + 1);
		initial = temp << (shift + 1);

	}

	return input;

}

int main() {
	int input = 0;
	scanf("%d", &input);
	printf("%d\n", reverseBinary(input));
}
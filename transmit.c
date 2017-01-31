
/*

File transmit.c


Purpose: simulate a transmission of characters over the network.  

It converts a message given as an array of characters to an array of short integers that are sent over the network.
The converted message uses 1-bit error correction code.

As part of the simulation, the program also injects errors to the encoded message by flipping one bit.


Revision:
a. Initial code - Doron Nussbaum
b. Updated code - Mohamad Yassine

*/

/************************************************************************/

// INCLUDE FILES


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "bit_manipulation.h"


/************************************************************************/
//MACROS  / DEFINES



#define MAX_MSG_LENGTH 2048
#define P1_MASK 0xaa8   // 0b0101010101000
#define P2_MASK 0xcc8	// 0b0110011001000
#define P4_MASK 0x10e0	// 0b1000011100000
#define P8_MASK 0x1e00  // 0b1111000000000


/* The following are ANSI Escape Sequences. 
 * You can find more by typing: man terminfo
 * The exact ones under can be found on stackoverflow here:
 * http://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
 */

#define ANSI_COLOR_RED     "\x1b[31;1m"
#define ANSI_COLOR_GREEN   "\x1b[32;1m"
#define ANSI_COLOR_YELLOW  "\x1b[33;1m"
#define ANSI_COLOR_BLUE    "\x1b[34;1m"
#define ANSI_COLOR_MAGENTA "\x1b[35;1m"
#define ANSI_COLOR_CYAN    "\x1b[36;1m"
#define ANSI_BACK_BLACK    "\x1b[31;1m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define CLEAR "\033[2J"
/************************************************************************/
// FUNCTION PROTOTYPES


int readMessage(char *s, int len, int *numRead);
int char2Short(char c, short *encodedChar);
int setParityBits(short *num);

/************************************************************************/


int main(int argc, char *argv[])

{
	int rc = 0;		// return code

	char s[MAX_MSG_LENGTH] = { '\0' };  // message
	short encodedMsg[MAX_MSG_LENGTH];
	int numRead = 0;  // number of characters in the message
	int i;

	// read the message
	printf(ANSI_COLOR_CYAN "Transmit Program written in C\n" ANSI_COLOR_RESET);
	printf("\nHamming Code Implementation v1.0.0 by Mohamad Yassine\n");

	printf(
		ANSI_COLOR_RED 
		"After running this program, please copy the output and run \n "
		"the receive program "
		ANSI_COLOR_GREEN
		"./recv .\n\n"
		ANSI_COLOR_RESET);

	printf("Please enter a message to transmit: ");
	readMessage(s, MAX_MSG_LENGTH, &numRead); 


	// encode the message
	for (i = 0; i < numRead; i++) {
		char2Short(s[i], &encodedMsg[i]);	// embedd the char in a short int
		setParityBits(&encodedMsg[i]);		// set the parity bits
	}
	// add errors to mesage 
	for (i = 0; i < numRead; i++) {
		if (rand()%36000 < 25000) {
			int bit = rand() % 13;
			flipBitShort(bit, &encodedMsg[i]);
		}
	}
	// print the message
	printf("\nTransmitted message (short integers):\n\n\t" ANSI_COLOR_RED);
	for (i = 0; i < numRead; i++) {
		printf("%d ", encodedMsg[i]);

	}


    printf(ANSI_COLOR_RESET "\n\n");
	return(0);
}


/***********************************************************************************/
/* reads a message from the user

input
len - maximum length of mesage that should be read

output
s - contains the message
numRead - the number of characters in the message

assumption - s is valid
*/

int readMessage(char *s, int len, int *numRead)
{
	int i;
	int rc = 1;
	*numRead = 0;
	for (i = 0; i < len, rc != 0; i++) {
		rc = scanf("%c", &s[i]);
		if (s[i] == '\n') break;
		(*numRead)++;
	}
	return(0);
}


/*************************************************************************/
/* spreads bits 0-7 of the character c into bits 3,5,6,7,9,10,11,12 of the short encodedChar

input
character c

output
encodedChar - a short with the bits of c

*/


int char2Short(char c, short *encodedChar)

{
	short mask = 0x0001;
	int i;
	int bitSet;

	*encodedChar = 0;
	for (i = 0; i < 8; i++) {

		// check if bit i is set
		bitSet = isCharBitSet(c, i);

		// set the correct bit in the encoded character
		if (!bitSet) continue;
		switch (i) {
		case 0:
			setShortBit(3, encodedChar);
			break;
		case 1:
		case 2:
		case 3:
			setShortBit(4 + i, encodedChar);
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			setShortBit(5 + i, encodedChar);
			break;
		default:
			printf("This should not happen !!!!\n");
			assert(0);
		}
	}
	return(0);
}



/*************************************************************************************/


/* sets the parity bits in the variable num  


input
num - the short number where parithy bits must be set
*/


int setParityBits(short *num)

{
	int mask;
	int sum;

    /*
     * Set parity bits p1 p2 p4 p8
     * Summary: 
     *  1 - Apply the MASK using the AND operand
     *  2 - Count the bits that are the result of the AND
     *  3 - Find if ODD or Even
     *      - ODD : If it was ODD (sum % 2 isn't 0) then
     *              We have to set that bit to 1 to make
     *              it even.
     *      - EVEN: Do nothing.
     *  4 - Done.
     * */
    
    if (compareBits(2, P1_MASK, *num)) setShortBit(1, num);
    if (compareBits(2, P2_MASK, *num)) setShortBit(2, num);
    if (compareBits(2, P4_MASK, *num)) setShortBit(4, num);
    if (compareBits(2, P8_MASK, *num)) setShortBit(8, num);
   	return(0);
}


/*

File receive.c


Purpose: simulate the receiveing end of a message over the network.  

The program converts a message encodded as an array of short integers into characters.
The input message uses 1-bit error correction code.
As part of the simulation, the program also corrects any 1-bit errors in the receiving message.


Revision:
a. Initial code - Doron Nussbaum
b. Updated code - Mohamad Yassine 100966528

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

#define XSTR(A) STR(A)
#define STR(A) #A
#define MAX_INPUT_LENGTH 8192
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


void short2Char(short encodedChar, char *c);
void correctCode(short *num);
void readEncodedMessage(short *buf, int len, int *numRead);



/**************************************************************************/

int main(int argc, char *argv[])

{
	int rc = 0;		// return code

	char s[MAX_MSG_LENGTH] = { '\0' };  // message
	short encodedMsg[MAX_MSG_LENGTH];
	int numRead = 0;  // number of characters in the message
	int i;

	// read the message
	printf(ANSI_COLOR_CYAN"Receive Program written in C\n"ANSI_COLOR_RESET);
	printf("\nHamming Code Implementation v1.0.0 by Mohamad Yassine\n");

	printf(
		ANSI_COLOR_RED 
		"If you have not already, please run "
		ANSI_COLOR_GREEN
		"./tran "
		ANSI_COLOR_RED
		"to generate a message.\n\n"
		ANSI_COLOR_RESET);

	printf("Please enter the transmitted message: ");
	readEncodedMessage(encodedMsg, MAX_MSG_LENGTH, &numRead);



	// print the corrected message
	printf("\n\n Transmitted Message:\n\n\t" ANSI_COLOR_BLUE);
	for (i = 0; i < numRead; i++) {
		char c;
		short2Char(encodedMsg[i], &c);
		printf("%c", c);
    }
    printf("\n");

    // correct the message
	for (i = 0; i < numRead; i++) {
		correctCode(&encodedMsg[i]);
	}

	// print the corrected message
	printf(ANSI_COLOR_RESET);
	printf("\n\n Corrected Transmitted Message:\n\n\t " ANSI_BACK_BLACK);
	for (i = 0; i < numRead; i++) {
		char c;
		short2Char(encodedMsg[i], &c);
		printf("%c", c);
	}
	printf(ANSI_COLOR_RESET" \n\n");
	return(0);
}


/***********************************************************************************/
/* reads a message from the user

input
len - maximum length of mesage that should be read

output
receivedMsg - contains the message
numRead - the number of characters in the message

*/


void readEncodedMessage(short *receivedMsg, int len, int *numRead)
{
	int i;
	int rc;
	char s[MAX_INPUT_LENGTH+1];
	char *token = NULL;
	*numRead = 0;

	s[MAX_INPUT_LENGTH] = '\0';
	scanf("%"XSTR(MAX_INPUT_LENGTH)"[^\n]s", s);
	token = strtok(s, " ");

	for (i = 0; token != NULL  &&  i < len;token = strtok(NULL, " "), i++) {
		rc = sscanf(token, "%hd", &receivedMsg[i]);
	}

	*numRead = i; // set the number of read integers

    // empty the input buffer
    for( ; getchar() != '\n'; );


}




/*************************************************************************/
/* collect of a short bits 3,5,6,7,9,10,11,12  to bits 0-7 of a char

input
encodedNum - a short with the bits of c

output
c - the char that is embedded in encodedNum

*/

//                    FROM 			   TO
void short2Char(short encodedNum, char *c)

{
	short mask = 0x0001;
	int i;
	int bitSet;
	int k;

	*c = 0;
	
	for (i = 0; i < 8; i++) {
		// Reaching into bit positions 3,5,6,7,9,10,11,12
		if (i == 0) 			k = 3; 
		if (i > 0  && i < 4) 	k = 4 + i; 
		if (i > 3  && i < 8)    k = 5 + i;

		// Checking if bit at k is set aka == 1 
		bitSet = isShortBitSet( encodedNum, k); 

		// if bit is 0.skip setCharBit and increment i 
		if (bitSet == 0) continue;

		// Set the correct bit in the decoded char
		setCharBit(i, c);

	}
}


/*************************************************************************************/


/* purpose:
performs error corrrections, if needed on the short integer

The function first checks the parity bits for error.  
If there is an error then it fixes it.

input
num - the address of the short number 
*/


void correctCode(short *num)

{
	int mask;
	int sum;
	int bitNumber = 0; //  bit number with the error bit
	int parity;		// a parity bit either 0 or 1
	int storedParity; // the parity bit in the encoded char

	// Reset parity
    parity = 0;
    // The bit we received
    storedParity = isShortBitSet(*num, 1);

    if (compareBits(2, P1_MASK, *num)) parity = 1;
    
    // Comapring before and now (checking if an error occured)
    // If there is an error add to BitNumber 
    if (storedParity != parity) bitNumber += 1;

    // Do the same for the rest
    
    parity = 0; 
    storedParity = isShortBitSet(*num, 2);
    if (compareBits(2, P2_MASK, *num)) parity = 1;
    if (storedParity != parity) bitNumber += 2;

 
    parity = 0; 
    storedParity = isShortBitSet(*num, 4);
    if (compareBits(2, P4_MASK, *num)) parity = 1;
    if (storedParity != parity) bitNumber += 4;

 
    parity = 0; 
    storedParity = isShortBitSet(*num, 8);
    if (compareBits(2, P8_MASK, *num)) parity = 1;
    if (storedParity != parity) bitNumber += 8;

    // Flip incorrect bit at bitNumber
    flipBitShort(bitNumber, num);

    return;
} 
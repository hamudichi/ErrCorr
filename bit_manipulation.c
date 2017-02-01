
/*

File bit_manipulation.c

Purpose :
contains helper functions for manipulating bits


Revisions:
file created: Doron Nussbaum
implemented function prototypes - Mohamad Yassine 100966528
* /

/************************************************************************/

// INCLUDE FILES

#include "bit_manipulation.h"


//example of a testing function main();
#if 0
int main(int argc, char *argv[])

{
	int rc = 0;		// return code


	short test = 0;
	short modified;
	int bitNum;		// bit number to be used
	

	test = 0;
	bitNum = 2;
	modified = test;
	flipBitShort(bitNum, &modified);
	printf("test_int=%d, flipping bit #=%d, answer should be=%d, test_modified=%d\n"
            , test, bitNum, 4, modified);

	rc = isShortBitSet(modified, 3);
	printf("Bit 3 in %d should not be set.  Answer is %d \n", modified, rc);

	rc = isShortBitSet(modified, 2);
	printf("Bit 2 in %d should  be set.  Answer is %d \n", modified, rc);


   getchar();
   
	return(0);
}

#endif
/*************************************************************************************/
/* purpose: checks if bit i is set

input:
c - the character to be checked
bitNum - the bit number to be checked

return:
1 if the bit is set to 1
0 if the bit is not set (bit is 0)

*/

int isCharBitSet(char c, int bitNum) {
    return ((c >> bitNum) & 1);
}




/*************************************************************************************/

/* purpose: checks if bit i is set

input: 
num - the number to be checked
bitNum - the bit number to be checked 

return:
1 if the bit is set to 1
0 if the bit is not set (bit is 0)

*/
int isShortBitSet(short num, int bitNum)

{
	/* ADDED JAN 26 19:30 */
    return (num >> bitNum) & 1;
}

/*************************************************************************************/
/* purpose: sets bit bitNum to 1 

input:
num - the address of the short integer
bitNum - the bit number to be checked

	

*/

void setShortBit(int bitNum, short *num) {
	/* Checks if the bit is 0 and changes it, if not then keeps it the same. */
    *num = *num | 1 << bitNum;
}

/*************************************************************************************/


/* purpose: sets bit bitNum to 1

input:
c - address of character 
bitNum - the bit number to be checked

return:
1 if the bit is set to 1
0 if the bit is not set (bit is 0)

*/
void setCharBit(int bitNum, char *c)

{
    //*c = (*c >> bitNum) & 1;
    *c = *c | (1 << bitNum);
    
}

/*************************************************************************************/


/*  count the number of bits in a short

input: 
num - a short interger

return
the numer of bits that are set to 1 in num



*/
int countBits(short num)

{
    /* Logic: 
     * 0x9  = 1001 | 2 bits set to 1
     * 0x11 = 1011 | 3 bits set to 1
     */
	int total = 0;
    int atNow = 0;
    int i;
    for (i = 0; i < 16; i++) {
        atNow = isCharBitSet(num, i);
        if (atNow) total++;
    }
	//	if (isShortBitSet(num, i) == 1) total++;
	

     return total;
}

/*************************************************************************************/

/* purpose:
flips bit i in num (set bit i to 1 if the bit is 0 or set bit i to 0 if the bit is 1)

input:
bitNum - the bit number to be flipped
num - address of the short integer

*/
void flipBitShort(int bitNum, short *num)

{
    /* Flip the bit at i */
     *num ^= 1 << bitNum;
     return;
}

/*****************************************************************************/
/*
 * Compare the bits between the already known masks (P1_MASK, P2_MASK ..etc )
 * Comparing usind AND operation, if there is a match then increment sum
 * 
 * Input : 
 * 	short modular 	: the number to use when modulating
 * 	short mask 		: the given masks 
 * 	short num 		: user provided short
 * Output :
 * 	the modular of the sum 
 */

int compareBits(short modular, short mask, short num) {
    int sum = 0;

    for (int i = 0; i < sizeof(mask)*8; i++) 
        if (isShortBitSet(num, i) & isShortBitSet(mask, i))
            sum += 1;
    

    return sum % modular;
} 


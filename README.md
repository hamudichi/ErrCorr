# ErrCorr.v1
[![N|Solid](http://i.imgur.com/aUrmbj4.jpg)](http://nonameslol.com)  
`Mohamad Yassine - January 2017`
##### Error Detection and Correctiong using Hamming Code
To demonstrate how parity checking works using the Hamming method. This program uses 4 individual bits to parity check, and can therefore correct it'sefl in case a bit is lost over transmision.
Writin in C and does not use any aditional libraries.

##### Compilation and Execution
You can simply compile the `c` files using the following
```sh
$ make
```
Run the transmit program by 
```sh
$ ./trans
```
After execution, go a head and type your sequence of chars or in other words string that you would like to test
Copy it to clip board and start 'receive' by
```sh
$ ./recv
```
Paste in the sequence of numbers and see that it does in fact work.

Cop



[MORE INFO TO BE ADDED WHEN COMPLETED]
Error Detection and Correction [COMP 2401, a1]
Implements the Hamming Code

<TITLE>ErrCorr</TITLE>: Hamming Code Implementation
Auth 	: Mohamad Yassine
Course:
Date : Jan 20, 2017

Purpose : To demonstrate how parity checking works using the Hamming method. 
		  This program uses 4 individual bits to parity check, and can therefore
		  correct it'sefl in case a bit is lost over transmittion.


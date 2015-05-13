/* 	sendto:tuf18653@temple.edu 
*/
//  FILE:	  	crypto_main.c (this is my tester program to compile)
//  AUTHOR:	  	Dau Ting Lam
//	DATE:	  	10/29/2014
//  FOR:	  	Assignment 8 - Crypto Cracker
// 	CLASS:    	CIS 2107, Section 2
//	INSTRUCTOR: John Fiore
//  TA:       	Chen Shen
//
//  notes: Tested working on Mac OS X's gcc Terminal
//	notes: 100% Complete
/***********************************************************/

#include "cryptocracker.h"
#include "cryptocracker.c"

#define EXIT_SUCCESS 0
#define EXIT_FAIL 0
#define DICT 0
#define ENCRYPT 1

int main (int argc, char** argv) {
	int status;	// fail/success
	float success_thres = 0.65; 	// setting 65% of words found in dict
	InputFile infDict;				// structs
	InputFile infEncrypt;

	/* User only entered encypted file */
	if ((argc==2) && ((status=usage(argc, argv, 2, 1)) == FILE_OPEN_SUCCESS)) { // only supplied encrypt, use default path
		char* path = "/usr/share/dict/words"; 	//default path
		infEncrypt.fp = fopen(argv[1], "r");
		infDict.fp = fopen(path, "r");
	}
	/* User entered encypted file and dict */
	else if ((argc==3) && ((status=usage(argc, argv, 3, 2)) == FILE_OPEN_SUCCESS)) {  // supplied both
		infEncrypt.fp = fopen(argv[1], "r");
		infDict.fp = fopen(argv[2], "r");
	}
	/* User entered no files, print error */
	else { 
		printf("error: no dict or encypt file to crack supplied\n");
		return EXIT_FAIL;
	}

	parse(&infEncrypt, file_char_count(infEncrypt.fp)); // read file and tokenize strings 
	parse(&infDict, file_char_count(infDict.fp));		// read file and tokenize strings

 	decrypt(&infEncrypt, &infDict, success_thres);		// determine shift and crack file and print 

	return EXIT_SUCCESS;
}

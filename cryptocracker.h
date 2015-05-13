/* 	sendto:tuf18653@temple.edu 
*/
//  FILE:	  	cryptocracker.h (header, declarations, constants)
//  AUTHOR:	  	Dau Ting Lam
//	DATE:	  	10/29/2014
//  FOR:	  	Assignment 8 - Crypto Cracker
// 	CLASS:    	CIS 2107, Section 2
//	INSTRUCTOR: John Fiore
//  TA:       	Chen Shen
//
//  notes: Tested working on Mac OS X's gcc Terminal
//	notes: To Test, run/compile crypto_main.c 
/***********************************************************/

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef FILEOPEN_H_
#define FILEOPEN_H_
#define FILE_OPEN_SUCCESS 1
#define FILE_OPEN_FAIL 0
int usage(int argc, char**argv, int expct, int reading);
#endif

#ifndef CRYPTO_H_
#define	CRYPTO_H_
#define DICT 0
#define ENCRYPT 1
#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */
#define EQ 1
#define NQ 0
#define NUM_TO_TRY 200 /* try checking the first 200 words in dict */

/* Description: Wrapper struct for file to crack/dictionary */
typedef struct _InputFile {
  FILE* fp;
  char** words;
  int wc;
}InputFile;

/* Descripton: shift c by k */
char shift_c(char c, int k);
/* Descripton: shift s by k */
char* shift_str(char* s, int k);
/* Descripton: search the dict with word, ignoring case 
	Return: 1 if search success, 0 if fail to find */
unsigned int search_dict_ignc(char* word, char** dict);
/* Descripton: parse file with size of characters inside the file */
void parse(InputFile *inf, unsigned int size);
/* Descripton: determine the shift, decrypt characters, and print it */
void decrypt(InputFile *infE, InputFile *infD, float thres);
/* Descripton: custom str compare, ignore case. 
	Return: 1 if match str, 0 if different str */
int strcmp_ign_case(char* s1, char* s2);
/* Descripton: print file by shifting k */
void print_cracked_file(FILE *fp, int k);
/* Descripton: char counter k */
unsigned int file_char_count(FILE *fp);
#endif

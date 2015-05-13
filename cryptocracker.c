/* 	sendto:tuf18653@temple.edu 
*/
//  FILE:	  	cryptocracker.c (implementations of functions)
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

#include "cryptocracker.h"

/* 	Function to: check if the arguments are correct
*	Returns:  int, 1 for success/ 0 for fail */
int usage(int argc, char**argv, int expct, int reading) {

	if (argc < expct) {											// Too little command-line arguments
    printf("error usage: %s filename is missing correct arguments\n", argv[0]);
    return FILE_OPEN_FAIL;
  	}
  	
  	if ((fopen(argv[reading], "r"))==NULL) {					
    printf("error opening %s for reading\n", argv[reading]);
    return FILE_OPEN_FAIL;
  	}

  	return FILE_OPEN_SUCCESS;									// otherwise, success
}

/* Descripton: shift c by k */
char shift_c(char c, int k) {
	char r;

	r = tolower(c) + (char)k;
	if (r <= 'z' && r >= 'a')
		return r;
	else
		return r - 26;
}

/* Descripton: shift s by k */
char* shift_str(char* s, int k) {
	int i, len;
	len = strlen(s);
	char* retp;
	retp = (char*)malloc(sizeof(char)*len+1);

	for (i = 0; i < len; ++i) {
		*(retp+i) = shift_c(*(s+i), k);
	}

	*(retp+len+1) = '\0';
	return retp;
}

/* Descripton: search the dict with word, ignoring case 
	Return: 1 if search success, 0 if fail to find */
unsigned int search_dict_ignc(char* word, char** dict) {
	char* s = word;
	char** dp = dict;
	unsigned int ret = 0;

	while(*dp != NULL) {
		char* p = *dp;
		if (strcmp_ign_case(s, p)) {		// is s==p?
			ret = 1; break; 				// found in dict, break out loop
		}
		else
			dp++;							// not found, move to next in dict
	}
	return ret;
}

/* Descripton: parse file with size of characters inside the file */
void parse(InputFile * inf, unsigned int size) {
	int i, j, sum;
	char line[512];
	char *tokenptr, *lineptr;

	inf->words = (char**)malloc(size*sizeof(char*)+1);
	i=sum=0;

    while (fgets(line, sizeof(line), inf->fp)) {
    	lineptr = line;
    	tokenptr = strtok(lineptr, " .,\n");
    	 while (tokenptr != NULL) {
            	inf->words[i] = strdup(tokenptr); // returned a malloc pointer
                i++;
                tokenptr= strtok(NULL, " .,_-!?:;/\\{}[]()|<>=+\"\'\n"); // tokenize
         }
    }

    inf->words[i] = NULL;
    inf->wc = i-1;

    rewind(inf->fp);
}

/* Descripton: determine the shift, decrypt characters, and print it */
void decrypt(InputFile *infE, InputFile *infD, float thres) {
	int i, shiftval, sum, min;
	unsigned int flag;
	char* p;
	shiftval = 0;
	flag = 1;
	sum = i = 0;
	
	if (infE->wc > NUM_TO_TRY) 
		min = NUM_TO_TRY;
	else 
		min = infE->wc;
	
	while (flag) {
		for (i=0; i<=min; ++i) {
			
			if (!shiftval) // 0
				p = infE->words[i];
			else 
				p = shift_str(infE->words[i], shiftval);
				
				
			sum+= search_dict_ignc(p, infD->words);
		}
		if (((float)sum/(float)min) > thres) {
			flag = 0;
		}
		else if (shiftval < 26) {
			sum = 0;
			shiftval++;
		}
		else {
			printf("uncrackable! \n");
			flag = 0;
		}
	}
	
	if (shiftval!=26) {
		if (infE->wc > NUM_TO_TRY+NUM_TO_TRY) 
			min = NUM_TO_TRY*2;
		else 
			min = infE->wc;

		
		for (i=NUM_TO_TRY; i<=min; ++i) {	
			if (!shiftval) // 0
				p = infE->words[i];
			else 
				p = shift_str(infE->words[i], shiftval);
			sum+= search_dict_ignc(p, infD->words);
		}
		
		if (((float)sum/(float)min) > thres) {
			print_cracked_file(infE->fp, shiftval);
		}
		else 
			printf("uncrackable! \n");
	}
	
}	

/* Descripton: custom str compare, ignore case. 
	Return: 1 if match str, 0 if different str */
int strcmp_ign_case(char* s1, char* s2) {
	char* p1 = s1;
	char* p2 = s2;
	int state = NQ;
	int diff;
	unsigned int len1, len2, space1, space2;

	len1 = strlen(s1);
	len2 = strlen(s2);

	space1 = space2 = 0;
	
	state = EQ;
	while ((*p1!='\0' && *p2!='\0') && state==EQ) {
		while (*p1=='\n' && *p1!='\0') {
			p1++;
			space1++;
		}
		while (*p2=='\n' && *p1!='\0') {
			p2++;
			space2++;
		}
		
		diff = ((tolower(*p1) == tolower(*p2)) ? 1 : 0);

		if (diff) {
			state = EQ;
			p1++;
			p2++;
		} 
		else {
			state = NQ;	
		}
	}
	
	if ((state==EQ) && (len1-space1) == (len2-space2))
		return EQ;
	else 
		return NQ;
	
}

/* Descripton: print file by shifting k */
void print_cracked_file(FILE *fp, int k) {
	int c;
	if (!k) { 							// is k zero? 
		while((c = fgetc(fp)) != EOF) 
			putchar(c);					// k=0, no shifting needed
	}
	else {								// k not zero, need shifting
		while((c = fgetc(fp)) != EOF) {
			if (isalpha((char)c))
				putchar((int)shift_c(c, k));
			else
				putchar(c);
		}
	}

	rewind(fp);

}

/* Descripton: char counter k */
unsigned int file_char_count(FILE *fp) {
	unsigned int c, nl, nw, nc, state;

	state = OUT;
	nl=nw=nc=0;

	while((c = fgetc(fp)) != EOF) {
		if(c != ' ') // here we dont care about empty whitespaces
		nc++; 
		if (c == '\n')
		nl++;
		if (isspace(c))
		state = OUT;
		else if (state == OUT) {
		state = IN;
		nw++;
		}
	}
	rewind(fp);
	return nc;
}

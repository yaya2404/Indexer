/*
 * tokenizer.c
 */
#include "tokenizer.h"

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.

 * NOTE: The way TKGetNextToken works in my function is that the char at position 0 of the input string is changed into an int. I then use the ASCII Table to determine whether the character is a number,letter, escape character, or punctuation. The function loops through the entire string incrementing itself by word++ until it reaches the '\0' or null-terminate symbol. After the checks, the character is then stored into "ans". 


 
 * Analysis: For the most part, the function must check through every character in the input string to determine the type of output and the output itself so the runtime	     is at best the length of the string or n. 

*/
char* TKGetNextToken(struct T *p) {	
		int let;
		char *ans = (char *) malloc(1024); 		//stores the string to be returned in function
		memset(ans, 0, 1024);
		while(p->w[0] != '\0'){
			let = p->w[0];			//stores char from position 0 of input string into integer form
			if(((let > 64) && (let < 91)) || ((let > 96) && (let < 123))||((let > 47) && (let < 58))){	//this if statement checks if "let" represents 
															//a letter a-z, A-Z, or 0-9
				if((let > 64) && (let < 91)){		//if the letter is from A-Z then it is changed to lowercase.
					ans[strlen(ans)] = let + 32;
				}else{
					ans[strlen(ans)] = let;		
				}
			}else{							//a check for non-alphanumeric numbers
				p->w++;
				if(strlen(ans) == 0){				//if ans is empty then the function returns a NULL
					free(ans);
					return NULL;
				}else{						//if ans is not empty then the function returns ans.
					return ans;
				}
			}
			p->w++;
		} 
	return ans;
}

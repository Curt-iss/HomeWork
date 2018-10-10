// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used C language code obtained from another student,
// the Internet, or any other unauthorized source, either modified
// or unmodified.
//
// - If any C language code or documentation used in my program
// was obtained from an authorized source, such as a text book or
// course notes, that has been clearly noted with a proper citation
// in the comments of my program.
//
// - I have not designed this program in such a way as to defeat or
// interfere with the normal operation of the grading code.
//
// Tanner Spicer
// tanner9


#include "FilterDigits.h"
#include <stdio.h>
/** This method concatenates 2 integers together
 *
 * Parameters: x: an unsigned 32 bit integer
 *             y: an unsigned 32 bit integer
 *
 * Returns: A concatenated integer
 * 
 *
 */
uint32_t concat(uint32_t x, uint32_t y){
  int power = 10;
  while (y >= power)
    power = power * 10;
  return x * power + y;

}
/**  Computes a new integer from N by separating all digits of N that
 *   are smaller than a specified value from those that are larger, and 
 *   placing the sets of digits (less, equal, larger) in an order 
 *   specified by one of the FilterAction values. 
 * 
 * For example:
 * 
 *     {954645,  LOFIRST,  6}  -->   544596
 *     {954645,  HIFIRST,  6}  -->   965445
 *     {   333,  LOFIRST,  3}  -->      333
 *     {   333,  HIFIRST,  3}  -->      333
 * 
 * Pre:  N is initialized
 *       action is HIFIRST or LOFIRST
 *       target is between 0 and 9, inclusive
 * Returns:  integer obtained by separating the digits of N as described
 *
 * Restrictions:
 *   - uses only its parameters and local automatic variables
 *     (i.e., no global variables)
 *   - does not make any use of character variables
 *   - does not make any use of arrays
 *   - does not read input or write output
 */
uint32_t FilterDigits(uint32_t N, enum FilterAction action, uint8_t pivot) {
  if (N==0)
      return 0;
  uint32_t Pivot = (uint8_t) pivot;
  uint32_t rest = N;
  uint32_t solution = 0;
  uint8_t is0 = 0;
  if (action == LOFIRST) {
      for (rest=N; rest>0; rest = rest / 10){
	if(rest%10>pivot)
	  solution = concat(rest%10, solution);
      }
      solution = solution / 10;
      if (solution == 0)
	is0=1;
      for (rest=N; rest>0; rest = rest / 10){
	if (rest%10==pivot){
	  solution = concat(Pivot, solution);
	  continue;
	}
      }
      if(is0)
      solution = solution/10;
      for (rest=N; rest>0; rest = rest / 10){
	if (rest%10<pivot)
	  solution = concat(rest%10, solution);
      }
      
  }
  else {
    for (rest=N; rest>0; rest = rest / 10){
      if(rest%10<pivot){
	  solution = concat(rest%10, solution);
      }
    }
    solution = solution / 10;
    if (solution == 0)
	is0=1;
    for (rest=N; rest>0; rest = rest / 10){
	if (rest%10==pivot)
	  solution = concat(Pivot, solution);
    }
    if(is0)
      solution = solution/10;
    if (solution == 0)
      solution = solution / 10;
    for (rest=N; rest>0; rest = rest / 10){
      if (rest%10>pivot)
	solution = concat(rest%10, solution);
    }
  }
  return solution;
}

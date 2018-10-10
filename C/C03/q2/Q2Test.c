#include "Q2Test.h"
#include "Q2Fns.h"

int Q2Test(int i1, int i2) {

   if ( t1( i1 ) ) {
      return 1;                  // A
	}
   else if ( t2( i1) ) {
      return 1;                  // B
	}
   else if ( t3( i1, i2 ) ) {
      return 1;                  // C
   }
   else if ( t4( i1, i2 ) ) {
      return 1;                  // D
	}
      
   return 0;                     // E
}


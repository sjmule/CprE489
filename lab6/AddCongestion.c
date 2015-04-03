/*****************************************************************************/
/*                                                                           */
/* This routine is called with a probability of bit error, p, and returns 1  */
/* if there is congestion, and 0 otherwise.                                  */
/*                                                                           */
/*****************************************************************************/

#include <stdlib.h>
#include <time.h>

long M = RAND_MAX;

int AddCongestion (double p)
{

	int c;
       	int seed;
	double r;
	seed =  (int) time( NULL);

	srandom(seed);

	c = 0;

	r = (double)random()/M;
	if ( r < p)
			c = 1;
	
	return (c);
}

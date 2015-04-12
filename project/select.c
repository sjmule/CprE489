/*
 * The following code will put the standard input and the socket descriptor
 * in the select function to be inspected for reading.  When the select
 * function returns, the descriptors are inspected to find out which one
 * is ready.   This code can be modified to handle files and sockets which
 * become ready for writing.
 */

#include <sys/time.h>

/* assume sd is the data channel socket & STDIN_FILENO is the
 * standard input file descriptor (it is 0)
 */

	int n;
	fd_set rset;		/* declare an fd_set for read descriptors */
	//...		

	for (;;) {	/* endless loop, if you want continuous operation */
		FD_ZERO(&rset);		/* clear all bits in rset */
		FD_SET(STDIN_FILENO, &rset);	/* set the standard input bit */
		FD_SET(sd, &rset);	/* set the socket descriptor bit */
 		n = select((sd>STDIN_FILENO? sd:STDIN_FILENO)+1, &rset, NULL, NULL, NULL);
		/* select blocks, and n is the number of ready descriptors */
		if ( (n == -1 ) && (errno == EINTR) ) /* interruption */
		   continue;
	  	if ((n== -1) {	/* error: you may handle it, if you want */
		 	/* code to handle errors */
	  	}
		/* after this point, handle the ready descriptor(s) */
	  
	  	/* check for ready data from the keyboard */

	  	if (FD_ISSET(STDIN_FILENO, &rset)) {
			//... /* read data from the standard input*/
			n--;
	  	}
	 
	  	/* check for ready data from the communication channel */

	  	if ((n > 0 ) && (FD_ISSET(sd, &rset)) ) {
			/* socket is ready for reading */
				//... /* read data from socket */
	  	}
	}
	 	



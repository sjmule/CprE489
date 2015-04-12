#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  pid_t pid;
  int status;

  if ((pid = fork()) > 0) {
    printf("Hello ");            /* This is the parent     */
    wait(&status);               /* wait for child to exit */
  } else if (pid == 0)
    printf("World!\n");          /* This is the child      */  
  else
    printf("fork failed\n");     /* no child created       */

  return 0;
}
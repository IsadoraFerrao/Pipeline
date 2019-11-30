/* C source code
 * ===========================================================================
 *
 *       Filename:  pipe_simples.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10-09-2010 15:45:22 BRT
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  
 *
 * ==========================================================================
 */

#include <stdio.h>

int main(int argc, char **argv)
{
    int shared_pipe[2];
    int outData=0;
    int inData = 100;

    pipe(shared_pipe);
    
    printf("[pid: %d] Processo corrente - outdata= %d\n", getpid(), outData);

    if( fork() == 0){ // child process
      printf("[pid: %d] Processo filho escreve no pipe[1]\n", getpid());
      close(shared_pipe[0]);
      write(shared_pipe[1], &inData, 4);
    }else{
      printf("[pid: %d] Processo pai antes de ler no pipe[0] outdata= %d -- ", getpid(), outData);
      close(shared_pipe[1]);
      read(shared_pipe[0], &outData, 4);
      printf("depois de ler outData= %d \n",outData);

    }
}

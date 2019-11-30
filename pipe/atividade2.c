#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    	int pipePaiFilho[2], pipeFilhoPai[2];
    	int outData;
    	int inData, i, n;
	char resultado[20];

	if(argc < 2){
		printf("Entrada precisa informar a quantidade de iterações\n");
		exit(0);
	}
	n = atoi(argv[1]);
	
	srandom(time(NULL));

    	pipe(pipePaiFilho);
	pipe(pipeFilhoPai);	
    
  if( fork() == 0){ // filho
	for(i=0; i<n; i++){
		inData = random()%100;
		close(pipePaiFilho[0]);
	      	write(pipePaiFilho[1], &inData, 4);
		close(pipeFilhoPai[1]);	
		read(pipeFilhoPai[0], resultado, sizeof(resultado));
	}
	close(pipePaiFilho[1]);
	close(pipeFilhoPai[0]);
  }else{//pai
	for(i=0; i<n; i++){	
		close(pipePaiFilho[1]);
      		read(pipePaiFilho[0], &outData, 4);
 		close( pipeFilhoPai[0]);
		if((outData%2)==0){
			write( pipeFilhoPai[1], "Par\n", (sizeof("Par\n")+1));	
		}
		else{
			write(pipeFilhoPai[1], "Impar\n", (sizeof("impar\n")+1));
		}
	}
	close(pipePaiFilho[0]);
	close(pipeFilhoPai[1]);
     }
}

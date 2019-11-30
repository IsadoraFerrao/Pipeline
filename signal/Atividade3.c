#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signal)
{
	printf("Cought signal %d!\n",signal);
	if (signal==SIGCHLD) {
		printf("[%d] Child ended\n", getpid());
		wait(NULL);
	}
}

int main()
{
	signal(SIGALRM,signalHandler);
	signal(SIGUSR1,signalHandler);
	signal(SIGCHLD,signalHandler);

	if (!fork()) {
		printf("[%d] Child running...\n", getpid());
		sleep(5);
		printf("[%d] Child sending SIGALRM...\n", getpid());
		kill(getppid(),SIGALRM); /*send alarm signal to parent*/
		sleep(5);
		printf("[%d] Child exitting...\n", getpid());
		return 0;
	}
	printf("Parent running, PID=%d. Press ENTER to exit.\n",getpid());
	getchar();
	printf("Parent exitting...\n");
	return 0;
}

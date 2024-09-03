#include "types.h"
#include "stat.h"
#include "user.h"




int addar(int *arrayofnums,int a,int b){

	int i;
	int so = 0;
	for(i=a;i<b;i++){
		so += arrayofnums[i];
	}	

	return so;


}



int child(int *a,int *b,int *fd,int *arrayofnums){
	int pid = fork();
	if (pid < 0){
		printf(1,"fork failed\n");
		return -1;
	}

	if(pid == 0){
	//	printf(1,"child proc\n");
		close(fd[0]);
		int localsum = addar(arrayofnums,*a,*b);
		write(fd[1],&localsum,sizeof(localsum));
		close(fd[1]);
		exit();
	}

	wait();
	*a += 10;
	*b += 10;

	return 0;
}





int main(int argc , char **argv){
	
	int arrayofnums[100];
	int i;
	int a = 0;
	int b =10;
	int fd[2];
	int SUM = 0;
	
	for(i=0;i<100;i++){
		arrayofnums[i] = i;

	}

	
	if(pipe(fd) < 0){
		printf(1,"pipe failed\n");
		exit();
	}


	
	while(b <= 100){
	if (child(&a,&b,fd,arrayofnums)< 0){
		printf(1,"failed\n");
		exit();
	}

	
	
	
		close(fd[1]);
		int localsum;
		read(fd[0],&localsum,sizeof(localsum));
		SUM += localsum;
	
	}


	printf(1,"answer is %d\n",SUM);
	exit();
	
	




	return 0;


}

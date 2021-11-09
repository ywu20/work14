#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>


void sigint_handle(){
 int fd = open("log.txt", O_CREAT|O_APPEND|O_WRONLY,0644);
 char str[] = "program exited due to SIGINT.\n";
 int a = write(fd,str,sizeof(str));
 printf("bytes written: %d\n",a);
 printf("errno: %s\n", strerror(errno));
 close (fd);
 exit(SIGINT);
}
static void sighandler(int signo){
 if(signo == SIGINT){
  sigint_handle();
 }
 else if (signo == SIGUSR1){
  printf("PPID: %d\n", getppid());
 }
}

int main(){
 while(1){
  printf("PID: %d\n", getpid());
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  sleep(1);
  
 }
 return 0;
}

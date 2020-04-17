//Q 3. write a program to send a message "end term practical" from parent process to child process.
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
int fd[2],n; 		//declare file descriptor in form of array with size 2
char buffer[100]; 	//array to store message
pid_t p; 	//pipe variable declaration where pid_t is datatype
pipe(fd); 	//create anonymous pipe
p=fork(); 	//create a child process
if(p>0) 	//parent
{
close(fd[0]);		 //close read end of pipe as parent wants to write
printf("Passing value to child\n");
write(fd[1],"End term practical\n",20); 	//write data to pipe from write end
sleep(1);
}
else 	// child
{
close(fd[1]);    //close write end of pipe as child wants to read
n=read(fd[0],buffer,100);     //read from pipe with help of read system call
write(1,buffer,n);        //write to buffer from where we can display message on screen
}
}

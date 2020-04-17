// Q.4 Write a program to display the last 10 characters of file on screen.
	
#include<stdio.h>
#include<stdlib.h> 
int main() 
{

FILE *fptr;
char ch;
int num;
long length;

printf("It will print the last 10 characters of a file on screen\n");

fptr = fopen("file1.txt", "r");    //Firstly open file in the read mode.
if (fptr == NULL) 
{
printf("cannot open this file\n");
printf("Please check whether file exists or not.\n");
exit(EXIT_FAILURE);
}

fseek(fptr, 0, SEEK_END);  //Now we need to accept position number so that we can start reading from that 				   //position. We are moving file pointer to the last location using fseek() 				   //function and passing SEEK_END constant.

length = ftell(fptr);      //Now we need to evaluate the current position of the file pointer.
			   //ftell() will tell you the location of file pointer.

fseek(fptr, (length - 10), SEEK_SET);  //We need to read last n characters from the file so we need to 					       //move pointer to (length-10) character back on the file. and from 					       //that location we need to read file.

do {
ch = fgetc(fptr);          //fgetc() - Used to read single character from file.
putchar(ch);
} while (ch != EOF);	   // read while end of file

fclose(fptr);              //Finally, close the file using fclose(fPtr)
return(0);
}

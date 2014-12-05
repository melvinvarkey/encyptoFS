#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "regs.c"
char* getpass();
int signup();
int crypto(){

	char username[BUFSIZ], *password="";  
  char buf[BUFSIZ];                 
  char *user_file, *pass_file;       
  char filename[]="psss";            
  FILE *infile;                     
	int flag=0;
	int emptyflag=0;
	char *crybuf;
  
  printf("Username: ");
  scanf("%s", username);
 
  password = getpass("Password: ");

 
  if((infile = fopen(filename, "r")) == NULL){

    printf("\nFile error!\nAborting...\n");
	
  } else {

  
  while (!feof(infile)) {

    
      buf[0] = '\0';
   
      fscanf(infile, "%s", buf);

      if(strlen(buf) == 0) continue;

      user_file = buf;

      pass_file = strchr(buf, ':');

      pass_file[0] = '\0';

      pass_file++;

      if(strcmp(user_file, username) == 0){

       	crybuf=crypt(password, pass_file);
 
 	if(strcmp(crybuf, pass_file) == 0){
       
	flag=1;

        } else {
	if(flag==0)
	
          printf("Invalid password!\n\n");
		
        }  
	        
        break;

      }  
		 
  	emptyflag=1;
	flag=999;
    }

  } 
if(strlen(buf)==0 && emptyflag==0){
printf("We could not find your Login credentials.Please Register :\n");
	flag=signup();
}
	
  
 fclose(infile);
return flag;
} 

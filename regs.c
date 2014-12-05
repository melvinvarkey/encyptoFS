#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <crypt.h>
char* getpass();
int signup(){
int flag=0;
  char salt[2];                                          
  const char *salt_chars = "abcdefghijklmnopqrstuvwxyz"  
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"  
                           "0123456789";

  char username[BUFSIZ],  password1[BUFSIZ],   
       password2[BUFSIZ], *buf;
  char filename[]="psss";                      
  FILE *outfile;                              

 
  srand(time(NULL));
  salt[0] = salt_chars[rand() % 62];
  salt[1] = salt_chars[rand() % 62];

  
  printf("Username: ");
  scanf("%s", username);

  do {

       buf = getpass("Password: ");

    sprintf(password1, "%s", buf);

    buf = getpass("Re-enter your password: ");

    sprintf(password2, "%s", buf);

   
    if(strcmp(password1, password2) != 0)
      printf("\nPasswords do not match!\nTry again.\n\n");

  } while(strcmp(password1, password2) != 0);

  
  buf = crypt(password1, salt);


  if((outfile = fopen(filename, "a+")) == NULL){

    printf("\nFile error!\nAborting...\n");
	
  } else {

 
    fprintf(outfile, "%s:%s\n", username, buf);
	flag=2;
  } 

  fclose(outfile);
	return flag;
}  

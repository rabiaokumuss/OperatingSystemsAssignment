#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<assert.h>

#define READ_END 0
#define WRITE_END 1

int main()
{
   char satir[300];
   char *ch;
   char *komut[5];
   char *cmd; 	
   int sayac=0;  
   int file=open("d.txt", O_WRONLY | O_CREAT);
   //int fd = open("test.txt", O_RDONLY);
while(1){
	
	printf(">");
	fgets(satir,sizeof(satir),stdin);
	satir[strlen(satir)-1]='\0';
	ch = strtok(satir, " ");
	fflush(stdout);
   
	if(!strcmp(satir,"quit")){
			exit(0);
	} 
    if(fork() == 0){
	 	cmd=ch;
		while (ch != NULL) {
			komut[sayac]=ch;
			ch = strtok(NULL, " ,");
			sayac++;
		}
		if(komut[2]==NULL){
			execvp(cmd, komut);
			while (ch != NULL) {
				komut[sayac]=NULL;
				sayac++;
			}
		}
		if(!strcmp(komut[1],">")||!strcmp(komut[2],">")){
			if(!strcmp(komut[1],">")){
				komut[1]=NULL;
				komut[3]=NULL;
			}	
			else if(!strcmp(komut[2],">")){
				komut[2]=NULL;
				komut[3]=NULL;
			}	
			dup2(file,1);
			execvp(cmd, komut);
			while (ch != NULL) {
				komut[sayac]=NULL;
				sayac++;
			}
			 close(file);  
		}
		
		exit(EXIT_FAILURE);
	}
    else if(fork() > 0)
    {
		
	// wait(NULL); 
      while(1);
    } 
    
    else if( fork() < 0)
    {   
      printf("Fork hatası!\n");
      exit(-1);
    }
    
   
} 
  return 0;
}

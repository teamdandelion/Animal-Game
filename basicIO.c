#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

int getYesNo();
char* getLine(FILE *fp);

char *getLine(FILE *fp){
    static char *buf = NULL;
    static size_t buf_size=0;
    
    if (buf==NULL){
    buf_size=512;
    buf = (char *) calloc (buf_size,sizeof(char));
    assert(buf!=NULL);
    }

int ch;

while(!isalpha (ch=fgetc(fp))){
    if (ch==EOF)
        return NULL;
}

//scans past whitespace

int index=0;

while(ch!='\n' && ch != EOF){
    //invariants:
    //index < buf_size
    //buf points to buffer of size buf_size
    //buf[0]..buf[index-1] consists of preceding characters in the line
    buf[index++]=ch;
    
    if (index==buf_size){
        buf_size*=2;
        buf=realloc(buf,buf_size);
        assert (buf!=NULL);
    }
    ch=fgetc(fp); //Equivalent to do...while, but I prefer the simpler syntax
}

buf[index]='\0';
return buf;
}


int getYesNo(){
    int ch;
//    while ( (ch=getchar()) != '\n' && ch !=EOF)
//        ;//got this from StackOverflow to 
// clear the input buffer
    printf(" (y/n): ");
    while ( (ch=getchar()) != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')
        ;
    if (ch == 'y' || ch=='Y')
        return 1;
    else
        return 0;
}
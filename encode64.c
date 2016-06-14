#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <b64.h>

#define MAXIN       30000
#define MAXOUT      64000

FILE *file_ptr;

int main(int argc, char *argv[] ) 
{
    int c;
    unsigned char in[MAXIN];
    unsigned char out[MAXOUT];
    char filename[50];
    int inlen=0;
    int outlen;
    if ( argc < 1 )
    {
         printf("%s\n","Missing arguments");  
         exit(1);
    }
    else
    {
         sprintf( filename , "%s",argv[1]);
    }
    setvbuf(stdout, NULL, _IOLBF, MAXOUT );

    file_ptr= fopen(filename, "rb");

    fseek(file_ptr, 0 , SEEK_END);
    inlen = ftell(file_ptr);
    fseek( file_ptr, 0, SEEK_SET);
    
    fread( in , inlen, 1 , file_ptr);

    b64_encode( &in, inlen, out, MAXOUT );

    outlen = strlen(out);
    printf("%d\n",outlen);

    printf("%s",out);
    exit(0);
}
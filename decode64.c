#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <b64.h>

#define MAXIN		30000
#define MAXOUT		64000
	
FILE *file_ptr;
FILE *fileo_ptr;

int main(int argc, char *argv[] ) 
{
    int c;
    unsigned char in[MAXIN];
    unsigned char out[MAXOUT];
    char filename[50];
    char *fileout;
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
  /*    setvbuf(stdout, NULL, _IOLBF, MAXOUT ); */

    file_ptr= fopen(filename, "r");

    fseek(file_ptr, 0 , SEEK_END);
    inlen = ftell(file_ptr);
    fseek( file_ptr, 0, SEEK_SET);
    
    fread( in, inlen, 1 , file_ptr);

    printf("%d\n", inlen);

    outlen = b64_decode(in ,inlen , NULL , 0);

    printf("%d\n",outlen);

    b64_decode( in, inlen, out, outlen );
     
    printf("%s",out);
    fileout = "/home/tmp/sigout.tiff";
    fileo_ptr= fopen(fileout, "wb");
   	
    fwrite( out , outlen , 1 , fileo_ptr );
    
    fclose(file_ptr);
    fclose(fileo_ptr);
   	
    exit(0);
}

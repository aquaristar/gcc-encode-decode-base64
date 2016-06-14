#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <b64.h>

#define MAXIN		30000
#define MAXOUT		64000
	
FILE *file_ptr;
FILE *fileo_ptr;

int Base64Decode(char* b64message, unsigned char** buffer, size_t* length) { //Decodes a base64 encoded string
  BIO *bio, *b64;

  int decodeLen = calcDecodeLength(b64message);
  *buffer = (unsigned char*)malloc(decodeLen + 1);
  (*buffer)[decodeLen] = '\0';

  bio = BIO_new_mem_buf(b64message, -1);
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_push(b64, bio);

  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Do not use newlines to flush buffer
  *length = BIO_read(bio, *buffer, strlen(b64message));
  assert(*length == decodeLen); //length should equal decodeLen, else something went horribly wrong
  BIO_free_all(bio);

  return (0); //success
}

int main(int argc, char *argv[] ) 
{
    int c;
    unsigned char in[MAXIN];
    unsigned char out[MAXOUT];
    char* base64DecodeOutput;
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
/*  setvbuf(stdout, NULL, _IOLBF, MAXOUT ); */

    file_ptr= fopen(filename, "r");

    fseek(file_ptr, 0 , SEEK_END);
    inlen = ftell(file_ptr);
    fseek( file_ptr, 0, SEEK_SET);
    
    fread( in , inlen, 1 , file_ptr);

    printf("%d\n", inlen);

    //outlen = b64_decode(in, inlen , NULL , 0);
    //printf("%d\n",outlen);
    //b64_decode( in, inlen, out, outlen );

    Base64Decode( in, &base64DecodeOutput, outlen );

    printf("%s", out);
    fileout = "/home/tmp/sigout.tiff";
    fileo_ptr= fopen(fileout, "wb");
   	
    fwrite( out , outlen , 1 , fileo_ptr );
    
    fclose(file_ptr);
    fclose(fileo_ptr);
   	
    exit(0);
}

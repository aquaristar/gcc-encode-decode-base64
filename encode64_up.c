#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>  
#include <openssl/bio.h>  
#include <openssl/buffer.h> 

#define MAXIN       30000
#define MAXOUT      64000

FILE *file_ptr;

size_t bc_base64_encode(const void *data, int data_len, char *buffer)
{
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new(BIO_s_mem());

    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, data, data_len);
    BIO_ctrl(bio, BIO_CTRL_FLUSH, 0, NULL);

    BUF_MEM *bptr = NULL;
    BIO_get_mem_ptr(bio, &bptr);

    size_t slen = bptr->length;
    memcpy(buffer, bptr->data, slen);
    buffer[slen] = '\0';

    BIO_free_all(bio);
    return slen;
}

int Base64Encode(const unsigned char* buffer, size_t length, char** b64Output) { 
    BIO *bio;
    BIO *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); 
    BIO_write(bio, buffer, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    *b64Output = (*bufferPtr).data;

    return (0);
}

int main(int argc, char *argv[] ) 
{
    int c;
    unsigned char in[MAXIN];
    unsigned char out[MAXOUT];
    char* base64EncodeOutput;
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

    //  b64_encode( &in, inlen, out, MAXOUT );

    //outlen = bc_base64_encode(&in, &inlen, &out);
    Base64Encode(in, inlen, &base64EncodeOutput);

    outlen = strlen(base64EncodeOutput);
    printf("%d\n",outlen);
    
    printf("%s",base64EncodeOutput);
    exit(0);
}



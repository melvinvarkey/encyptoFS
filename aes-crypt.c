
#include "aes-crypt.h"

#define BLOCKSIZE 1024
#define FAILURE 0
#define SUCCESS 1

extern int do_crypt(FILE* in, FILE* out, int action, char* key_str){
   

    unsigned char inbuf[BLOCKSIZE];
    int inlen;
   
    unsigned char outbuf[BLOCKSIZE + EVP_MAX_BLOCK_LENGTH];
    int outlen;
    int writelen;

    EVP_CIPHER_CTX ctx;
    unsigned char key[32];
    unsigned char iv[32];
    int nrounds = 5;
  
    int i;
      if(action >= 0){
        if(!key_str){
           
            fprintf(stderr, "Key_str must not be NULL\n");
            return 0;
        }
       
        i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), NULL,
                (unsigned char*)key_str, strlen(key_str), nrounds, key, iv);
        if (i != 32) {
          
            fprintf(stderr, "Key size is %d bits - should be 256 bits\n", i*8);
            return 0;
        }
       
        EVP_CIPHER_CTX_init(&ctx);
        EVP_CipherInit_ex(&ctx, EVP_aes_256_cbc(), NULL, key, iv, action);
    }    

   
    for(;;){
       
        inlen = fread(inbuf, sizeof(*inbuf), BLOCKSIZE, in);
        if(inlen <= 0){
           
            break;
        }

       
        if(action >= 0){
            if(!EVP_CipherUpdate(&ctx, outbuf, &outlen, inbuf, inlen))
            {
               
                EVP_CIPHER_CTX_cleanup(&ctx);
                return 0;
            }
        }
       
        else{
            memcpy(outbuf, inbuf, inlen);
            outlen = inlen;
        }

        writelen = fwrite(outbuf, sizeof(*outbuf), outlen, out);
        if(writelen != outlen){
           
            perror("fwrite error");
            EVP_CIPHER_CTX_cleanup(&ctx);
            return 0;
        }
    } 

 
    if(action >= 0){
        
        if(!EVP_CipherFinal_ex(&ctx, outbuf, &outlen))
        {
            EVP_CIPHER_CTX_cleanup(&ctx);
            return 0;
        }
       
        fwrite(outbuf, sizeof(*inbuf), outlen, out);
        EVP_CIPHER_CTX_cleanup(&ctx);
    }

    
    return 1;
}

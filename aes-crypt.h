
#ifndef AES_CRYPT_H
#define AES_CRYPT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/aes.h>

#define BLOCKSIZE 1024
#define FAILURE 0
#define SUCCESS 1

extern int do_crypt(FILE* in, FILE* out, int action, char* key_str);

#endif

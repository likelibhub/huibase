


#include "des.h"

#include <openssl/des.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#include <hadaptation.h>

namespace HUIBASE {

namespace CRYPTO{


HSTR DesNcbcEncrypt (HCSTRR clearText, HCSTRR key)
{
    std::string cipherText;

    DES_cblock keyEncrypt;
    memset(keyEncrypt, 0, 8);

    if (key.length() <= 8)
        memcpy(keyEncrypt, key.c_str(), key.length());
    else
        memcpy(keyEncrypt, key.c_str(), 8);

    DES_key_schedule keySchedule;
    DES_set_key_unchecked(&keyEncrypt, &keySchedule);

    const_DES_cblock inputText;
    DES_cblock outputText;
    std::vector<unsigned char> vecCiphertext;
    unsigned char tmp[8];

    for (size_t i = 0; i < clearText.length() / 8; i++)
    {
        memcpy(inputText, clearText.c_str() + i * 8, 8);
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
        memcpy(tmp, outputText, 8);

        for (int j = 0; j < 8; j++)
            vecCiphertext.push_back(tmp[j]);
    }

    if (clearText.length() % 8 != 0)
    {
        int tmp1 = clearText.length() / 8 * 8;
        int tmp2 = clearText.length() - tmp1;
        memset(inputText, 0, 8);
        memcpy(inputText, clearText.c_str() + tmp1, tmp2);

        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
        memcpy(tmp, outputText, 8);

        for (int j = 0; j < 8; j++)
            vecCiphertext.push_back(tmp[j]);
    }

    cipherText.clear();
    cipherText.assign(vecCiphertext.begin(), vecCiphertext.end());

    return cipherText;
}


HSTR DesNcbcDecrypt (HCSTRR cipherText, HCSTRR key) {
    std::string clearText;

    DES_cblock keyEncrypt;
    memset(keyEncrypt, 0, 8);

    if (key.length() <= 8)
        memcpy(keyEncrypt, key.c_str(), key.length());
    else
        memcpy(keyEncrypt, key.c_str(), 8);

    DES_key_schedule keySchedule;
    DES_set_key_unchecked(&keyEncrypt, &keySchedule);

    const_DES_cblock inputText;
    DES_cblock outputText;
    std::vector<unsigned char> vecCleartext;
    unsigned char tmp[8];

    for (size_t i = 0; i < cipherText.length() / 8; i++)
    {
        memcpy(inputText, cipherText.c_str() + i * 8, 8);
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
        memcpy(tmp, outputText, 8);

        for (int j = 0; j < 8; j++)
            vecCleartext.push_back(tmp[j]);
    }

    if (cipherText.length() % 8 != 0)
    {
        int tmp1 = cipherText.length() / 8 * 8;
        int tmp2 = cipherText.length() - tmp1;
        memset(inputText, 0, 8);
        memcpy(inputText, cipherText.c_str() + tmp1, tmp2);

        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
        memcpy(tmp, outputText, 8);

        for (int j = 0; j < 8; j++)
            vecCleartext.push_back(tmp[j]);
    }

    clearText.clear();
    clearText.assign(vecCleartext.begin(), vecCleartext.end());

    return clearText;
    }


    HRET Des3Encrypt (HUPSZ in, HINT inlen, HUPSZ out, HINT* outlen, HCSTRR password) {
        const EVP_CIPHER * cipher = EVP_des_ede3_ecb( );

        HASSERT_THROW(cipher != nullptr, SSL_ERR);

        unsigned char key[EVP_MAX_KEY_LENGTH];
        unsigned char iv[EVP_MAX_KEY_LENGTH];

        EVP_BytesToKey(cipher,EVP_md5(), nullptr, (HCUPSZ)password.c_str(), password.size(), 1, key, iv);

        EVP_CIPHER_CTX ctx;
        EVP_CIPHER_CTX_init(&ctx);

        EVP_CIPHER_CTX_set_padding(&ctx,0);

        int rv = EVP_EncryptInit_ex(&ctx, cipher, nullptr, key, iv);

        if(rv != 1){

            EVP_CIPHER_CTX_cleanup(&ctx);
            HASSERT_THROW(false, SSL_ERR);

        }

        rv = EVP_EncryptUpdate(&ctx,out, outlen, in, inlen);

        if(rv != 1){

            EVP_CIPHER_CTX_cleanup(&ctx);
            HASSERT_THROW(false, SSL_ERR);
        }

        HINT templen = 0;
        rv = EVP_EncryptFinal_ex(&ctx,out + *outlen, &templen);

        if(rv != 1) {

            EVP_CIPHER_CTX_cleanup(&ctx);
            HASSERT_THROW(false, SSL_ERR);

        }


        EVP_CIPHER_CTX_cleanup(&ctx);

        *outlen += templen;

        HRETURN_OK;
    }


    HRET Des3Decrypt (HUPSZ in, HINT inlen, HUPSZ out, HINT* outlen, HCSTRR password) {

        const EVP_CIPHER * cipher = EVP_des_ede3_ecb( );
        HASSERT_THROW(cipher != nullptr, SSL_ERR);

        unsigned char key[EVP_MAX_KEY_LENGTH];
        unsigned char iv[EVP_MAX_KEY_LENGTH];

        EVP_BytesToKey(cipher, EVP_md5(), nullptr, (HCUPSZ)password.c_str(), password.size(), 1, key, iv);

        EVP_CIPHER_CTX ctx;
        EVP_CIPHER_CTX_init(&ctx);

        int rv = EVP_DecryptInit_ex(&ctx, cipher, nullptr, key, iv);

        if(rv != 1) {

            EVP_CIPHER_CTX_cleanup(&ctx);
            HASSERT_THROW(false, SSL_ERR);

        }

        rv = EVP_DecryptUpdate(&ctx,out, outlen, in, inlen);
        if(rv != 1) {

            EVP_CIPHER_CTX_cleanup(&ctx);
            HASSERT_THROW(false, SSL_ERR);

        }

        HINT templen = 0;
        rv = EVP_DecryptFinal_ex(&ctx,out + *outlen, &templen);
        if(rv != 1) {

            EVP_CIPHER_CTX_cleanup(&ctx);
            HASSERT_THROW(false, SSL_ERR);

        }

        EVP_CIPHER_CTX_cleanup(&ctx);

        *outlen += templen;

        HRETURN_OK;
    }



    HRET Des3Encrypt (HMEMR src, HMEMR dst, HCSTRR passwd) {

        HINT src_len = src.size() * 2;
        HUPSZ out = new HUCHAR[src_len];
        CHECK_NEWPOINT(out);

        ZERO_MEM(out, src_len);

        HRET cb = 0;

        do {

            cb = Des3Encrypt (&src[0], src.size(), out, &src_len, passwd);

        } while (0);

        std::copy(out, out + src_len, std::back_inserter(dst));

        HDEL_ARR(out);

        return cb;

    }



    HRET Des3Encrypt (HCSTRR src, HMEMR mem, HCSTRR passwd) {

        HMEM src_mem;

        hstr_uvs (src, src_mem);

        return Des3Encrypt (src_mem, mem, passwd);

    }


    HRET Des3Decrypt (HMEMR src, HMEMR dst, HCSTRR passwd) {

        HINT out_len = src.size() * 2;
        HUPSZ out = new HUCHAR[out_len];
        CHECK_NEWPOINT(out);

        ZERO_MEM(out, out_len);

        HRET cb = 0;

        do {

            cb = Des3Decrypt (&src[0], src.size(), out, &out_len, passwd);

        } while (0);

        std::copy (out, out + out_len, std::back_inserter(dst));

        HDEL_ARR(out);

        return cb;

    }

}


}

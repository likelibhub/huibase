


#ifndef __HUIBASE_DES_H__
#define __HUIBASE_DES_H__


#include <huibase.h>


namespace HUIBASE {


namespace CRYPTO {

    HSTR DesNcbcEncrypt (HCSTRR str, HCSTRR strPw);


    HSTR DesNcbcDecrypt (HCSTRR str, HCSTRR strPw);


    HRET Des3Encrypt (HUPSZ in, HINT inlen, HUPSZ out, HINT* outlen, HCSTRR password);


    HRET Des3Decrypt (HUPSZ in, HINT inlen, HUPSZ out, HINT* outlen, HCSTRR password);


    HRET Des3Encrypt (HMEMR src, HMEMR dst, HCSTRR passwd);


    HRET Des3Encrypt (HCSTRR src, HMEMR dst, HCSTRR passwd);


    HRET Des3Decrypt (HMEMR src, HMEMR dst, HCSTRR passwd);

}


}


#endif //__HUIBASE_DES_H__

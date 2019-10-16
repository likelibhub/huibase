

#ifndef __HCRYPTO_COMM_H__
#define __HCRYPTO_COMM_H__

#include <huibase.h>

namespace HUIBASE {

    namespace CRYPTO {

        HRET HEncode (HCSTRR strin, HSTRR strout);


        HRET HDecode (HCSTRR strin, HSTRR strout);

    }

}


#endif //__HCRYPTO_H__

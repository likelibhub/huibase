


#include "hcrypto.h"
#include "urlencode.h"
#include "hadaptation.h"
#include "base64.h"

namespace HUIBASE {


    namespace CRYPTO {


        HRET HEncode (HCSTRR strin, HSTRR strout) {

            HMEM base_mem;
            CBase64::Encode (strin, base_mem);

            HSTR strBase = huvs_str(base_mem);

            strout = UrlEncode (strBase);

            HRETURN_OK;
        }


        HRET HDecode (HCSTRR strIn, HSTRR strOut) {

            HSTR strUnUrl = UrlDecode (strIn);

            HMEM base_mem, src_mem;
            hstr_uvs(strUnUrl, base_mem);

            CBase64::Decode(base_mem, src_mem);

            strOut = huvs_str(src_mem);

            HRETURN_OK;

        }



    }



}

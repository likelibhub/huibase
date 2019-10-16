


#ifndef __BINBCD_H__
#define __BINBCD_H__

#include <huibase.h>

namespace HUIBASE {


    namespace CRYPTO {

        HRET Bin2BcdStr (HCUPSZ cusz, HINT len, HUPSZ usz, HINT rlen);


        HCHAR IntToBcd (HINT n);


        HINT BcdToInt (HUINT n);


        HINT BcdStr2Bin (HPSZ dst, HINT dst_len, HCPSZ src);


        HINT Str2Bcd (HPSZ sz_bcd, HCPSZ sz_str, HINT max_len);

    }

}

#endif //__BIN2BCD_H__

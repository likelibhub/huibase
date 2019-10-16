

#include <sys/time.h>
#include "hadaptation.h"

namespace HUIBASE {

    HRET hsleep (HUINT nSec, HUINT nMiSec) {

        struct timeval tval = {0, 0};
        tval.tv_sec = nSec;
        tval.tv_usec = nMiSec;

        auto cb = select (0, nullptr, nullptr, nullptr, &tval);

        HASSERT_RETURN(cb == 0, SYS_FAILED);

        HRETURN_OK;

    }

    HCSTRR hcmap_get (HCPSR ps, HCSTRR strKey) {

        HPS::const_iterator cit = ps.find(strKey);

        HASSERT_THROW_MSG(cit != ps.end(), "hcmap_get pos out", POS_END);

        return cit->second;

    }


    HUINT hget_rand (HUINT n) {

        struct timeval tv = {0,0};
        (void) gettimeofday(&tv, nullptr);

        (void)srand((unsigned int)tv.tv_usec);

        HUINT res = rand();

        return n != 0 ? res % n : res;

    }


}

/*******************************************************
 *
 * FileName: hmemcached.h
 *
 * Author: Tom Hui, tomhui1009@yahoo.com, 8613760232170
 *
 * Create Date: Sat Jun 09 17:04 2018
 *
 * Brief:
 *   Wrapper for memcached. This library depend on
 * libmemcached.
 *
 *******************************************************/

#ifndef __H_MEMCACHED_H__
#define __H_MEMCACHED_H__

#include <libmemcached/memcached.h>
#include "nosql_comm.h"
#include <huibase.h>

namespace HUIBASE {

    namespace NOSQL {

        class CMemcached {
        public:
            static constexpr HUINT MEM_BUF_LEN = 20480;

        public:
            CMemcached (const NoSqlConnectionInfo& info);

            ~ CMemcached ();

            HRET Set (HCSTRR strKey, HCSTRR strValue, HTIME extt = 0) throw (HCException);

            HRET Get (HCSTRR strKey, HSTRR strValue) throw (HCException);

            HRET Delete (HCSTRR strkey) throw (HCException);

            HBOOL Exists (HCSTRR strKey) throw (HCException);

            HUINT Increment (HCSTRR strKey, HUINT offset) throw (HCException);

            HUINT Decrement (HCSTRR strKey, HUINT offset) throw (HCException);

            HRET Add (HCSTRR strKey, HCSTRR strVal, HTIME nexpir = 0) throw (HCException);

            HBOOL NotDouble (HCSTRR strKey, HCSTRR strVal, HTIME nexpir = 20) throw (HCException);

        private:
            memcached_st* m_st = nullptr;
        };

    }


}


#endif //__H_MEMCACHED_H__

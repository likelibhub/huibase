


#include "simpleconn.h"

namespace HUIBASE {


    namespace HMYSQL {


        CSimpleConn::CSimpleConn (HCSTRR strHost, HCSTRR strDb, HCSTRR strUser, HCSTRR strPass, HUINT nPort)
            : CMysqlConnDrive (strDb, strHost, strUser, strPass, nPort) {  }



        HRET CSimpleConn::Query(HCSTRR sql, CRes& res) throw (HCException) {

            HASSERT_THROW_MSG(HIS_TRUE(IsInited()), "mysql db is not connected", UN_INIT);

            HFAILED_MSG(Execute(sql), "query mysql failed");


            HFAILED_MSG(StoreResult(res), "store query result failed");

            HRETURN_OK;
        }


        HRET CSimpleConn::Exec(HCSTRR sql) throw (HCException) {

            HASSERT_THROW_MSG(HIS_TRUE(IsInited()), "mysql db is not connected", UN_INIT);

            HFAILED_MSG(Execute(sql), "query mysql failed");

            HRETURN_OK;
        }

    }

}

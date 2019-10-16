/*****************************************************************************
 *
 * FileName: simpledb.h
 *
 * Author: Tom Hui, tomhui1009@yahoo.com, 8613760232170
 *
 * Create Date: Sat Aug 04 13:21 2018
 *
 * Brief:
 *   Provides a simple mysql connection class base the mysql connection drive.
 *   This connection class only use to short connection application.
 *
 *****************************************************************************/


#ifndef __SIMPLECONN_H__
#define __SIMPLECONN_H__

#include "mysqlconndrive.h"


namespace HUIBASE {

    namespace HMYSQL {

        class CSimpleConn : public CMysqlConnDrive {
        public:
            CSimpleConn () { }

            CSimpleConn (HCSTRR strhost, HCSTRR strDb, HCSTRR strUser, HCSTRR strPass, HUINT nPort);

            CSimpleConn (const CSimpleConn& sc) = delete;

        public:
            HRET Query (HCSTRR sql, CRes& res) throw (HCException);

            HRET Exec (HCSTRR sql) throw (HCException);

        };

    }


}



#endif //__SIMPLECONN_H__

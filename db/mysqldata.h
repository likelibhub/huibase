/*****************************************************************************
 *
 * FileName: mysqldata.h
 *
 * Author: Tom Hui, tomhui1009@yahoo.com, 8613760232170
 *
 * Create Date: Sun Jul 29 17:25 2018
 *
 * Brief:
 *       Wrapper class for MYSQL_RES, MYSQL_ROW.
 *
 *****************************************************************************/

#ifndef __MYSQLDATA_H__
#define __MYSQLDATA_H__

#include <huibase.h>
#include <hdict.h>
#include <mysql.h>

namespace HUIBASE {

    namespace HMYSQL{

        class CRow : public HCParam {
        public:
            typedef HVSTRS base;
            typedef base::iterator iterator;
            typedef base::const_iterator const_iterator;
            typedef base::const_reference const_reference;

        public:
            CRow () { }

            //CRow (const CRow&);

        };

        class CRes: public std::vector<CRow> {
        public:
            typedef std::vector<CRow> base;
            typedef base::iterator iterator;
            typedef base::const_iterator const_iterator;
            typedef base::const_reference const_reference;

            typedef base::size_type size_type;
            typedef base::value_type value_type;

        public:
            CRes (MYSQL_RES* res);

            void SetRes (MYSQL_RES* res);

        private:
            void pushRes (MYSQL_RES* res);
        };


    }

}


#endif //__MYSQLDATA_H__



#include "mysqldata.h"



namespace HUIBASE {

    namespace HMYSQL {

        //CRow::CRow(const CRow& row)
        //: HCParam(row.cbegin(), row.cend()) { }



        CRes::CRes(MYSQL_RES* res) {

            pushRes(res);

        }


        void CRes::SetRes(MYSQL_RES* res) {

            pushRes(res);

        }


        void CRes::pushRes(MYSQL_RES* res) {

            if (res) {

                HUINT filed_num = mysql_num_fields (res);

                MYSQL_FIELD* field = nullptr;
                MYSQL_ROW __row;

                HVSTRS names;

                while ((field = mysql_fetch_field(res))) {

                    names.push_back(field->name);

                }

                while ((__row = mysql_fetch_row(res))) {

                    CRow row;
                    for (HINT i = 0; i < filed_num; ++i) {

                        row.setValue (names[i], __row[i] ? __row[i] : "NULL");

                    }

                    push_back(row);

                }

            }

        }


    }

}

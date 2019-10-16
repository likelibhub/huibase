
#include <sstream>
#include "mysqlconndrive.h"

namespace HUIBASE {

namespace HMYSQL {

CMysqlConnDrive::CMysqlConnDrive()
    : m_st(nullptr){

    init();

}


CMysqlConnDrive::CMysqlConnDrive(HCSTRR db, HCSTRR host, HCSTRR user, HCSTRR pw,
				   HINT port)
    : m_db(db), m_host(host), m_port(port), m_user(user), m_pw(pw) {

    init ();

}


CMysqlConnDrive::~CMysqlConnDrive() {

    uninit();

}


HRET CMysqlConnDrive::Connect(HUINT nConnectTimeout, HUINT nReadTimeout, HBOOL bRec){

    HASSERT_RETURN(m_st != nullptr, UN_INIT);

    if (nConnectTimeout != 0) {

        HNOTOK_RETURN(SetConnectTimeout(nConnectTimeout));

    }

    if (nReadTimeout != 0) {

        HNOTOK_RETURN(SetReadTimeout(nReadTimeout));

    }


    HNOTOK_RETURN(SetReconnect(bRec));

    m_st = mysql_real_connect(m_st, m_host.c_str(), m_user.c_str(), m_pw.c_str(), m_db.c_str(), m_port, nullptr, 0);

    if (not m_st) {
        HRETURN(DB_DISCONN);
    }

    HRETURN_OK;
}


HRET CMysqlConnDrive::Disconnect() {

    IF_TRUE(IsInited()) {

        mysql_close(m_st);

        m_st = nullptr;

    }

}


void CMysqlConnDrive::SetConnInfo(const CONN_INFO &ci) {

    m_db = ci.m_db;
    m_host = ci.m_host;
    m_port = ci.m_port;
    m_user = ci.m_user;
    m_pw = ci.m_pw;
    
}


HULL CMysqlConnDrive::GetAffectedRows() {

    if (m_st == nullptr) {
        return 0;
    }

    return mysql_affected_rows(m_st);

}


HSTR CMysqlConnDrive::GetClientVersion() {

    if (m_st == nullptr) {
        return "Error Mysql Client Version";
    }

    return mysql_get_client_info();

}


HRET CMysqlConnDrive::Execute(HCSTRR sql) {

    CHECK_DBST;

    HASSERT_RETURN(mysql_real_query(m_st, sql.c_str(), sql.length()) == 0, QRY_ERR);

    HRETURN_OK;

}


HRET CMysqlConnDrive::StoreResult(CRes& res) {

    CHECK_DBST;

    MYSQL_RES* cb_res = mysql_store_result(m_st);

    if (cb_res == nullptr) {

        HRETURN_OK;

    }

    res.SetRes(cb_res);

    mysql_free_result(cb_res);

    HRETURN_OK;
}


HRET CMysqlConnDrive::UseResult(CRes& res) {

    CHECK_DBST;

    MYSQL_RES* cb_res = mysql_use_result(m_st);

    if (cb_res == nullptr) {

        HRETURN_OK;

    }

    res.SetRes(cb_res);

    mysql_free_result(cb_res);

    HRETURN_OK;
}


HULL CMysqlConnDrive::GetNewId() {

    CHECK_DBST;

    return (HULL) mysql_insert_id(m_st);

}


HBOOL CMysqlConnDrive::Ping() {

    if (m_st == nullptr) {
        return HFALSE;
    }

    HRET_BOOL(mysql_ping(m_st) == 0);

}


HSTR CMysqlConnDrive::Profile() {

    stringstream ss;
    ss << "host[" << m_host << "]"
       << " port[" << m_port << "]";

    return ss.str();
    
}


HRET CMysqlConnDrive::SetUtf8() {

    HASSERT_RETURN(m_st != nullptr, UN_INIT);

    HASSERT_RETURN(mysql_options(m_st, MYSQL_SET_CHARSET_NAME, "utf8") == 0, QRY_ERR);

    HRETURN_OK;

}


HRET CMysqlConnDrive::SetReconnect(HBOOL b) {

    HASSERT_RETURN(m_st != nullptr, UN_INIT);

    my_bool recb = b == HTRUE ? 1 : 0;
    HASSERT_RETURN(mysql_options(m_st, MYSQL_OPT_RECONNECT, &recb) == 0, QRY_ERR);

    HRETURN_OK;
}


HRET CMysqlConnDrive::SetConnectTimeout(HUINT nTimeout) {

    HASSERT_RETURN(m_st != nullptr, UN_INIT);

    HASSERT_RETURN(mysql_options(m_st, MYSQL_OPT_CONNECT_TIMEOUT, &nTimeout) == 0, QRY_ERR);

    HRETURN_OK;
}


HRET CMysqlConnDrive::SetReadTimeout(HUINT nTimeout) {

    HASSERT_RETURN(m_st != nullptr, UN_INIT);

    HASSERT_RETURN(mysql_options(m_st, MYSQL_OPT_READ_TIMEOUT, &nTimeout) == 0, QRY_ERR);

    HRETURN_OK;

}


void CMysqlConnDrive::init() {

    /*
     * In a nonmultithreaded environment, mysql_init() invokes mysql_library_init() automatically as necessary. However, mysql_library_init() is not thread-safe in a multithreaded environment, and thus neither is mysql_init. Before calling mysql_init(), either call mysql_library_init prior to spawning any threads, or use a mutex to protect the mysql_library_init() call. This should be done prior to any other client library call.
     */
    // Before calling mysql_init(), call mysql_library_init prior.
    (void) mysql_library_init(0, nullptr, nullptr);

    m_st = mysql_init (nullptr);
    HASSERT_THROW_MSG(m_st != nullptr, "mysql_init failed", MEMORY_OUT);

}


void CMysqlConnDrive::uninit() {

    if (m_st != nullptr) {

        mysql_close(m_st);

        /*
         * To avoid memory leaks after the application is done using the library, be sure to call mysql_library_end() explicitly. This enables memory managment to be performed to clean up and free resources used by the library.
         */
        (void) mysql_library_end();

    }

}


}

}

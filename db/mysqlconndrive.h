/*******************************************************
 *
 * FileName: dbdrive.h
 *
 * Author: Tom Hui, tomhui1009@yahoo.com, 8613760232170
 *
 * Create Date: Sat Jul 28 15:45 2018
 *
 * Brief:
 *   Provides a thin abstraction layer over the underlying
 *   database client library.
 *   This class does as little as possible to adapt between
 *   its public interface and the interface require by
 *   underlying C API. That is, in fact, its only mission.
 *
 *******************************************************/



#ifndef __MYSQLCONNDRIVE_H__
#define __MYSQLCONNDRIVE_H__


#include <huibase.h>
#include <hstr.h>
#include "mysqldata.h"


namespace HUIBASE {

namespace HMYSQL {

typedef struct {
    HSTR m_host;
    HINT m_port;
    HSTR m_user;
    HSTR m_pw;
    HSTR m_db;
}CONN_INFO;

class CMysqlConnDrive {
#define CHECK_DBST HASSERT_RETURN(m_st != nullptr, UN_INIT)

public:
    CMysqlConnDrive();

    CMysqlConnDrive(HCSTRR db, HCSTRR host, HCSTRR user, HCSTRR pw,
		     HINT port);

    CMysqlConnDrive(const CMysqlConnDrive& conn) = delete;

    CMysqlConnDrive(CMysqlConnDrive&& conn)
        : m_st(conn.m_st) { conn.m_st = nullptr;  }

    virtual ~CMysqlConnDrive ();

    HBOOL IsInited () const { HRET_BOOL(m_st != nullptr); }

    HRET Connect (HUINT nConnectTimeout = 1, HUINT nReadTimeout = 1, HBOOL bRec = HTRUE);

    HRET Disconnect ();

    void SetConnInfo (const CONN_INFO& ci);

    HULL GetAffectedRows ();

    HSTR Profile ();

    HRET SetUtf8 ();

    HSTR GetClientVersion ();

    HRET Execute (HCSTRR sql);

    HRET StoreResult (CRes & res);

    HRET UseResult (CRes& res);

    HULL GetNewId ();

    HBOOL Ping ();

    HRET SetReconnect (HBOOL b = HTRUE);

    HRET SetConnectTimeout (HUINT nTimeout = 1);

    HRET SetReadTimeout (HUINT nTimeout = 1);

private:
    void init ();

    void uninit ();


private:
    HSTR m_db;
    HSTR m_host;
    HINT m_port;
    HSTR m_user;
    HSTR m_pw;

    MYSQL * m_st = nullptr;
};

}

}

#endif //__MYSQLCONNDRIVE_H__

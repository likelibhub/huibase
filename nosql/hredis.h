/*******************************************************
 *
 * FileName: hredis.h
 *
 * Author: Tom Hui, tomhui1009@yahoo.com, 8613760232170
 *
 * Create Date: Sun Mar 11 01:03 2018
 *
 * Brief:
 *   wrapper redis.
 *
 *******************************************************/

#ifndef __HREDIS_H__
#define __HREDIS_H__

#include <huibase.h>
#include <hiredis.h>

#include "nosql_comm.h"

namespace HUIBASE {

    namespace NOSQL {

#define SINGLE_SET_BEGIN HNOTOK_RETURN(connect())

#define SINGLE_SET_END redisReply* r = (redisReply*)redisCommand (m_context, strComm.c_str()); \
                                                                        \
        HASSERT_THROW_MSG(r != nullptr, "redisreply is nullptr", DEP_ERROR); \
                                                                        \
        HRET ret = HERR_NO(OK);                                         \
        do {                                                            \
            if (r->type != REDIS_REPLY_STRING) {                        \
                ret = HERR_NO(DEP_ERROR);                               \
                break;                                                  \
            }                                                           \
        } while(0);                                                     \
                                                                        \
        freeReplyObject(r);                                             \
                                                                        \
        return ret

#define SINGLE_GET_BEGIN HNOTOK_RETURN(connect())

#define SINGLE_GET_END redisReply* r = (redisReply*)redisCommand (m_context, strComm.c_str()); \
        \
        HASSERT_THROW_MSG(r != nullptr, "redisreply is nullptr", DEP_ERROR); \
        \
        HRET ret = HERR_NO(OK); \
        do { \
            if (r->type != REDIS_REPLY_STRING) { \
                ret = HERR_NO(DEP_ERROR); \
                break; \
            } \
        } while(0); \
        \
        strVal = r->str; \
        \
        freeReplyObject(r); \
        \
        return ret;

#define SINGLE_RET_BEGIN HNOTOK_RETURN(connect())

#define SINGLE_RET_END HRET ret = HERR_NO(OK); \
        \
        redisReply* r = (redisReply*)redisCommand(m_context, strComm.c_str()); \
        do { \
            \
            HASSERT_THROW_MSG(r != nullptr, "redis is error", DEP_ERROR); \
            \
            if (r->type != REDIS_REPLY_STATUS) { \
                ret = HERR_NO(DEP_ERROR); \
                break; \
            } \
            \
            if (strcasecmp(r->str, "0") == 0) { \
                ret = HERR_NO(NO_DONE); \
                break; \
            } \
            \
            if (strcasecmp(r->str, "1") != 0) { \
                ret = HERR_NO(DEP_ERROR); \
            } \
            \
        } while (0); \
        \
        freeReplyObject(r); \
        \
        return ret;

#define SINGLE_BOOL_BEGIN \
    HIF_NOTOK(connect()) { \
        return HFALSE; \
    }


#define SINGLE_BOOL_END redisReply* r = (redisReply*)redisCommand(m_context, strComm.c_str()); \
        \
        HASSERT_THROW_MSG(r != nullptr, "redisreply is nullptr", DEP_ERROR); \
        \
        HASSERT_THROW_MSG(r->type == REDIS_REPLY_INTEGER, "redisreply is not integer", DEP_ERROR); \
        \
        auto cb = r->integer; \
        \
        freeReplyObject(r); \
        \
        HRET_BOOL(cb == 1);


        class CRedisBase {
        public:
            static const HSTR NIL;
        };

        class CRedis : public CRedisBase {
        public:
            CRedis (HCSTRR strIp, HUINT nPort);

            CRedis (const NoSqlConnectionInfo& info);

            virtual ~CRedis ();

            void Release ();

        public:
            // signle
            HRET SingleSet (HCSTRR key, HCSTRR val) const;

            HRET SingleGet (HCSTRR key, HSTRR val) const;

            HRET SingleExpire (HCSTRR key, HINT sec) const;

            HBOOL SingleExists (HCSTRR key) const;

            HRET SingleHDel (HCSTRR strKey, HCSTRR strFiled) const;

            HBOOL SingleHExists (HCSTRR strKey, HCSTRR strField) const;

            HRET SingleHGet (HCSTRR strKey, HCSTRR strField, HSTRR strVal) const;

            HRET SingleHSet (HCSTRR strKey, HCSTRR strField, HCSTRR strVal) const;

        private:
            HRET connect () const throw (HCException);


        private:
            mutable redisContext* m_context = nullptr;

            NoSqlConnectionInfo m_info;
        };

    }

}



#endif //__HREDIS_H__

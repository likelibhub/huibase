/*******************************************************
 *
 * FileName: hredis.cpp
 *
 * Author: Tom Hui, tomhui1009@yahoo.com, 8613760232170
 *
 * Create Date: Sun Mar 11 01:03 2018
 *
 * Brief:
 *   Implementation for hredis.
 *
 *******************************************************/

#include <hstr.h>
#include "hredis.h"

namespace HUIBASE {

    namespace NOSQL {

        const HSTR CRedisBase::NIL = "**NIL**";


        CRedis::CRedis(HCSTRR strIp, HUINT nPort){
            m_info.strIp = strIp;
            m_info.nPort = nPort;
        }


        CRedis::CRedis(const NoSqlConnectionInfo& info)
            :m_info(info) { }


        CRedis::~CRedis () {

            Release ();

        }

        void CRedis::Release() {

            if (m_context != nullptr) {

                redisFree(m_context);
                m_context = nullptr;

            }

        }

        HRET CRedis::SingleSet (HCSTRR key, HCSTRR val) const {

            HNOTOK_RETURN(connect());

            HSTR strComm = HCStr::Format("set %s %s", key.c_str(), val.c_str());

            redisReply* r = (redisReply*)redisCommand(m_context, strComm.c_str());

            HASSERT_RETURN(r != nullptr, DEP_ERROR);

            HASSERT_RETURN(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str, "OK") == 0, DEP_ERROR);

            freeReplyObject(r);

            HRETURN_OK;
        }


        HRET CRedis::SingleGet(HCSTRR key, HSTRR val) const {

            HNOTOK_RETURN(connect());

            HSTR strComm = HCStr::Format("get %s", key.c_str());

            redisReply* r = (redisReply*)redisCommand (m_context, strComm.c_str());

            HASSERT_THROW_MSG(r != nullptr, "redisreply is nullptr", DEP_ERROR);

            HASSERT_THROW_MSG(r->type == REDIS_REPLY_STRING,"redis reply is not string",  DEP_ERROR);

            val = r->str;

            freeReplyObject(r);

            HRETURN_OK;

        }


        HRET CRedis::SingleExpire(HCSTRR key, HINT sec) const {

            HASSERT_RETURN(key.size(), INVL_PARA);

            SINGLE_RET_BEGIN;

            HSTR strComm = HCStr::Format("expire %s %d", key.c_str(), sec);

            SINGLE_RET_END;
        }


        HBOOL CRedis::SingleExists(HCSTRR key) const {

            SINGLE_BOOL_BEGIN;

            HSTR strComm = HCStr::Format("exists %s", key.c_str());

            SINGLE_BOOL_END;
        }


        HRET CRedis::SingleHDel(HCSTRR strKey, HCSTRR strField) const {

            SINGLE_RET_BEGIN;

            HSTR strComm = HCStr::Format("HDEL %s %s", strKey.c_str(), strField.c_str());

            SINGLE_RET_END;

        }


        HBOOL CRedis::SingleHExists(HCSTRR strKey, HCSTRR strField) const {

            SINGLE_BOOL_BEGIN;

            HSTR strComm = HCStr::Format("HEXISTS %s %s", strKey.c_str(), strField.c_str());

            SINGLE_BOOL_END;

        }


        HRET CRedis::SingleHGet (HCSTRR strKey, HCSTRR strField, HSTRR strVal) const {

            SINGLE_GET_BEGIN;

            HSTR strComm = HCStr::Format("HGET %s %s", strKey.c_str(), strField.c_str());

            SINGLE_GET_END;

        }


        HRET CRedis::SingleHSet (HCSTRR strKey, HCSTRR strField, HCSTRR strVal) const {

            SINGLE_RET_BEGIN;

            HSTR strComm = HCStr::Format("HSET %s %s %s", strKey.c_str(), strField.c_str(), strVal.c_str());

            SINGLE_SET_END;

        }





        HRET CRedis::connect() const throw (HCException) {

            if (m_context == nullptr) {

                m_context = redisConnect(m_info.strIp.c_str(), m_info.nPort);

                HASSERT_THROW_MSG(m_context != nullptr, "redisConnect return null handle", ILL_PT);

                if (m_context->err) {

                    redisFree(m_context);

                    m_context = nullptr;

                    HRETURN(DEP_ERROR);

                }

            }

            HRETURN_OK;
        }


    }

}

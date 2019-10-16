

#include "hmemcached.h"

namespace HUIBASE {

    namespace NOSQL {

        CMemcached::CMemcached (const NoSqlConnectionInfo& info) {

            memcached_return rc;
            memcached_server_st* server = nullptr;

            m_st = memcached_create(nullptr);

            server = memcached_server_list_append(server, info.strIp.c_str(), info.nPort, &rc);

            rc = memcached_server_push(m_st, server);

            HASSERT_THROW_MSG(rc == MEMCACHED_SUCCESS, "memcach object structetion failed", MEM_ERR);

            memcached_server_list_free(server);

        }


        CMemcached::~CMemcached() {

            if (m_st != nullptr) {

                memcached_free(m_st);

            }

        }


        HRET CMemcached::Set(HCSTRR strKey, HCSTRR strValue, HTIME extt) throw (HCException) {

            HASSERT_THROW_MSG((not strKey.empty()) && (not strValue.empty()), "CMemcached Set Failed. Error input", INVL_PARA);

            HASSERT_THROW_MSG(memcached_set(m_st, strKey.c_str(), strKey.length(), strValue.c_str(), strValue.length(), extt, 0) == MEMCACHED_SUCCESS, "memcached set failed", MEM_ERR);

            HRETURN_OK;

        }


        HRET CMemcached::Get(HCSTRR strKey, HSTRR strValue) throw (HCException) {

            HASSERT_THROW_MSG(not strKey.empty(), "CMemcached Get Failed. Error Input", INVL_PARA);

            strValue.clear();

            size_t res_len = 0;

            memcached_return rc;
            uint32_t flags = 0;

            char * ret = memcached_get(m_st, strKey.c_str(), strKey.length(), &res_len, &flags, &rc);

            if (rc == MEMCACHED_NOTFOUND || rc == MEMCACHED_NOTSTORED) {

                strValue.clear();
                HRETURN_OK;

            }

            HASSERT_THROW_MSG(rc == MEMCACHED_SUCCESS, "CMemcached get failed", MEM_ERR);

            HCHAR buf[MEM_BUF_LEN] = {0};

            memcpy(buf, ret, res_len);
            free(ret);

            strValue = buf;

            HRETURN_OK;

        }

        HRET CMemcached::Delete(HCSTRR strKey) throw (HCException) {

            HASSERT_THROW_MSG(not strKey.empty(), "CMemcached delete failed", INVL_PARA);

            HASSERT_THROW_MSG(memcached_delete(m_st, strKey.c_str(), strKey.length(), 0) == MEMCACHED_SUCCESS, "memcached delete failed", MEM_ERR);

            HRETURN_OK;

        }


        HBOOL CMemcached::Exists(HCSTRR strKey) throw (HCException) {

            HASSERT_THROW_MSG(not strKey.empty(), "CMemcached exists failed", INVL_PARA);

            HRET_BOOL(memcached_exist(m_st, strKey.c_str(), strKey.length()) == MEMCACHED_SUCCESS);

        }


        HUINT CMemcached::Increment(HCSTRR strKey, HUINT offset) throw (HCException) {

            HASSERT_THROW_MSG(not strKey.empty(), "CMemcached exists failed", INVL_PARA);

            HASSERT_THROW_MSG(HIS_TRUE(Exists(strKey)), "CMemcached Increment key is not exists", INVL_PARA);

            uint64_t res = 0;

            HASSERT_THROW_MSG(memcached_increment(m_st, strKey.c_str(), strKey.length(), offset, &res) == MEMCACHED_SUCCESS, "CMemcached increment failed", MEM_ERR);

            return (HUINT) res;
        }


        HUINT CMemcached::Decrement(HCSTRR strKey, HUINT offset) throw (HCException) {

            HASSERT_THROW_MSG(not strKey.empty(), "CMemcached exists failed", INVL_PARA);

            HASSERT_THROW_MSG(HIS_TRUE(Exists(strKey)), "CMemcached Decrement key is not exists", INVL_PARA);

            uint64_t res = 0;

            HASSERT_THROW_MSG(memcached_decrement(m_st, strKey.c_str(), strKey.length(), offset, &res) == MEMCACHED_SUCCESS, "CMemcached decrement failed", MEM_ERR);

            return (HUINT) res;
        }


        HRET CMemcached::Add(HCSTRR strKey, HCSTRR strVal, HTIME nexpir) throw (HCException) {

            HASSERT_THROW_MSG(not strKey.empty(), "CMemcached add failed", INVL_PARA);

            HASSERT_THROW_MSG(memcached_add(m_st, strKey.c_str(), strKey.length(), strVal.c_str(), strVal.length(), nexpir, 0) == MEMCACHED_SUCCESS, "CMemcached add failed", MEM_ERR);

            HRETURN_OK;

        }


        HBOOL CMemcached::NotDouble(HCSTRR strKey, HCSTRR strVal, HTIME nexpir) throw (HCException) {

            HASSERT_THROW_MSG(not strKey.empty(), "CMemcached add failed", INVL_PARA);

            HRET_BOOL(memcached_add(m_st, strKey.c_str(), strKey.length(), strVal.c_str(), strVal.length(), nexpir, 0) == MEMCACHED_SUCCESS);

        }


    }


}

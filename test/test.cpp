

#include <hmemcached.h>
#include <huibase.h>

using namespace HUIBASE;
using namespace HUIBASE::NOSQL;

int main() {

    NoSqlConnectionInfo info;
    info.strIp = "127.0.0.1";
    info.nPort = 9101;

    CMemcached mem(info);

    HSTR val;
    mem.Get("test", val);

    cout << val << endl;


	return 0;
}


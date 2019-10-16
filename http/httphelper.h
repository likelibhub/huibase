



#ifndef __HTTPHELPER_H__
#define __HTTPHELPER_H__


#include <huibase.h>
#include <curl/curl.h>


namespace HUIBASE {

namespace HTTP {

	enum enum_http_opt {
		eho_userpw = (HINT)CURLOPT_USERPWD,

		eho_end,
	};

	struct http_opt{
		enum_http_opt opt;
		HSTR optValue;
	};

	using HTTP_OPTS = std::vector<http_opt>;

	HRET HttpGet (HCSTRR strUrl, HSTRR strRes);

    HRET HttpGetWithHeader (HCSTRR strUrl, const HTTP_OPTS& opts, HSTRR strRes);

	HRET HttpPost (HCSTRR strUrl, HCSTRR strData, HSTRR strRes);

	HRET HttpPostWithHeader (HCSTRR strUrl, HCSTRR strData, const HTTP_OPTS& opts, HSTRR strRes);

}

}



#endif //__HTTPHELPER_H__



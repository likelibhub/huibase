


#include "httphelper.h"



namespace HUIBASE {

namespace HTTP {

	static HSIZE OnWriteData(void* buffer, HSIZE size, HSIZE nmemb, void* lpVoid) ;

	HRET HttpGet (HCSTRR strUrl, HSTRR strRes) {
		
		curl_global_init(CURL_GLOBAL_ALL);
    	CURL * url = curl_easy_init();
	    if( NULL == url ){
    	    return -1;
    	}

	    CURLcode res;  

    	curl_easy_setopt(url, CURLOPT_URL, strUrl.c_str());  
    	curl_easy_setopt(url, CURLOPT_READFUNCTION, NULL);     
    	curl_easy_setopt(url, CURLOPT_WRITEFUNCTION, OnWriteData);
    	//curl_easy_setopt(url, CURLOPT_HEADERDATA, &strRes);
	    curl_easy_setopt(url, CURLOPT_WRITEDATA, (void *)&strRes);  
    	curl_easy_setopt(url, CURLOPT_NOSIGNAL, 1);  
	    curl_easy_setopt(url, CURLOPT_SSL_VERIFYPEER, false);
    	//curl_easy_setopt(url, CURLOPT_SSL_VERIFYPEER, 0L);
    	curl_easy_setopt(url, CURLOPT_CONNECTTIMEOUT, 3);  
    	curl_easy_setopt(url, CURLOPT_TIMEOUT, 10);
    	res = curl_easy_perform(url);  
    	curl_easy_cleanup(url);  
	    curl_global_cleanup();


		return (int) res == 0 ? HERR_NO(OK) : HERR_NO(HTTP_FAILED);
	}


    HRET HttpGetWithHeader (HCSTRR strUrl, const HTTP_OPTS& opts, HSTRR strRes) {

        curl_global_init(CURL_GLOBAL_ALL);
        CURL *url = curl_easy_init();

        if (nullptr == url) {
            HRETURN(DEP_ERROR);
        }

        CURLcode res;

        curl_easy_setopt(url, CURLOPT_URL, strUrl.c_str());
        curl_easy_setopt(url, CURLOPT_READFUNCTION, NULL);
	    curl_easy_setopt(url, CURLOPT_WRITEFUNCTION, OnWriteData);
	    curl_easy_setopt(url, CURLOPT_WRITEDATA, (void *)&strRes);
	    curl_easy_setopt(url, CURLOPT_NOSIGNAL, 1);
	    curl_easy_setopt(url, CURLOPT_SSL_VERIFYPEER, false);
	    curl_easy_setopt(url, CURLOPT_CONNECTTIMEOUT, 3);
	    curl_easy_setopt(url, CURLOPT_TIMEOUT, 10);

        for (HTTP_OPTS::size_type i = 0; i < opts.size(); ++i) {
			const http_opt& ho = opts.at(i);
			curl_easy_setopt(url, (CURLoption)ho.opt, ho.optValue.c_str());
		}

        res = curl_easy_perform(url);
    	curl_easy_cleanup(url);
	    curl_global_cleanup();

        return (int) res == 0 ? HERR_NO(OK) : HERR_NO(HTTP_FAILED);

    }


	HRET HttpPost (HCSTRR strUrl, HCSTRR strData, HSTRR strRes) {

		curl_global_init(CURL_GLOBAL_ALL);
    	CURL * url = curl_easy_init();
	    if( NULL == url ){
	        return -1;
	    }

	    CURLcode res;  

	    curl_easy_setopt(url, CURLOPT_URL, strUrl.c_str()); 
	    curl_easy_setopt(url, CURLOPT_POSTFIELDS, strData.c_str());
	    curl_easy_setopt(url, CURLOPT_READFUNCTION, NULL);     
	    curl_easy_setopt(url, CURLOPT_WRITEFUNCTION, OnWriteData);
	    //curl_easy_setopt(url, CURLOPT_HEADERDATA, &strRes);
	    curl_easy_setopt(url, CURLOPT_WRITEDATA, (void *)&strRes);  
	    curl_easy_setopt(url, CURLOPT_NOSIGNAL, 1);  
	    curl_easy_setopt(url, CURLOPT_SSL_VERIFYPEER, false);
	    //curl_easy_setopt(url, CURLOPT_SSL_VERIFYPEER, 0L);
	    curl_easy_setopt(url, CURLOPT_CONNECTTIMEOUT, 3);  
	    curl_easy_setopt(url, CURLOPT_TIMEOUT, 10);
	    res = curl_easy_perform(url);  
	    curl_easy_cleanup(url);  
	    curl_global_cleanup();

		return (int) res == 0 ? HERR_NO(OK) : HERR_NO(HTTP_FAILED);
	}

	HSIZE OnWriteData(void* buffer, HSIZE size, HSIZE nmemb, void* lpVoid)  {  
    	HSTR* str = dynamic_cast<HSTR*>((HSTR *)lpVoid);  
    	if( NULL == str || NULL == buffer )  
    	{  
        	return -1;  
    	}  
  
    	HCHAR* pData = (HCHAR*)buffer;  
    	str->append(pData, size * nmemb);  
    	return nmemb;  
	}  


	HRET HttpPostWithHeader (HCSTRR strUrl, HCSTRR strData, const HTTP_OPTS& opts, HSTRR strRes) {

		curl_global_init(CURL_GLOBAL_ALL);
    	CURL * url = curl_easy_init();
	    if( NULL == url ){
	        return -1;
	    }

	    CURLcode res;  

	    curl_easy_setopt(url, CURLOPT_URL, strUrl.c_str()); 
	    curl_easy_setopt(url, CURLOPT_POSTFIELDS, strData.c_str());
	    curl_easy_setopt(url, CURLOPT_READFUNCTION, NULL);     
	    curl_easy_setopt(url, CURLOPT_WRITEFUNCTION, OnWriteData);
	    //curl_easy_setopt(url, CURLOPT_HEADERDATA, &strRes);
	    curl_easy_setopt(url, CURLOPT_WRITEDATA, (void *)&strRes);  
	    curl_easy_setopt(url, CURLOPT_NOSIGNAL, 1);  
	    curl_easy_setopt(url, CURLOPT_SSL_VERIFYPEER, false);
	    //curl_easy_setopt(url, CURLOPT_SSL_VERIFYPEER, 0L);
	    curl_easy_setopt(url, CURLOPT_CONNECTTIMEOUT, 3);  
	    curl_easy_setopt(url, CURLOPT_TIMEOUT, 10);

		for (HTTP_OPTS::size_type i = 0; i < opts.size(); ++i) {
			const http_opt& ho = opts.at(i);
			curl_easy_setopt(url, (CURLoption)ho.opt, ho.optValue.c_str());
		}
	    
	    res = curl_easy_perform(url);  
	    curl_easy_cleanup(url);  
	    curl_global_cleanup();

		return (int) res == 0 ? HERR_NO(OK) : HERR_NO(HTTP_FAILED);
		
	}

}

}



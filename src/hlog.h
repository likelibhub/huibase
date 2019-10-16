/**************************=cpphd=******************************************
 * 
 * @ File Name: hlog.h
 * 
 * @ Create Author: Tom Hui
 * 
 * @ Create Date: Sun Jan 08 21:46 2017
 * 
 * @ Brief:
 * 	declare hbase's log class.
 * 
 ****************************************************************************/



#ifndef __HLOG_H__
#define __HLOG_H__

#include "huibase.h"
#include "hholder.hpp"


namespace HUIBASE {

#define LOG_MAX_LEN ( HLEN8096_C )

    class HCLog {
    public:
	
	HCLog ();
	
	HCLog (HCSTRR strFileName);

	virtual ~HCLog ();

	void SetFileLogName (HCSTRR strFileName) {
	    m_strFileLogName = strFileName;
	}

	HCSTRR GetFileLogName () const { return m_strFileLogName; }

    public:

	HRET Normal (HCPSZ ff, HINT ll, HCPSZ fmt, ...);

	HRET Warnning (HCPSZ ff, HINT ll, HCPSZ fmt, ...);

	HRET Error (HCPSZ ff, HINT ll, HCPSZ fmt, ...);

	virtual HRET WriteLog (HCPSZ ff, HINT ll, HCPSZ stype, HCPSZ slog);
   		
    protected:

	virtual HSTR newLogName () ;

	virtual HRET shiftLog ();

    private:	

	virtual HRET open ();

	virtual HRET close ();

    private:

	HSTR m_strFileLogName;

	static const HUINT m_sShiftSize = 1024 * 1024 * 100;

	HUINT m_len = 0;

	HUINT m_todayIndex = 0;

	HSYS_T m_fd;

    private:
	static time_t ms_logTime;
	static HBOOL more_day ();

    };

    HRET InitLog (HCSTRR strFilename);

    void log_down (HCPSZ ff, HINT ll,HCPSZ stype,HCPSZ fmt, ...);

//#define _JUST_TEST_
#ifndef _JUST_TEST_    
#define LOG_NORMAL(fmt,args...) log_down(__FILE__, __LINE__,"NORMAL", fmt, ##args)

#define LOG_WARNNING(fmt,args...) log_down(__FILE__, __LINE__,"WARNNING", fmt, ##args)

#define LOG_ERROR(fmt,args...) log_down(__FILE__,__LINE__,"ERROR",fmt,##args)

#define LOG_NS(ss) log_down(__FILE__,__LINE__,"NORMAL",ss)
#define LOG_WS(ss) log_down(__FILE__,__LINE__,"WARNNING",ss)
#define LOG_ES(ss) log_down(__FILE__,__LINE__,"ERROR",ss)

#define HFUN_BEGIN LOG_NORMAL("[%s]: begin...", __FUNCTION__)
#define HFUN_END LOG_NORMAL("[%s]: end...", __FUNCTION__)

#define HLOG_NORMAL(log,fmt,args...) (log).Normal(__FILE__,__LINE__,fmt,##args)
#define HLOG_WARNNING(log,fmt,args...) (log).Warnning(__FILE__,__LINE__,fmt,##args)
#define HLOG_ERROR(log,fmt,args...) (log).Error(__FILE__,__LINE__,fmt,##args)

#define HLOG_NS(log,ss) (log).Normal(__FILE__,__LINE__,ss)
#define HLOG_WS(log,ss) (log).Warnning(__FILE__,__LINE__,ss)
#define HLOG_ES(log,ss) (log).Error(__FILE__,__LINE__,ss)

#else 
#define HFUN_END 
#define HFUN_BEGIN
#define LOG_NORMAL
#define LOG_WARNNING
#define LOG_ERROR

#define LOG_NS
#define LOG_WS
#define LOG_ES


#endif 

    
}


#endif //__HLOG_H__
















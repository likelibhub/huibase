

#include "hlog.h"
#include "htime.h"


namespace HUIBASE {

    time_t HCLog::ms_logTime = time(NULL);

    HCLog::HCLog () {

	m_fd = HINVA_FD;

    }


    HCLog::HCLog (HCSTRR strFileName)
	: m_strFileLogName(strFileName){

	open();

    }

    HCLog::~HCLog() {

	close();

    }

#define __WRITE_LOG  \
    HCHAR buf[LOG_MAX_LEN] = {0};		 \
    memset(buf, 0, sizeof(HCHAR) * LOG_MAX_LEN); \
    va_list ap; \
    va_start(ap, fmt);	 \
    vsnprintf(buf, LOG_MAX_LEN, fmt, ap); \
    va_end(ap)

    HRET HCLog::Normal(HCPSZ ff, HINT ll, HCPSZ fmt, ...) {

	__WRITE_LOG;

        WriteLog(ff, ll,"NORMAL", buf);

	HRETURN_OK;

    }

    HRET HCLog::Warnning(HCPSZ ff, HINT ll, HCPSZ fmt, ...) {

	__WRITE_LOG;

	WriteLog(ff, ll, "WARNNING", buf);

	HRETURN_OK;
    }

    HRET HCLog::Error(HCPSZ ff, HINT ll, HCPSZ fmt, ...) {

	__WRITE_LOG;

	WriteLog(ff, ll, "ERROR", buf);

	HRETURN_OK;
    }


    HRET HCLog::WriteLog(HCPSZ ff, HINT ll, HCPSZ stype, HCPSZ slog) {

	HCHAR buf[LOG_MAX_LEN] = {0};

#ifdef WIN32
	snprintf(buf, LOG_MAX_LEN, "[%s][%d][%s]: %s.[%s:%d]\n", HCTime::GetTimeNow().c_str(), (int)getpid(),  stype, slog, ff, ll);
#else
	snprintf(buf, LOG_MAX_LEN, "[%s][%d][%lu][%s]: %s.[%s:%d]\n", HCTime::GetTimeNow().c_str(), (int)getpid(), (unsigned long)pthread_self(), stype, slog, ff, ll);
#endif

	m_len += strlen(buf);

	shiftLog();

	if (HINVA_FD == m_fd) {

	    open();

	}

	ssize_t wcb = write(m_fd,buf, strlen(buf));
	if (wcb < 0) {
		printf("write failed");
	}

	HRETURN_OK;

    }

    HSTR HCLog::newLogName() {

	HSTR ret;

	ret = m_strFileLogName + "_" + HCTime::GetTimeNow().substr(0, 10) + "_" + 
		HCStr::itos(m_todayIndex) + ".log";

	return ret;

    }


    HRET HCLog::open () {

	m_fd = ::open( newLogName().c_str(), O_CREAT | O_WRONLY | O_APPEND , 0664);
	if (HINVA_FD == m_fd) {

	    printf("fopen failed\n");
	    exit(-1);

	    HRETURN(SYS_FAILED);

	}

	HRETURN_OK;
	
    }

    HRET HCLog::close() {

	if (HINVA_FD == m_fd) {

	    HRETURN(UN_INIT);

	}

	::close(m_fd);

	m_fd = HINVA_FD;

	m_len = 0;

	HRETURN_OK;

    }

    HRET HCLog::shiftLog() {

	if (HIS_TRUE(more_day())) {

		m_todayIndex = 0;

	    close();

	}

	if (m_len > m_sShiftSize) {

		++ m_todayIndex;

		close();

	}

	HRETURN_OK;

    }


    HBOOL HCLog::more_day() {

	HTIME _tt = time(NULL);
	struct tm * p = localtime(&_tt);
	int ny = p->tm_year, nm = p->tm_mon, nd = p->tm_mday;

	p = localtime(&ms_logTime);
	int ly = p->tm_year, lm = p->tm_mon, ld = p->tm_mday;

	if (ny == ly && nm == lm && nd == ld) {
	    return HFALSE;
	}

	ms_logTime = _tt;

	return HTRUE;

    }

	static HCLog gs_log;
    static HCLog * gs_plog = nullptr;
    static HCPointerHolder<HCLog> gs_log_holder;

    HRET InitLog (HCSTRR strFilename) {

		gs_log.SetFileLogName(strFilename);

		gs_plog = &gs_log;

		HRETURN_OK;

    }


    void log_down (HCPSZ ff, HINT ll, HCPSZ stype, HCPSZ fmt, ...) {

	HCHAR buf[LOG_MAX_LEN] = {0};
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, LOG_MAX_LEN, fmt, ap);
	va_end(ap);

	gs_plog->WriteLog(ff, ll, stype, buf);

    }

}















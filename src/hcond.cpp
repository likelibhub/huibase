

#include "hcond.h"


namespace HUIBASE {

HCCondAttr::HCCondAttr() throw (HCException){

	auto cb = pthread_condattr_init(&m_attr);
	HASSERT_THROW(cb == 0, SYS_FAILED);

}


HCCondAttr::~HCCondAttr() {

	(void)pthread_condattr_destroy(&m_attr);

}

HCCond::HCCond () throw (HCException){

	auto cb = pthread_cond_init(m_id.GetIdP(), nullptr);
	HASSERT_THROW(cb == 0, SYS_FAILED);

}


HCCond::HCCond (const HCCondAttr& attr) throw (HCException) {

	auto cb = pthread_cond_init(m_id.GetIdP(), attr.GetAttrP());
	HASSERT_THROW(cb == 0, SYS_FAILED);
	
}

HCCond::~HCCond() {
	
	(void)pthread_cond_destroy(m_id.GetIdP());

}


HRET HCCond::Signal () throw (HCException) {

	auto cb = pthread_cond_signal(m_id.GetIdP());
	HASSERT_THROW(cb == 0, SYS_FAILED);

	HRETURN_OK;

}

HRET HCCond::Broatcast () throw (HCException) {
	auto cb = pthread_cond_broadcast(m_id.GetIdP());
	HASSERT_THROW(cb == 0, SYS_FAILED);

	HRETURN_OK;
}

HRET HCCond::Wait (HCMutex& mutex) throw (HCException) {

	auto cb = pthread_cond_wait(m_id.GetIdP(), mutex.m_id.GetIdP());
	HASSERT_THROW(cb == 0, SYS_FAILED);

	HRETURN_OK;

}

}




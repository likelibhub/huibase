

#ifndef _H_TASK_H_
#define _H_TASK_H_

#include "huibase.h"

namespace HUIBASE{

class HCTask{
public:
	HCTask();
	virtual ~ HCTask();

public:
	virtual HRET ParseInput(HCPSR ps) throw (HCException);

	virtual HRET DoWork() throw (HCException);

	virtual HRET DoTurn() throw (HCException);

protected:
	virtual HRET CommitInput() throw (HCException) {HRETURN_OK;}

	virtual HRET Commit() throw (HCException) = 0 ;

	virtual HRET CommitReturn() throw (HCException) {HRETURN_OK;}

protected:
	HPS m_inps;
	
};


}
#endif 


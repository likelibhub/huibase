


#include "htask.h"

namespace HUIBASE{


HCTask::HCTask(){


}


HCTask::~HCTask(){


}

HRET HCTask::ParseInput (HCPSR ps) throw (HCException) {

	m_inps = ps;

	return CommitInput();

}


HRET HCTask::DoWork() throw (HCException) {

    return	Commit();

}


HRET HCTask::DoTurn()  throw (HCException){

    

    return CommitReturn();
    
}



}


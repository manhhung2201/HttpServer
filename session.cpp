#include "session.h"

Session::Session(TcpSocket* slave)
{
    this->slave = slave;
    this->quitSession = false;

}
Session::~Session()
{
    delete slave;
}

bool Session::isQuit()
{
    return quitSession;
}



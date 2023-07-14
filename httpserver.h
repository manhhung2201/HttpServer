#ifndef HTTPSERVER_H_
#define HTTPSERVER_H_

#include "tcpserver.h"
#include "httpsession.h"


class HTTPServer: public TCPServer
{
public:
    HTTPServer(unsigned short port=80);
    ~HTTPServer();
protected:
    void startNewSession(TcpSocket* slave);
    void configServer();
    void cleanServer();
    void initCmd();
private:
    int readCmd(TcpSocket* slave, char* buffer, int buflen);
    unsigned short parseCmd(char *sCmdBuf, int len, char * cmd_argv[], int& cmd_argc);
protected:
};

#endif // HTTPSERVER_H_


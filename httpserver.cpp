
#include <iostream>
#include <cstring>
#include <sstream>
#include "httpserver.h"
#include "random.h"

const char HTTP_DELIMITER[]= " ";
const char EOL[] = "\r\n";
const char BLANK_LINE[] = "\r\n";
const char HTTP_WELCOME[]= "-------------------------Hello, HTTP Server is already!----------------------\r\n";

HTTPServer::HTTPServer(unsigned short port):TCPServer(port)
{
    initCmd();

}


HTTPServer::~HTTPServer()
{
    if(isRunning())
    {
        stop();
        cout<< "HTTP Server stopped!\n";
    }
}
void HTTPServer::cleanServer()
{

}
void HTTPServer::configServer()
{

}
void HTTPServer::initCmd()
{
    addCmd(GET, FUNC_CAST(&HTTPSession::doGET));
    addCmd(HEAD, FUNC_CAST(&HTTPSession::doHEAD));



}

// viet ham doc request tu client
int HTTPServer::readCmd(TcpSocket* slave, char* buffer, int buflen)
{

    try
    {
        int byteRead = slave->recvLine(buffer,buflen);
        if(byteRead >= 2) // loai bo CRLF (\r\n) o cuoi xau chua lenh
        {
            buffer[byteRead-2] = 0;
            return byteRead - 2;
        }
        else
        {
            buffer[0] = 0;
            return 0;
        }
    }
    catch(SocketException&e )
    {
        cerr << e.what() << endl;
        return -1;
    }
}


// viet ham phan tich cu phap
unsigned short HTTPServer::parseCmd(char *sCmdBuf, int len, char * cmd_argv[], int& cmd_argc)
{
    char * arg;
    cmd_argc = 0; // so tham so = 0

    if(len<=0)
        return SERVER_CMD_UNKNOWN;  // do dai cua xau chua lenh > 0

    arg = strtok (sCmdBuf,HTTP_DELIMITER); // tách
    while (arg != NULL)
    {
        cmd_argv[cmd_argc++] = arg;
        arg = strtok (NULL, HTTP_DELIMITER);
    }
    int i;
    if(cmd_argc>0)
    {
        for(i = 0; i<this->numCmd; i++)
        {
            if(stricmp(cmd_argv[0],cmdNameList[i].c_str())==0)
                return i ;
        }
    }
    return SERVER_CMD_UNKNOWN;
}

void HTTPServer::startNewSession(TcpSocket* slave)
{

    HTTPSession* session = new HTTPSession(slave);
    char cmdBuffer[SERVER_CMD_BUF_LEN];
    int cmdLen;
    char* cmdArgv[SERVER_CMD_ARG_NUM];
    int cmdArgc;
    unsigned short cmdId;
    ostringstream log;
    try
    {

        slave->send(HTTP_WELCOME);
        while(!session->isQuit())
        {
            // Nhan lenh
            cmdBuffer[0] = 0;
            cmdLen = readCmd(slave, cmdBuffer, SERVER_CMD_BUF_LEN);

            if(cmdLen <= 0)
                break;
            // Phan tich lenh
            cmdId = parseCmd(cmdBuffer, cmdLen, cmdArgv, cmdArgc );
            // Thuc hien lenh
            doCmd(session,cmdId,cmdArgv,cmdArgc);

        }
        // session finish
        delete session;


    }
    catch(SocketException&e)
    {
        cerr << e.what() << endl;
        delete session;
    }
}


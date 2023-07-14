#include <iostream>
#include "servercli.h"

ServerCLI::ServerCLI():CmdLineInterface("server>")
{
    http = new HTTPServer();

    initCmd();

    if(http->start()){
        cout <<  "----------------Http Server started------------------------------" << endl;

        cout << "(Nhap help de duoc tro giup)" << endl;

        }
    else{
        cout << "----------------Http Server failed to start-----------------------" <<endl;}

}
ServerCLI::~ServerCLI()
{
    delete http;
}



void ServerCLI::initCmd()
{
    addCmd("start",CLI_CAST(&ServerCLI::doStart));
    addCmd("stop",CLI_CAST(&ServerCLI::doStop));
    addCmd("restart",CLI_CAST(&ServerCLI::doRestart));
    addCmd("status",CLI_CAST(&ServerCLI::doStatus));
    addCmd("help", CLI_CAST(&ServerCLI::doHelp));
}

void ServerCLI::doStart(char * cmd_argv[], int cmd_argc)
{
    if(http->isRunning())
        cout << "----------------Http server is running!-------------------------" << endl;
    else if(http->start())
        cout << "----------------Http Server started------------------------------" << endl;
    else
        cout << "----------------Http Server failed to start---------------------" <<endl;
}

void ServerCLI::doStop(char * cmd_argv[], int cmd_argc)
{
    http->stop();
    cout <<     "----------------Http Server stopped------------------------------" << endl;
}



void ServerCLI::doRestart(char * cmd_argv[], int cmd_argc)
{

    if(http->restart())
        cout << "----------------Http Server restarted----------------------------" << endl;
    else
        cout << "----------------Http Server failed to restart--------------------" <<endl;

}

void ServerCLI::doStatus(char * cmd_argv[], int cmd_argc)
{

    if(http->isRunning())
        cout << "----------------Http Server is running---------------------------"<<endl;
    else
        cout << "----------------Http Server is not running-----------------------"<<endl;

}

void ServerCLI::doHelp(char * cmd_argv[], int cmd_argc)
{
    cout << "Cac lenh cua chuong trinh:" << endl;
    cout<<  "+-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*+"<< endl;
    cout<<  "| Lenh   | Ghi chu                 |"<< endl;
    cout<<  "+--------+-------------------------+"<< endl;
    cout << "| start  | Bat Http server         |" << endl;
    cout << "| stop   | Tat Http server         |" << endl;
    cout << "| status | Trang thai Tttp server  |" << endl;
    cout << "| help   | Tro giup                |" << endl;
    cout << "| quit   | Thoat                   |" << endl;
    cout<<  "+----------------------------------+"<< endl;
}

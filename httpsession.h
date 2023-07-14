#ifndef HTTPSESSION_H_INCLUDED
#define HTTPSESSION_H_INCLUDED
#include <vector>
#include "tcpserversocket.h"
#include "session.h"

// cac lenh trong ban tin SMTP request
#define GET  "GET"
#define HEAD  "HEAD"



#ifndef QUIT
    #define QUIT  "QUIT"
#endif // QUIT



class HTTPSession : public Session // HTTPSession là một lớp dẫn xuất từ lớp Session. Lớp này đại diện cho một phiên HTTP giữa máy chủ và client
{

    string response;

public:
    HTTPSession(TcpSocket* slave);//Đây là hàm khởi tạo của lớp HTTPSession, nhận một con trỏ đến TcpSocket (slave) để thiết lập kết nối giữa máy chủ và client.
    ~HTTPSession();//Đây là hàm hủy của lớp HTTPSession, được gọi khi một đối tượng HTTPSession bị hủy. Nó được sử dụng để giải phóng bất kỳ tài nguyên nào mà đối tượng có thể đang giữ.
    const string& getResponse() const {return response;}
    void doUnknown(char* cmd_argv[], int cmd_argc);
    void reset();
    void doGET(char* cmd_argv[], int cmd_argc);
    void doHEAD(char* cmd_argv[], int cmd_argc);


};



#endif // HTTPSESSION_H_INCLUDED


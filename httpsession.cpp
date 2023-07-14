#include <cstring>
#include <iostream>
#include "httpsession.h"
#include <string>
#include <ctime>
#include <fstream>

HTTPSession::HTTPSession(TcpSocket* slave): Session(slave)
{
    this->quitSession = false;
}

HTTPSession::~HTTPSession()
{
}

void HTTPSession::doGET(char* cmd_argv[], int cmd_argc)
{

    if (cmd_argc == 3 && strncmp(cmd_argv[1], "http/2", 9) == 0 && strncmp(cmd_argv[2], "localhost", 9) == 0)
    {
        std::string filename = cmd_argv[2] + 9;
        std::string filepath = "D:\\HttpServer\\html\\" + filename;


        std::ifstream ifs(filepath, std::ios::binary);// mở tệp tin yêu cầu
        if (!ifs)
        {
            response = "----------------HTTP/2 404 Not Found------------------------------\r\n\r\n";
            slave->send(response);
            return;
        }

        // Read the file into a vector of char
        std::vector<char> buffer((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

        // Set the content type based on the file extension
        std::string extension = filename.substr(filename.find_last_of(".") + 1);
        std::string content_type = (extension == "html") ? "text/html" : "text/plain";

        // Construct the response header
        response  = "+----------------GET-----------------+\r\n";
        response += "|           HTTP/2 200 OK            |\r\n";
        response += "+------------------------------------+\r\n";
        response += "| Server         | HttpServer        |\r\n";
        response += "| Content-Type   | " + content_type + "        |\r\n";
        response += "| Extension      | " + extension + "               |\r\n";
        response += "| Content-Length | " + std::to_string(buffer.size()) + "               |\r\n";
        response += "| Connection     | Close             |\r\n";
        response += "+------------------------------------+\r\n";

        response += "-------------Thong tin file-----------\r\n\r\n";

        // Send the header and the binary data of the file
        slave->send(response);
        slave->send(&buffer[0], buffer.size());
    }
    else
    {
        response = "----------------HTTP/2 404 Not Found------------------------------\r\n\r\n";
        slave->send(response);
    }
}



void HTTPSession::doHEAD(char* cmd_argv[], int cmd_argc)
{

    if (cmd_argc == 3 && strncmp(cmd_argv[1], "http/2", 9) == 0 && strncmp(cmd_argv[2], "localhost", 9) == 0)
    {
        std::string filename = cmd_argv[2] + 9;
        std::string filepath = "D:\\HttpServer\\html\\" + filename;

        std::ifstream file(filepath);
        std::string extension = filename.substr(filename.find_last_of(".") + 1);
         std::string content_type = (extension == "html") ? "text/html" : "text/plain";
        if (file.is_open())
        {
            // Calculate the content length
            file.seekg(0, std::ios::end); // trỏ đến cuối tệp tin
            int contentLength = file.tellg();// trả về độ dài tệp tin
            file.close();

            // Construct the response header
            response  = "+---------------HEAD-----------------+\r\n";
            response += "|          HTTP/2 200 OK             |\r\n";
            response += "+------------------------------------+\r\n";
            response += "| Server        |  HttpServer        |\r\n";
            response += "| Content-Type  | " + content_type +"          |\r\n";
            response += "| Extension     | " + extension + "               |\r\n";
            response += "| Content-Length| " + std::to_string(contentLength) + "               |\r\n";
            response += "| Connection    |Close               |\r\n";
            response += "+------------------------------------+\r\n";

        }
        else
        {
            response = "----------------HTTP/2 404 Not Found------------------------------\r\n\r\n";
        }
    }
    else
    {
            response = "----------------HTTP/2 404 Not Found------------------------------\r\n\r\n";
    }

    slave->send(response);
}

void HTTPSession::doUnknown(char* cmd_argv[], int cmd_argc)
{
    // Generate the HTML content for the error page
    std::string error_content = "Error - 505HTTP Version Not Supported";

    // Construct the response header
    response  = "+---------------UnKnonw----------------+\r\n";
    response += "|HTTP/2 505 HTTP Version Not Supported |\r\n";
    response += "+--------------------------------------+\r\n";
    response += "| Server         | HttpServer          |\r\n";
    response += "| Content-Type   | text/html           | \r\n";
    response += "| Content-Length | " + std::to_string(error_content.size()) + "                  |\r\n";
    response += "| Connection     | Close               |\r\n";
    response += "+--------------------------------------+\r\n\r\n";
    // Send the header and the HTML content of the error page
    std::string full_response = response + error_content;
    slave->send(full_response);
}


void HTTPSession::reset()
{
}

#include <iostream>
#include <fstream>
#include <vector>
#include <winsock2.h>
#include <string>
#include "guide.h" 
#include "package.h"
#include "business.h"

#pragma comment(lib, "ws2_32.lib")
using namespace std;

string handleRequest(const string& fullRequest) {
    if (fullRequest == "check") {
        return "Connection Established successfully.";
    }

    // Extract class name
    size_t pos = fullRequest.find("|");
    if (pos == string::npos) return "Invalid request format.\n";

    string className = fullRequest.substr(0, pos);
    string rest = fullRequest.substr(pos + 1);

    if (className == "guide") {
        return guide::processRequest(rest);
    }
     else if (className == "package") {
      return package::processRequest(rest);
     }
     else if (className == "business") {
        return business::processRequest(rest);
    }

    return "Unknown class type.\n";
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c;
    char buffer[2048];

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(12345);

    bind(s, (struct sockaddr*)&server, sizeof(server));
    listen(s, 3);

    cout << "Server listening on port 12345...\n";
    c = sizeof(struct sockaddr_in);

    while ((new_socket = accept(s, (struct sockaddr*)&client, &c)) != INVALID_SOCKET) {
        int recv_size = recv(new_socket, buffer, sizeof(buffer), 0);
        if (recv_size <= 0) {
            cerr << "Failed to receive data.\n";
            closesocket(new_socket);
            continue;
        }

        buffer[recv_size] = '\0';
        string response = handleRequest(buffer);
        send(new_socket, response.c_str(), response.size(), 0);
        closesocket(new_socket);
    }

    closesocket(s);
    WSACleanup();
    return 0;
}

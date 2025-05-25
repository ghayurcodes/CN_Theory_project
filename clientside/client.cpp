#define _WINSOCK_DEPRECATED_NO_WARNINGS  // Fix deprecated warning for inet_addr()
#include "menus.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> 
#pragma comment(lib, "ws2_32.lib")
#include <string>
using namespace std;

void sendRequest(string request) {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  

    if (connect(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        cout << "Connection failed. Error: " << WSAGetLastError() << endl;
        closesocket(s);
        WSACleanup();
        exit(0);
    }

    send(s, request.c_str(), request.size(), 0);

    char buffer[2048];
    int recv_size = recv(s, buffer, sizeof(buffer), 0);
    if (recv_size > 0) {
        buffer[recv_size] = '\0';//byte to string
        cout << "\nServer: \n" << buffer << endl;
    }
    else {
        cout << "Failed to receive data from server.\n";
    }

    closesocket(s);
    WSACleanup();
}



int main() {
    sendRequest("check");
    int choice;
    while (true) {
        cout << "\nWelcome to tour Management system.\n";
        cout << "Press 1 for Tour guide Menu.\n";
        cout << "Press 2 to select from our pre picked Packages for you.\n";
        cout << "Press 3 for Business Class.\n";
        cout << "Press 4 to get the total tours registered.\n";
        cout << "Press 5 to exit the Program.\n";

        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
        case 1:
            sendRequest(guide::showSubMenu());
            break;
        case 2:
            sendRequest(package::showSubMenu());
            break;
        case 3:
            sendRequest(business::showSubMenu());
            break;
        case 4:
            sendRequest("total");
            break;
        case 5:
            cout << "Exiting program...\n";
            break;
     
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }
}

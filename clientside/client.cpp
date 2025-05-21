#define _WINSOCK_DEPRECATED_NO_WARNINGS  // Fix deprecated warning for inet_addr()

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
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  // Deprecated but now allowed

    if (connect(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        cout << "Connection failed. Error: " << WSAGetLastError() << endl;
        closesocket(s);
        WSACleanup();
        return;
    }

    send(s, request.c_str(), request.size(), 0);

    char buffer[2048];
    int recv_size = recv(s, buffer, sizeof(buffer), 0);
    if (recv_size > 0) {
        buffer[recv_size] = '\0';
        cout << "\nServer: \n" << buffer << endl;
    }
    else {
        cout << "Failed to receive data from server.\n";
    }

    closesocket(s);
    WSACleanup();
}

int main() {
    int choice;
    while (true) {
        cout << "\n--- Tours Management System ---\n";
        cout << "1. Add Tour\n2. View Tours\n3. Update Tour\n4. Delete Tour\n5. Exit\nChoose: ";
        cin >> choice;

        if (choice == 1) {
            string name, date;
            float price;
            int people;
            cin.ignore();
            cout << "Name: "; getline(cin, name);
            cout << "Price: "; cin >> price;
            cout << "No. of People: "; cin >> people;
            cin.ignore();
            cout << "Booking Date: "; getline(cin, date);

            string request = "ADD|" + name + "|" + to_string(price) + "|" + to_string(people) + "|" + date;
            sendRequest(request);
        }
        else if (choice == 2) {
            sendRequest("VIEW|");
        }
        else if (choice == 3) {
            int index;
            string name, date;
            float price;
            int people;
            cout << "Enter index to update: "; cin >> index;
            cin.ignore();
            cout << "New Name: "; getline(cin, name);
            cout << "New Price: "; cin >> price;
            cout << "New People: "; cin >> people;
            cin.ignore();
            cout << "New Booking Date: "; getline(cin, date);
            string req = "UPDATE|" + to_string(index) + "|" + name + "|" + to_string(price) + "|" + to_string(people) + "|" + date;
            sendRequest(req);
        }
        else if (choice == 4) {
            int index;
            cout << "Enter index to delete: "; cin >> index;
            sendRequest("DELETE|" + to_string(index));
        }
        else break;
    }
    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <winsock2.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

struct Tour {
    string name;
    float price;
    int people;
    string book_date;

    string serialize() const {  
        return name + "|" + to_string(price) + "|" + to_string(people) + "|" + book_date;
    }

    static Tour deserialize(const string& data) {
        Tour t;
        string temp = data;
        size_t pos = 0;

        pos = temp.find("|"); t.name = temp.substr(0, pos); temp.erase(0, pos + 1);
        pos = temp.find("|"); t.price = stof(temp.substr(0, pos)); temp.erase(0, pos + 1);
        pos = temp.find("|"); t.people = stoi(temp.substr(0, pos)); temp.erase(0, pos + 1);
        t.book_date = temp;
        return t;
    }
};

vector<Tour> loadTours() {
    ifstream fin("tours.txt");
    vector<Tour> tours;
    string line;
    while (getline(fin, line)) {
        tours.push_back(Tour::deserialize(line));
    }
    return tours;
}

void saveTours(const vector<Tour>& tours) {
    ofstream fout("tours.txt");
    for (const auto& t : tours) {
        fout << t.serialize() << endl;  // ? Safe usage now
    }
}

string handleRequest(string request) {
    vector<Tour> tours = loadTours();
    string cmd = request.substr(0, request.find("|"));
    request.erase(0, cmd.length() + 1);

    if (cmd == "ADD") {
        tours.push_back(Tour::deserialize(request));
        saveTours(tours);
        return "Tour added successfully.\n";
    }
    else if (cmd == "VIEW") {
        if (tours.empty()) return "No tours found.\n";
        string res;
        int i = 0;
        for (const auto& t : tours) {
            res += "[" + to_string(i++) + "] " + t.serialize() + "\n";
        }
        return res;
    }
    else if (cmd == "UPDATE") {
        int index = stoi(request.substr(0, request.find("|")));
        request.erase(0, request.find("|") + 1);
        if (index < 0 || index >= (int)tours.size()) return "Invalid index.\n";
        tours[index] = Tour::deserialize(request);
        saveTours(tours);
        return "Tour updated.\n";
    }
    else if (cmd == "DELETE") {
        int index = stoi(request);
        if (index < 0 || index >= (int)tours.size()) return "Invalid index.\n";
        tours.erase(tours.begin() + index);
        saveTours(tours);
        return "Tour deleted.\n";
    }

    return "Unknown command.\n";
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
        if (recv_size == SOCKET_ERROR || recv_size == 0) {
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

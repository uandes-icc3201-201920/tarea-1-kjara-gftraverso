#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <sys/un.h>
#include <map>
#include <iterator> 
#include <cstdlib>
#include <pthread.h>// threads
#include <ctime>
 
using namespace std;
map <int, string> KVStore;
int NumItems = 0;
char buf[4096];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

string SelectInfo(string str, int inst){
    string str2;
    bool copy = false;
    bool Error = true;
    if (inst == 1 || inst == 2){
        bool a = false;
        for (int i = 0; i < (int)str.length()-2; ++i){
            if (a){
                if (str[i] == ','){
                    Error = false;
                }
            }
            if (str[i] == '('){
                a = true;
            }
        }
        if (!a){
            return NULL;
        }
    }
    if (inst == 0){
        for (int i = 0; i < (int)str.length()-1; ++i){
            if (copy){
                str2 += str[i];
            }
            if (str[i] == '('){
                copy = true;
            }
        }
    }
    else if (inst == 1 && (!Error)){
        for (int i = 0; i < (int)str.length(); ++i){
            if (copy){
                if (str[i] == ','){
                    break;
                }
                str2 += str[i];
            }
            if (str[i] == '('){
                copy = true;
            }
        }
    }
    else if (inst == 2 && (!Error)){
        for (int i = 0; i < (int)str.length()-1; ++i){
            if (copy){
                str2 += str[i];
            }
            if (str[i] == ','){
                copy = true;
            }
        }
    }
    
    return str2;
}

string SplitString(string str){
    string str2;
    for (int i = 0; i < (int)str.length(); ++i){
        if (str[i] == '('){
            break;
        }
        str2 += str[i]; 
    }
    return str2;
}

bool ValidString(string str){
    bool valid = false;
    for (int i = 0; i < (int)str.length(); ++i){
        if (str[i] == '('){
            valid = true;
            break;
        }
    }
    if ((valid) && (str[str.length()-1] == ')')){
        valid = true;
    } else {
        valid = false;
    }
    return valid;
}

int CreateSocket(string str){
    int length = str.length();
    char socket_path[length];
    for (int i = 0; i < length; ++i){
        socket_path[i] = str[i];
    }

    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock == -1){
        cout << "Can't create a socket! Quitting" << endl;
        return -1;
    }
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
    unlink(socket_path);
    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1){
        cout << "bind Error" << endl;
        return -1;
    }
    if(listen(sock, 10) == -1){
        cout << "listen Error" << endl;
        return -1;
    }
    return sock;
}

int connecting(int sock, sockaddr_un client, socklen_t clientSize){

    int Socket = accept(sock, (sockaddr*)&client, &clientSize);
    return Socket;
}

void* Thread(void* Socket){
    int clientSocket = *((int *)Socket);
    string value;
    int key ;
    while(true){
        string serverInput = "";
        memset(buf, 0, 4096);
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        string StrCliente = string(buf, 0, bytesReceived);
        if (StrCliente == "connect")
        {
            cout << "Client connected!" << endl;
            serverInput = "Client connected!";
        }
        if (bytesReceived == 0){
            cout << "Client disconnected " << endl;
        }
        pthread_mutex_lock(&lock);
        if (ValidString(StrCliente)){
            if (SplitString(StrCliente) == "insert"){
                serverInput = "Elemento insertado correctamente";
                if (SelectInfo(StrCliente,1).length() > 0){
                    key = stoi(SelectInfo(StrCliente, 1));
                    value = SelectInfo(StrCliente, 2);
                    map<int, string>::iterator itr; 
                    for (itr = KVStore.begin(); itr != KVStore.end(); ++itr){ 
                        if (itr -> first == key){
                            serverInput = "Error, Key ya existente!";
                        }
                    }
                    KVStore.insert(pair<int, string>(key, value));
                } else {
                    value = SelectInfo(StrCliente, 0);
                    bool correctkey = false;
                    srand(time(0));
                    int contador = 0;
                    if (NumItems > 0){
                        while(!correctkey){
                            key = rand()%101;
                            map<int, string>::iterator itr; 
                            for (itr = KVStore.begin(); itr != KVStore.end(); ++itr) { 
                                if ((itr -> first) == key){

                                    break;
                                }
                                if (contador == NumItems){
                                    correctkey = true;
                                }
                                contador++;
                            } 
                        }
                    } else {
                        key = 1;
                    }
                    KVStore.insert(pair<int, string>(key, value));
                    serverInput = to_string(key);
                }
                NumItems++;
            }
            else if (SplitString(StrCliente) == "get"){
                key = stoi(SelectInfo(StrCliente, 0));
                map<int, string>::iterator itr; 
                for (itr = KVStore.begin(); itr != KVStore.end(); ++itr) { 
                    if ((itr -> first) == key){
                        serverInput = itr->second;
                    }
                }
            }
            else if (SplitString(StrCliente) == "peek"){
                key = stoi(SelectInfo(StrCliente, 0));
                map<int, string>::iterator itr; 
                serverInput = "false";
                for (itr = KVStore.begin(); itr != KVStore.end(); ++itr) { 
                    if ((itr -> first) == key){
                        serverInput = "true";
                    }
                }
            }
            else if (SplitString(StrCliente) == "update"){
                key = stoi(SelectInfo(StrCliente, 1));
                value = SelectInfo(StrCliente, 2);
                map<int, string>::iterator itr; 
                bool exist = false;
                for (itr = KVStore.begin(); itr != KVStore.end(); ++itr){ 
                    if ((itr -> first) == key){
                        exist = true;
                    }
                }
                if (exist){
                    KVStore.erase(key);
                    KVStore.insert(pair<int, string>(key, value));
                    serverInput = "Successful update";
                } else {
                    serverInput = "Update fail, key no existe!";
                }
            }
            else if (SplitString(StrCliente) == "delete"){
                serverInput = "no existe tal Key.";
                key = stoi(SelectInfo(StrCliente, 0));
                bool exist = false;
                map<int, string>::iterator itr;
                for (itr = KVStore.begin(); itr != KVStore.end(); ++itr){ 
                    if ((itr -> first) == key){
                        serverInput = itr -> second;
                        exist = true;
                    }
                } 
                if (exist)
                {
                    KVStore.erase(key);
                }
            }
            string instruction = SplitString(StrCliente);
            string info = SelectInfo(StrCliente,2);
        }
        else if (StrCliente == "disconnect" || StrCliente == "quit"){
            cout << "Client disconnected" << endl;
            serverInput = "Client disconnected";
            send(clientSocket, serverInput.c_str(), serverInput.size() + 1, 0);
            close(clientSocket);

            break;
        }
        else if (StrCliente == "list"){
            map<int, string>::iterator itr; 
            serverInput += "\tKey\tValue\n";
            for (itr = KVStore.begin(); itr != KVStore.end(); ++itr) { 
                serverInput += "\t        "; 
                serverInput += to_string(itr->first); 
                serverInput += '\t'; 
                serverInput += itr->second; 
                serverInput += '\n'; 
            } 
        } 
        else if (StrCliente != "connect"){
            serverInput = "Error, input no valido.";
        }
        send(clientSocket, serverInput.c_str(), serverInput.size() + 1, 0);
        pthread_mutex_unlock(&lock);
    }
    close(clientSocket);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]){
    string path = "/tmp/db.tuples.sock";
    int clientSocket;
    if (argc > 1){
        for (int i = 0; i < argc; ++i){
            if (argv[i][1] == 's' && i+1 <= argc){
                path = argv[i+1];
            }
        }
    }

    cout << "\nSocket path: "<< path << endl;

    int listening = CreateSocket(path);
    if (listening == -1){
        return 1;
    }

    while (true){
        pthread_t thread1;
        sockaddr_un client;
        socklen_t clientSize = sizeof(client);
        // Wait for a connection
        clientSocket = connecting(listening, client, clientSize);
        if( pthread_create( &thread1 , NULL , Thread, (void*) &clientSocket) < 0)
        {
            cout << "No se pudo crear el thread" << endl;
            return 1;
        }
    }
    return 0;
}
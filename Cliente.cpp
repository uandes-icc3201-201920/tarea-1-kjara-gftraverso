#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <ctime>
 
using namespace std;

int main(int argc, char const *argv[]){
    string path = "/tmp/db.tuples.sock";  
	int sock;
    char buf[4096];
    string userInput;
    bool connected = false;

    while(true){
	    
		if (userInput == "connect"){
        	if (argc > 1){
		        for (int i = 0; i < argc; ++i){
		            if (argv[i][1] == 's' && i+1 <= argc){
		                path = argv[i+1];
		            }
		        }
		    }

			int length = path.length();
		    char socket_path[length];
		    for (int i = 0; i < length; ++i){
		        socket_path[i] = path[i];
	    	}
	    	socket_path[length] = '\0';
        	sock = socket(AF_UNIX, SOCK_STREAM, 0);
		    if (sock == -1){
		        return -1;
		    }
		    sockaddr_un addr;
		    addr.sun_family = AF_UNIX;
		    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

		    //	Connect to the server on the socket
		    int connectRes = connect(sock, (sockaddr*)&addr, sizeof(addr));
		    if (connectRes == -1){
		    	cout << "error to connect!" << endl;
		    	connected = false;
		        return 1;
		    }else{
		    	connected = true;
		    }
        }

        else if (userInput == "quit"){
        	if (connected){
        		int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
		        if (sendRes == -1){
		            cout << "Could not send to server!\r\n";
		            continue;
		        }

		        //		Wait for response
		        memset(buf, 0, 4096);
		        int bytesReceived = recv(sock, buf, 4096, 0);
		        if (bytesReceived == -1){
		            cout << "There was an error getting response from server\r\n";
		    	} else {
		            //		Display response
		            cout << "[SERVER]: " << string(buf, bytesReceived) << "\r\n";
		        }
			}
		    break;
        }

        if (connected){
	        //		Send to server
	        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	        if (sendRes == -1){
	            cout << "Could not send to server!\r\n";
	            continue;
	        }

	        //		Wait for response
	        memset(buf, 0, 4096);
	        int bytesReceived = recv(sock, buf, 4096, 0);
	        if (bytesReceived == -1){
	            cout << "There was an error getting response from server\r\n";
	        } else {
	            //		Display response
	            cout << "[SERVER]: " << string(buf, bytesReceived) << "\r\n";
	        }

	        if (userInput == "disconnect"){
	        	connected = false;
    			close(sock);
    			continue;
	        }
        }
        cout << "[Cliente]: ";
	    getline(cin, userInput);
    }

    //	Close the socket
    close(sock);

    return 0;
}
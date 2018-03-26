#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "serverhandler.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <sstream>

using namespace std;

/*
 * Read an integer from a client.
 */
int readAction(const shared_ptr<Connection>& conn) {
		unsigned char byte = conn->read();
		return byte;
}

/*
 * Send a string to a client.
 */
void writeString(const shared_ptr<Connection>& conn, const string& s) {
	for (char c : s) {
		conn->write(c);
	}
	conn->write('$');
}

string translateCommand(const unsigned int cmd, const shared_ptr<Connection>& conn, Serverhandler& sh){
	cout << cmd << endl;
	switch(cmd){
		case 1: return sh.listNewsGroup(conn);
		case 2: return sh.createNewsGroup(conn);
		case 3:	return sh.deleteNewsGroup(conn);
		case 4:	return sh.listArticles(conn);
		case 5: return sh.createArticle(conn);
		case 6: return sh.deleteArticle(conn);
		case 7: return sh.getArticle(conn);
		default: return "Wrong input";
	}
}

int main(int argc, char* argv[]){
	if (argc != 2) {
		cerr << "Usage: myserver port-number" << endl;
		exit(1);
	}

	int port = -1;
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}

	Server server(port);
	if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}

	Serverhandler sh;
	while (true) {
		auto conn = server.waitForActivity();
		if (conn != nullptr) {
			try {
				unsigned int action = readAction(conn) - '0';
				sh.setAction(action);
				string response = translateCommand(action, conn, sh);



				writeString(conn, response);
			} catch (ConnectionClosedException&) {
				server.deregisterConnection(conn);
				cout << "Client closed connection" << endl;
			}
		} else {
			conn = make_shared<Connection>();
			server.registerConnection(conn);
			cout << "New client connects" << endl;
		}
	}
}

#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "serverhandler.h"
#include "database1.h"
#include "database.h"
#include "messagehandler.h"

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

string translateCommand(const unsigned int cmd, Serverhandler& sh){
	cout << cmd << endl;
	switch(cmd){
		case 1: sh.listNewsGroups();
		case 2: sh.createNewsGroup();
		case 3:	sh.deleteNewsGroup();
		case 4:	sh.listArticles();
		case 5: sh.createArticle();
		case 6: sh.deleteArticle();
		case 7: sh.getArticle();
		default: cout << "Wrong input" << endl;
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
	while (true) {
		auto conn = server.waitForActivity();
		if (conn != nullptr) {
			Database* database = new Database1();
			MessageHandler mh(conn);
			Serverhandler sh(database, mh);
			try {
				unsigned int action = readAction(conn);
				sh.setAction(action);
				string response = translateCommand(action, sh);



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

#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "serverhandler.h"
#include "database1.h"
#include "database2.h"
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

void translateCommand(const Protocol p, Serverhandler& sh){
	switch(p){
		case Protocol::COM_LIST_NG: sh.listNewsGroups(); break;
		case Protocol::COM_CREATE_NG: sh.createNewsGroup(); break;
		case Protocol::COM_DELETE_NG:	sh.deleteNewsGroup(); break;
		case Protocol::COM_LIST_ART:	sh.listArticles(); break;
		case Protocol::COM_CREATE_ART: sh.createArticle(); break;
		case Protocol::COM_DELETE_ART: sh.deleteArticle(); break;
		case Protocol::COM_GET_ART: sh.getArticle(); break;
		default: cout << "Wrong input" << endl;
	}
}

int main(int argc, char* argv[]){
	if (argc != 3) {
		cerr << "Usage: newsserver port-number database: 1 or 2" << endl;
		exit(1);
	}

	int port = -1;
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	int db = -1;
	try {
		db = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Invalid database. " << e.what() << endl;
		exit(1);
	}

	Server server(port);
	if (!server.isReady()) {
		cerr << "Server initializaation error." << endl;
		exit(1);
	}
	Database* database;
	if(db == 1) {
		cout << "db1" << endl;
		database = new Database1();
	} else {
		cout << "db2" << endl;
		database = new Database2();
	}
	while (true) {
		auto conn = server.waitForActivity();
		if (conn != nullptr) {
			MessageHandler mh(conn);
			Serverhandler sh(database, mh);
			try {
				Protocol action = mh.recvCode();
				sh.setAction(static_cast<unsigned int>(action));
				translateCommand(action, sh);
				//end
				if(mh.recvCode() != Protocol::COM_END) {
          throw ConnectionClosedException();
        }
				// cout << "sent" << endl;
				cout << "sent2" << endl;
				//writeString(conn, response);
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

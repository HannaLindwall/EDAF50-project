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
		database = new Database1();
	} else {
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

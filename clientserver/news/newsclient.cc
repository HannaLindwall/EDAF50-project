/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"
#include "inputhandler.h"
#include "messagehandler.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <sstream>

using namespace std;

void getHelp() {
  cout << "1 = list newsgroups" << endl;
  cout << "2 = create newsgroup" << endl;
  cout << "3 = delete newsgroup" << endl;
  cout << "4 = list articles" << endl;
  cout << "5 = create article" << endl;
  cout << "6 = delete article" << endl;
  cout << "7 = get article" << endl;
}
string readAction(const Connection& conn) {
	string s;
	char ch;
	while ((ch = conn.read()) != '$') {
		s += ch;
	}
	return s;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: myclient host-name port-number" << endl;
		exit(1);
	}

	int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}

	Connection conn(argv[1], port);
	if (!conn.isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
  MessageHandler mh(conn);
  Inputhandler ih(mh);
	cout << "Enter a number to choose an action or enter HELP: " << endl;
	string input;
	while (cin >> input) {
		try {
      if(input == "HELP") {
        getHelp();
      } else {
        unsigned int act;
        try {
					//check that first input is a number
      	  act = stoi(input);
					//check that it's an action
          unsigned int ret_act = ih.perform_action(act);
          if(ret_act != 0) {
						//create the correct input to the server
						ih.sendParameters();
            //cout << "sent" << endl;
						string reply = ih.readParameters();
            cout << reply << endl;
            //ANS_END
            mh.recvCode();
            //cout << "reply " << reply << endl;
            //reply = ih.translateReply(reply);

          } else {
            cout << "Command could not be found" << endl;
          }

        } catch (exception& e) {
      		cerr << "Invalid input h" << endl;
      	}
      }
      cout << "Enter a number to choose an action or enter HELP" << endl;
		} catch (ConnectionClosedException&) {
			cout << " no reply from server. Exiting." << endl;
			exit(1);
		}
	}
}

/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

/*
 * Send an integer to the server as four bytes.
 */
void writeNumber(const Connection& conn, int value) {
	conn.write((value >> 24) & 0xFF);
	conn.write((value >> 16) & 0xFF);
	conn.write((value >> 8)	 & 0xFF);
	conn.write(value & 0xFF);
}
void getHelp() {
  cout << "1 = list newsgroups" << endl;
  cout << "2 = create newsgroup" << endl;
  cout << "3 = delete newsgroup" << endl;
  cout << "4 = list articles" << endl;
  cout << "5 = create article" << endl;
  cout << "6 = delete article" << endl;
  cout << "7 = get article" << endl;
  cout << "8 = command end" << endl;
  cout << "40 = string" << endl;
  cout << "41 = number" << endl;
  cout << "signal input is string or number, if string enter length also" << endl;
  cout << "all commands must end with 8" << endl;
}

/*
 * Read a string from the server.
 */
string readString(const Connection& conn) {
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
  ClientHandler ch;
	cout << "Enter a number to choose an action or enter HELP: " << endl;
	string input;
	while (cin >> input) {
		try {
      if(input == "HELP") {
        getHelp();
      } else {
        int act;
        try {
      	  act = stoi(input);
          string ret_act = ch.action(act);

          writeNumber(conn, nbr);
          string reply = readString(conn);
          cout << " " << reply << endl;

        } catch (exception& e) {
      		cerr << "Invalid input" << endl;
      	}
      }
      cout << "Enter a number to choose an action or enter HELP << endl;"
		} catch (ConnectionClosedException&) {
			cout << " no reply from server. Exiting." << endl;
			exit(1);
		}
	}
}

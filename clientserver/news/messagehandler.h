#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>
#include <memory>
#include <cstdlib>
#include <iostream>
#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"
using namespace std;

class MessageHandler {
public:
  MessageHandler(std::shared_ptr<Connection>& c);
  MessageHandler(Connection& c);
  void sendByte(unsigned char code);
  void sendCode(Protocol p);
  void sendInt(unsigned int value);
  void sendIntParameter(int param);
  void sendStringParameter(string param);
  unsigned char recvByte();
  Protocol recvCode();
  int recvInt();
  int recvIntParameter();
  string recvStringParameter();
private:
  std::shared_ptr<Connection> conn;

};
#endif

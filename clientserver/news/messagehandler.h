#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>
#include <memory>
#include <cstdlib>
#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"
using std::string;

class MessageHandler {
public:
  MessageHandler(std::shared_ptr<Connection>& c);
  MessageHandler(Connection& c);
  void sendByte(unsigned char code);
  void sendCode(Protocol p);
  void sendInt(int value);
  void sendIntParameter(int param);
  void sendStringParameter(string param);
  int recvByte();
  int recvCode();
  int recvInt();
  int recvIntParameter();
  string recvStringParameter();
private:
  std::shared_ptr<Connection> conn;

};
#endif

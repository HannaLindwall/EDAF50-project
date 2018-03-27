#include <string>
#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"
using std::string;

class MessageHandler {
public:
  MessageHandler(Connection& c) : conn(&c) {}
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
  Connection* conn;

};

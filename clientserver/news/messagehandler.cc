#include "messagehandler.h"

MessageHandler::MessageHandler(std::shared_ptr<Connection>& c) : conn(c) {}

MessageHandler::MessageHandler(Connection& c) : conn(&c) {}

void MessageHandler::sendByte(unsigned char code){
  //cout << code << endl;
  conn->write(code);
}
void MessageHandler::sendCode(Protocol p) {
  sendInt(static_cast<unsigned int>(p));
}
void MessageHandler::sendInt(unsigned int value) {
  cout << value << endl;
  sendByte((value >> 24) & 0xFF);
  sendByte((value >> 16) & 0xFF);
  sendByte((value >> 8) & 0xFF);
  sendByte(value & 0xFF);
}
void MessageHandler::sendIntParameter(int param) {
  sendCode(Protocol::PAR_NUM);
  sendInt(param);
}
void MessageHandler::sendStringParameter(string param) {
  sendCode(Protocol::PAR_STRING);
  sendInt(param.length());
  for (unsigned int i = 0; i < param.length(); i++) {
    sendByte(param[i]);
  }
}
int MessageHandler::recvByte() {
  unsigned char code = conn->read();
  return code;
}
int MessageHandler::recvCode() {
  unsigned char code = recvInt();
  return code;
}
int MessageHandler::recvInt() {
  unsigned char b1 = recvByte();
  unsigned char b2 = recvByte();
  unsigned char b3 = recvByte();
  unsigned char b4 = recvByte();
  return (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
}

int MessageHandler::recvIntParameter() {
  unsigned int code = recvCode();
  return recvInt();
}
string MessageHandler::recvStringParameter() {
  unsigned int code = recvCode();
  unsigned int n = recvInt();

  string result;
  for (unsigned int i = 1; i <= n; i++) {
    unsigned char ch = conn->read();
    result += ch;
  }
  return result;
}

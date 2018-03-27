#include <string>
#include "connection.h"
#include "connectionclosedexception.h"

class MessageHandler {
public:
  MessageHandler(Connection& c) : conn(c) {}
private:
  Connection conn;

};

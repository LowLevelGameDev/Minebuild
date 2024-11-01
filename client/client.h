#pragma once
#include <interface.hpp>


/*
* Relies on interface
* renders changes signified by server to the client
* updates server with any client interaction
*/
class Client {
  Interface server;
public:
  bool open(Interface&& server) {}
  // seed creation
  // (create world from seed, safe server holds copy)
  // user input
  // drawing
  // END
};



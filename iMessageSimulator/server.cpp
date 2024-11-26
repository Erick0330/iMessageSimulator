#include "server.h"
#include <string>
using namespace std;


string Server::getName() const
{
    return name1;
}

void Server::setName(const string value)
{
    name1 = value;
}
Server::Server() : name1("")
{
}

Server::Server(const string value) : name1(value){
}

Server::Server(const Server& value) : name1(value.getName()){
}


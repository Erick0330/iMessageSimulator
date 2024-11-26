#ifndef SERVER_H
#define SERVER_H
#include <string>
using namespace std;

class Server
{
private:
    string name1;

public:
    Server();
    string getName() const;
    void setName(const string value);
    Server(const string value);
    Server(const Server &value);
};

#endif // SERVER_H

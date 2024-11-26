#ifndef MAIL_H
#define MAIL_H
#include <string>
#include "server.h"
#include "user.h"
using namespace std;

class Mail
{
private:
    User user;
    Server server;
    string text;

public:
    Mail();
    Mail(Mail &m);
    Server getServer() const;
    void setServer(Server value);
    User getUser() const;
    void setUser(User value);
    string getText() const;
    void setText(const string value);
    Mail(string &serve, string &use, string &str);
};

#endif // MAIL_H

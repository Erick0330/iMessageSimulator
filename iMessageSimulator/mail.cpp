#include "mail.h"


Server Mail::getServer() const
{
    return server;
}

void Mail::setServer( Server value)
{
    server.setName(value.getName());
}

User Mail::getUser() const
{
    return user;
}

void Mail::setUser( User value)
{
    user.setName(value.getName());
}

string Mail::getText() const
{
    return text;
}

void Mail::setText(const string value)
{
    text = value;
}

Mail::Mail() : server(), user(), text("")
{
}

Mail::Mail(string &serve, string &use, string &str) : server(serve), user(use), text(str){
}

Mail::Mail(Mail &m) : server(m.getServer()), user(m.getUser()) , text(m.getText())
{
}

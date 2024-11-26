#include "user.h"
#include <string>
using namespace std;

string User::getName() const
{
    return name;
}

void User::setName(const string value)
{
    name = value;
}
User::User() : name("")
{
}

User::User(const string value) : name(value){
}

User::User(const User& value) : name(value.getName()){
}

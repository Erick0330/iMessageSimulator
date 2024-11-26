#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User
{
private:
    string name;
public:
    User();
    string getName() const;
    void setName(const string value);
    User(const string value);
    User(const User &value);
};

#endif // USER_H

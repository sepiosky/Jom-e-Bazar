#ifndef __EXCEPTIONS_H_
#define __EXCEPTIONS_H_


#include<iostream>
#include<exception>

class NotFound : public std::exception {
public:
virtual const char* what() const throw () { return "Not Found\n"; };
};

class BadRequest : public std::exception {
public:
virtual const char* what() const throw () { return "Bad Request\n"; };
};

class PermissionDenied : public std::exception {
public:
virtual const char* what() const throw () { return "Permission Denied\n"; };
};

class UsernameExists : public std::exception {
public:
virtual const char* what() const throw () { return "Username Already Exists,Choose Anothe One\n"; };
};
class WrongPassword : public std::exception {
public:
virtual const char* what() const throw () { return "The Password You've Entered Is Wrong\n"; };
};
class MailExists : public std::exception {
public:
virtual const char* what() const throw () { return "This Mail Has An Account,Sign In\n"; };
};
class UserDoesntExists : public std::exception {
public:
virtual const char* what() const throw () { return "No Account With This Username Available\n"; };
};
class PasswordsAreNotSame : public std::exception {
public:
virtual const char* what() const throw () { return "Re-enter Password Correctly\n"; };
};
class BadComment : public std::exception {
public:
virtual const char* what() const throw () { return "Your Comment Is Inappropriate\n"; };
};


#endif

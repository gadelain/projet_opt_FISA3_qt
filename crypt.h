#include <string>

#ifndef CRYPT_H
#define CRYPT_H


class crypt
{
public:
    crypt();

};

char decale(char, char, int);
std::string decode(std::string, int);
std::string code(std::string, int);
char decale(char c, char debut, int decalage);
int img_import(std::string);

#endif // CRYPT_H

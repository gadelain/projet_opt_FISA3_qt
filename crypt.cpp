#include "crypt.h"
#include "cimageqt.h"

crypt::crypt()
{

}

char code(char c, int d) {
    if (c >= 'a' && c <= 'z')
        return decale(c, 'a', d);
    else if (c >= 'A' && c <= 'Z')
        return decale(c, 'A', d);
    else
        return c;
}

char decale(char c, char debut, int decalage) {
    while (decalage < 0)
        decalage += 26;
    return debut + (((c - debut) + decalage) % 26);
}

std::string code(std::string texte, int decalage) {
    const size_t taille = texte.size();
    std::string chaine(texte);
    for (size_t i = 0; i < taille; i++)
        chaine[i] = code(chaine[i], decalage);
    return chaine;
}

std::string decode(std::string texte, int decalage) {
    return code(texte, -decalage);
}

int img_import(std::string filepath) {
    int nb_cesar;


    return nb_cesar;
}


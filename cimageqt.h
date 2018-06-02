#include <string>
#ifndef CIMAGEQT_H
#define CIMAGEQT_H


class CImageQT
{
private :


        int              m_iHauteur;
        int              m_iLargeur;
        std::string      m_sNom;
        unsigned char*   m_pucData;
        unsigned char**  m_ppucPixel;

public:
    CImageQT();
    CImageQT(const std::string& nom);
    unsigned char*& operator() (int i, int j) const {
            return m_ppucPixel[i*m_iLargeur+j];
    }
    unsigned char*& operator() (int i) const {
            return m_ppucPixel[i];
    }
    int lireHauteur() const {
            return m_iHauteur;
    }

    int lireLargeur() const {
            return m_iLargeur;
    }
    std::string lireNom() const {
            return m_sNom;
    }
    int lireNbPixels() const {
            return m_iHauteur*m_iLargeur;
    }
};

#endif // CIMAGEQT_H

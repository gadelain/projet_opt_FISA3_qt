#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <cmath>
#include <vector>

#include "cimageqt.h"

#define MAGIC_NUMBER_BMP ('B'+('M'<<8))

CImageQT::CImageQT()
{

}

CImageQT::CImageQT(const std::string& name) {

    BITMAPFILEHEADER header;
    BITMAPINFOHEADER infoHeader;

    std::ifstream f(name.c_str(),std::ios::in | std::ios::binary); // transformation d'une string en chaîne de type C
    if (f.is_open()) {
        f.read((char*)&header,sizeof(BITMAPFILEHEADER));
        if (header.bfType != MAGIC_NUMBER_BMP)
            throw std::string("ouverture format BMP impossible ...");
        else {
            f.read((char*)&infoHeader,sizeof(BITMAPINFOHEADER));
            if (infoHeader.biCompression > 0)
                throw std::string("Format compresse non supporté...");
            else {
                if (infoHeader.biBitCount == 24) {
                    this->m_iHauteur = infoHeader.biHeight;
                    this->m_iLargeur = infoHeader.biWidth;
                    this->m_sNom.assign(name.begin(),name.end()-4);
                    this->m_pucData = new unsigned char[infoHeader.biHeight*infoHeader.biWidth*3];
                    this->m_ppucPixel = new unsigned char*[infoHeader.biHeight*infoHeader.biWidth];
                    for (int i=0;i<infoHeader.biHeight*infoHeader.biWidth;i++)
                        this->m_ppucPixel[i] = &this->m_pucData[3*i];

                    // gérer multiple de 32 bits via zéros éventuels ignorés
                    int complement = (((this->m_iLargeur*3-1)/4) + 1)*4 - this->m_iLargeur*3;

                    for (int i= m_iHauteur-1; i >= 0; i--) {
                        for (int j=0;j<m_iLargeur;j++) {
                            f.read((char*)&this->m_ppucPixel[i*m_iLargeur+j][2],sizeof(char));
                            f.read((char*)&this->m_ppucPixel[i*m_iLargeur+j][1],sizeof(char));
                            f.read((char*)&this->m_ppucPixel[i*m_iLargeur+j][0],sizeof(char));
                    }

                    char inutile;
                    for (int k=0; k< complement; k++)
                        f.read((char*)&inutile,sizeof(char));
                    }
                }
                else {
                    // cas d'une image en niveaux de gris
                    this->m_iHauteur = infoHeader.biHeight;
                    this->m_iLargeur = infoHeader.biWidth;
                    this->m_sNom.assign(name.begin(),name.end()-4);
                    this->m_pucData = new unsigned char[infoHeader.biHeight*infoHeader.biWidth*3];
                    this->m_ppucPixel = new unsigned char*[infoHeader.biHeight*infoHeader.biWidth];
                    for (int i=0;i<infoHeader.biHeight*infoHeader.biWidth;i++)
                        this->m_ppucPixel[i] = &this->m_pucData[3*i];

                    // lecture palette
                    unsigned char* palette=NULL;
                    palette = new unsigned char[256*4];
                    for (int indice=0;indice<4*256;indice++)
                        f.read((char*)&palette[indice],sizeof(char));

                    // gérer multiple de 32 bits via zéros éventuels ignorés
                    int complement = (((this->m_iLargeur-1)/4) + 1)*4 - this->m_iLargeur;
                    // passage du gris vers la couleur par duplication des valeurs
                    for (int i= m_iHauteur-1; i >= 0; i--) {
                        for (int j=0;j<m_iLargeur;j++) {
                            unsigned char temp;
                            f.read((char*)&temp,sizeof(char));
                            this->m_ppucPixel[i*m_iLargeur+j][0]=palette[4*temp+2];
                            this->m_ppucPixel[i*m_iLargeur+j][1]=palette[4*temp+1];
                            this->m_ppucPixel[i*m_iLargeur+j][2]=palette[4*temp];
                        }

                        char inutile;
                        for (int k=0; k< complement; k++)
                            f.read((char*)&inutile,sizeof(char));
                    }
                }
            }
        }
        f.close();
    }
    else
        throw std::string("Ouverture impossible !");
}


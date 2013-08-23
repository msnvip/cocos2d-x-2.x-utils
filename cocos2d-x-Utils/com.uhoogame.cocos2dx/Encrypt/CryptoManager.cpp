//
//  NSFileManager-AES.m
//  Encryption
//
//  Created by Jeff LaMarche on 2/12/09.
//  Copyright 2009 Jeff LaMarche Consulting. All rights reserved.
//

#include "CryptoManager.h"
#include <stdio.h>
#include <string>

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

void strcat_my(unsigned char* dest, unsigned char* src, unsigned long size)
{
	unsigned char* target = dest;
	long bufSize = strlen((char*)dest);
    
	target = target + bufSize;
	while(size > 0)
	{
		*target++ = *src++;
		--size;
	}
}

CryptoManager * CryptoManager::sharedManager()
{
    static CryptoManager instance;
    return &instance;
}

unsigned char* CryptoManager::decrytBuffer_to_buffer(unsigned char *encryptBuffer, unsigned long size)
{
    for (int i=0; i<size; ++i) {
        unsigned char buf = encryptBuffer[i];
        buf ^= XOR_NUMBER;
        encryptBuffer[i] = buf;
    }
    
    return  encryptBuffer;
}

unsigned char* CryptoManager::decryptFile_to_buffer(const std::string &fileName)
{
    unsigned char* pBuffer = NULL;
    
    
	FILE *pInf = fopen(fileName.c_str(), "rb");
    if (!pInf) {
        return NULL;
    }
    fseek(pInf,0,SEEK_END);
	long pSize = ftell(pInf);
	fseek(pInf,0,SEEK_SET);
	pBuffer = new unsigned char[pSize];
	pBuffer[0] = '\0';
    
    bool reached_eof = false;
    unsigned char buffer[16];
    unsigned long bytes_read;
    
    do {
        if ((bytes_read = fread(buffer, 1, 16, pInf)) < 16)
        {
            if (!feof(pInf))
            {
                perror("Error reading input file ring:");
                delete [] pBuffer;
                return  NULL;
            }
            else
            {
               
                reached_eof = true;
            }
        }
        
        //
        for (int i=0; i<bytes_read; ++i) {
            unsigned char buf = buffer[i];
            buf ^= XOR_NUMBER;
            buffer[i] = buf;
        }
        
        strcat_my(pBuffer, buffer, bytes_read);
        
    } while (!reached_eof);
    
    fclose(pInf);
    return pBuffer;
}



int CryptoManager::encryptFile(const std::string &infName, const std::string& outfName)
{
    
	FILE *pInf = fopen(infName.c_str(), "rt");
    string outFileName;
    if (outfName == "") {
        outFileName = outFileName + infName + ".aes";
    }
    else {
        outFileName = outfName;
    }
    FILE *pOutf = fopen(outFileName.c_str(), "wb");
    
    bool reached_eof = false;
    unsigned char buffer[16];
    unsigned long bytes_read;
    do {
        if ((bytes_read = fread(buffer, 1, 16, pInf)) < 16)
        {
            if (!feof(pInf))
            {
                perror("Error reading input file ring:");
                fclose(pInf);
                fclose(pOutf);
                return  -1;
            }
            else
            {
                reached_eof = true;
            }
        }
        
        //
        for (int i=0; i<bytes_read; ++i) {
            unsigned char buf = buffer[i];
            buf ^= XOR_NUMBER;
            buffer[i] = buf;
        }
        
        fwrite(buffer, 1, bytes_read, pOutf);
        
    } while (!reached_eof);
    
    fclose(pInf);
    fclose(pOutf);
    return 0;
}

int CryptoManager::decryptFile(const std::string &infName, const std::string& outfName)
{
	FILE *pInf = fopen(infName.c_str(), "rb");
    if (!pInf) {
        return -1;
    }
    string outFileName = infName;
    if (outfName == "") {
        outFileName = outFileName.substr(0,outFileName.length()-4);
    }
    else {
        outFileName = outfName;
    }
    FILE *pOutf = fopen(outFileName.c_str(), "wb");
    if (!pOutf) {
        return -1;
    }
    
    bool reached_eof = false;
    unsigned char buffer[16];
    unsigned long bytes_read;
    do {
        if ((bytes_read = fread(buffer, 1, 16, pInf)) < 16)
        {
            if (!feof(pInf))
            {
                perror("Error reading input file ring:");
                fclose(pInf);
                fclose(pOutf);
                return  -1;
            }
            else
            {
                reached_eof = true;
            }
        }
        
        //
        for (int i=0; i<bytes_read; ++i) {
            unsigned char buf = buffer[i];
            buf ^= XOR_NUMBER;
            buffer[i] = buf;
        }
        
        fwrite(buffer, 1, bytes_read, pOutf);
        
    } while (!reached_eof);
    
    fclose(pInf);
    fclose(pOutf);
    return 0;

}



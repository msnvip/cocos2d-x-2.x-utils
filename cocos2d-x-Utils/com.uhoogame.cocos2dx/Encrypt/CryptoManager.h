//
//  NSFileManager-AES.h
//  Encryption
//
//  Created by Jeff LaMarche on 2/12/09.
//  Copyright 2009 Jeff LaMarche Consulting. All rights reserved.
//

#ifndef AESMANAGER__H
#define AESMANAGER__H

#include <string>
#include <cstdlib>

class CryptoManager
{
public:
    static const unsigned char XOR_NUMBER = 0x1f;
    
    static CryptoManager * sharedManager();
    
    /****** Wangtiwei 的加密解密 ********/
	
    //输入需要被加密的文件的路径,加密并输出到指定路径
    static int encryptFile(const std::string& infName, const std::string& outfName = "");
	
	//解密文件并输出到指定的文件，成功返回0，失败返回-1
	static int decryptFile(const std::string& infName, const std::string& outfName = "");
	
    //解密文件并返回数据缓存，成功返回字符数组，使用完毕需要手动释放。失败返回NULL
	static unsigned char* decryptFile_to_buffer(const std::string& fileName);
	
    //传入加密的buffer和大小,成功返回解密后的字符数组,使用完需要手动释放.失败返回NULL
    static unsigned char* decrytBuffer_to_buffer(unsigned char* encryptBuffer, unsigned long size);
    
};

#endif
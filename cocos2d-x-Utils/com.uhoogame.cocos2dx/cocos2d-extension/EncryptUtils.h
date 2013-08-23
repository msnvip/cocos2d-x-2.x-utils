//
//  EncryptUtils.h
//  Android-aBooM
//
//  Created by mac on 13-6-14.
//
//

#ifndef __Android_aBooM__EncryptUtils__
#define __Android_aBooM__EncryptUtils__

#include <string>
#include "CCDictionary.h"
#include "CCArray.h"

USING_NS_CC;

/*
 *加密辅助函数
*/

#ifdef __cplusplus
extern "C" {
#endif
    
///CCDictionary
CCDictionary* createCCDictionaryWithData(unsigned char* data);
CCDictionary* createCCDictionaryWithEncrytData(unsigned char* encryptData);
CCDictionary* createCCDictionaryWithEncrytFile(const std::string& filename);

//CCArray
CCArray* createCCArrayWithData(unsigned char* data);
CCArray* createCCArrayWithEncryptData(unsigned char* encryptData);
CCArray* createCCArrayWithEncryptFile(const std::string& filename);
    
#ifdef __cplusplus
}
#endif

#endif /* defined(__Android_aBooM__EncryptUtils__) */

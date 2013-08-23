//
//  ParseActionSpecial.h
//  cocos2d-x-Utils
//
//  Created by mac on 13-7-5.
//
//

#ifndef __cocos2d_x_Utils__ParseActionSpecial__
#define __cocos2d_x_Utils__ParseActionSpecial__

#include "ActionParseBase.h"

/**
 * CCRepeatForever
 */
class ParserRepeatForever : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCSpeed
 */
class ParserSpeed : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};



#endif /* defined(__cocos2d_x_Utils__ParseActionSpecial__) */

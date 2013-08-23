//
//  ParseActionInstant.h
//  cocos2d-x-Utils
//
//  Created by mac on 13-7-5.
//
//

#ifndef __cocos2d_x_Utils__ParseActionInstant__
#define __cocos2d_x_Utils__ParseActionInstant__

#include "ActionParseBase.h"

/**
 * CCShow
 */
class ParserShow : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCHide
 */
class ParserHide : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCToggleVisibility
 */
class ParserToggleVisibility : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCFlipX
 */
class ParserFlipX : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCFlipY
 */
class ParserFlipY : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCPlace
 */
class ParserPlace : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};



#endif /* defined(__cocos2d_x_Utils__ParseActionInstant__) */

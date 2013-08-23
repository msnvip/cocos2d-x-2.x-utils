//
//  ParseActionEase.h
//  cocos2d-x-Utils
//
//  Created by mac on 13-7-5.
//
//

#ifndef __cocos2d_x_Utils__ParseActionEase__
#define __cocos2d_x_Utils__ParseActionEase__

#include "ActionParseBase.h"

/**
 * CCActionEase
 */
class ParserActionEase : public ActionParseBase{};

/**
 * CCEaseBackIn
 */
class ParserEaseBackIn : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseBackInOut
 */
class ParserEaseBackInOut : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseBackOut
 */
class ParserEaseBackOut : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseBounceIn
 */
class ParserEaseBounceIn : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseBounceInOut
 */
class ParserEaseBounceInOut : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseBounceOut
 */
class ParserEaseBounceOut : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseElasticIn
 */
class ParserEaseElasticIn : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseElasticInOut
 */
class ParserEaseElasticInOut : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseElasticOut
 */
class ParserEaseElasticOut : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseExponentialIn
 */
class ParserEaseExponentialIn : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseExponentialInOut
 */
class ParserEaseExponentialInOut : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseExponentialOut
 */
class ParserEaseExponentialOut : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseIn, CCeaseInOut, CCeaseOut
 */
class ParserSimpleEase : public ActionParseBase{};

/**
 * CCEaseIn
 */
class ParserEaseIn : public ParserSimpleEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseInOut
 */
class ParserEaseInOut : public ParserSimpleEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCeaseOut
 */
class ParserEaseOut : public ParserSimpleEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};


/**
 * CCEaseSineIn
 */
class ParserEaseSineIn : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCeaseSineOut
 */
class ParserEaseSineOut : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCEaseSineInOut
 */
class ParserEaseSineInOut : public ParserActionEase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};


#endif /* defined(__cocos2d_x_Utils__ParseActionEase__) */

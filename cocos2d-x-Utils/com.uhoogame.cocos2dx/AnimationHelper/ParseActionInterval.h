//
//  ParserMoveTo.h
//  cocos2d-x-Utils
//
//  Created by mac on 13-6-17.
//
//

#ifndef __cocos2d_x_Utils__ParserActionInterval__
#define __cocos2d_x_Utils__ParserActionInterval__

#include "ActionParseBase.h"

/**
 * CCAnchorPointTo
 */
class ParserAnchorPointTo : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCAnchorPointBy
 */
class ParserAnchorPointBy : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};


/**
 * CCScaleTo
 */
class ParserScaleTo : public ActionParseBase
{
public:
    CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCScaleBy
 */
class ParserScaleBy : public ActionParseBase
{	
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCMoveTo
 */
class ParserMoveTo : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCMoveBy
 */
class ParserMoveBy : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCJumpTo
 */
class ParserJumpTo : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCJumpBy
 */
class ParserJumpBy : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCBezierBy
 */
class ParserBezierBy : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCBezierTo
 */
class ParserBezierTo : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCFadeOut
 */
class ParserFadeOut : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCFadeIn
 */
class ParserFadeIn : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCFadeTo
 */
class ParserFadeTo : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCTintBy
 */
class ParserTintBy : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCTintTo
 */
class ParserTintTo : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCDelayTime
 */
class ParserDelayTime : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCRotateTo
 */
class ParserRotateTo : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCRotateBy
 */
class ParserRotateBy : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCSkewBy
 */
class ParserSkewBy : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCSkewTo
 */
class ParserSkewTo : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCBlink
 */
class ParserBlink : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCSequence
 */
class ParserSequence : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCRepeat
 */
class ParserRepeat : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCSpawn
 */
class ParserSpawn : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCReverseTime
 */
class ParserReverseTime : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCActionTween
 */
class ParserActionTween : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};


#endif /* defined(__cocos2d_x_Utils__ParserActionInterval__) */

//
//  ParseActionGrid3D.h
//  cocos2d-x-Utils
//
//  Created by mac on 13-7-5.
//
//

#ifndef __cocos2d_x_Utils__ParseActionGrid3D__
#define __cocos2d_x_Utils__ParseActionGrid3D__

#include "ActionParseBase.h"

/**
 * CCFlipX3D
 */
class ParserFlipX3D : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCFlipY3D
 */
class ParserFlipY3D : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCLiquid
 */
class ParserLiquid : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCLens3D
 */
class ParserLens3D : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCpageTurn3D
 */
class ParserPageTurn3D : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCRipple3D
 */
class ParserRipple3D : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCShaky3D
 */
class ParserShaky3D : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCTwirl
 */
class ParserTwirl : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCWaves
 */
class ParserWaves : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCWaves3D
 */
class ParserWaves3D : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

#endif /* defined(__cocos2d_x_Utils__ParseActionGrid3D__) */

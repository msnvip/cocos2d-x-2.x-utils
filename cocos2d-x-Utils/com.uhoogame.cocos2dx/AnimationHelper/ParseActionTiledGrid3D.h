//
//  ParseActionTiledGrid3D.h
//  cocos2d-x-Utils
//
//  Created by mac on 13-7-5.
//
//

#ifndef __cocos2d_x_Utils__ParseActionTiledGrid3D__
#define __cocos2d_x_Utils__ParseActionTiledGrid3D__

#include "ActionParseBase.h"

/**
 * CCFadeOut*Tiles 基类
 */
class ParserActionTiledGrid3D : public ActionParseBase{};

/**
 * CCFadeOutTRTiles
 */
class ParserFadeOutTRTiles : public ParserActionTiledGrid3D
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCFadeOutBLTiles
 */
class ParserFadeOutBLTiles : public ParserActionTiledGrid3D
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCFadeOutUpTiles
 */
class ParserFadeOutUpTiles : public ParserActionTiledGrid3D
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCFadeOutDownTiles
 */
class ParserFadeOutDownTiles : public ParserActionTiledGrid3D
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCJumpTiles3D
 */
class ParserJumpTiles3D : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
}
;

/**
 * CCShakyTiles3D
 */
class ParserShakyTiles3D : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCShatteredTiles3D
 */
class ParserShatteredTiles3D : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCShuffleTiles
 */
class ParserShuffleTiles : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCSplitCols
 */
class  ParserSplitCols : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCSplitRows
 */
class ParserSplitRows : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCTurnOffTiles
 */
class ParserTurnOffTiles : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};

/**
 * CCWavesTiles3D
 */
class ParserWavesTiles3D : public ActionParseBase
{
public:
	CCAction* parseAction(CCDictionary* dict);
};


#endif /* defined(__cocos2d_x_Utils__ParseActionTiledGrid3D__) */

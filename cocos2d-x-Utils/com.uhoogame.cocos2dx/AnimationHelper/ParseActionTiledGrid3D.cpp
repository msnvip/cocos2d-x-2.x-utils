//
//  ParseActionTiledGrid3D.cpp
//  cocos2d-x-Utils
//
//  Created by mac on 13-7-5.
//
//

#include "ParseActionTiledGrid3D.h"

CCAction* ParserFadeOutTRTiles::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	CCSize grid = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	return CCFadeOutTRTiles::create(duration, grid);
}

CCAction* ParserFadeOutBLTiles::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	CCSize grid = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	return CCFadeOutBLTiles::create(duration, grid);
}

CCAction* ParserFadeOutUpTiles::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	CCSize grid = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	return CCFadeOutUpTiles::create(duration, grid);
}

CCAction* ParserFadeOutDownTiles::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	CCSize grid = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	return CCFadeOutDownTiles::create(duration, grid);
}

CCAction* ParserJumpTiles3D::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	int jump = dict->valueForKey("Jump")->intValue();
	float amp = dict->valueForKey("Amp")->floatValue();
	CCSize gridSize = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	float ampRate = dict->valueForKey("AmpRate")->floatValue();
	CCJumpTiles3D* jumpTiles3D = CCJumpTiles3D::create(duration, gridSize, jump, amp);
	jumpTiles3D->setAmplitudeRate(ampRate);
	return  jumpTiles3D;
}

CCAction* ParserShakyTiles3D::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	int range = dict->valueForKey("Range")->intValue();
	bool shakeZ = dict->valueForKey("ShakeZ")->boolValue();
	CCSize grid = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	return CCShakyTiles3D::create(duration, grid, range, shakeZ);
}

CCAction* ParserShatteredTiles3D::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	int range = dict->valueForKey("Range")->intValue();
	bool shatterZ = dict->valueForKey("ShatterZ")->boolValue();
	CCSize grid = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	return CCShatteredTiles3D::create(duration, grid, range, shatterZ);
}

CCAction* ParserShuffleTiles::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	int seed = dict->valueForKey("Seed")->intValue();
	CCSize grid = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	return CCShuffleTiles::create(duration, grid, seed);
}

CCAction* ParserSplitCols::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	int cols = dict->valueForKey("Cols")->intValue();
	return CCSplitCols::create(duration, cols);
}

CCAction* ParserSplitRows::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	int rows = dict->valueForKey("Rows")->intValue();
	return CCSplitCols::create(duration, rows);
}

CCAction* ParserTurnOffTiles::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	int seed = dict->valueForKey("Seed")->intValue();
	CCSize grid = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	return CCTurnOffTiles::create(duration, grid, seed);
}

CCAction* ParserWavesTiles3D::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	int wave = dict->valueForKey("Wave")->intValue();
	float amp = dict->valueForKey("Amp")->floatValue();
	CCSize gridSize = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	float ampRate = dict->valueForKey("AmpRate")->floatValue();
	CCWavesTiles3D* wavesTiles3D = CCWavesTiles3D::create(duration, gridSize, wave, amp);
	wavesTiles3D->setAmplitudeRate(ampRate);
	return wavesTiles3D;
}
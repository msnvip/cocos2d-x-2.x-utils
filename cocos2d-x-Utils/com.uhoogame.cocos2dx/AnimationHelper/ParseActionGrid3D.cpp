//
//  ParseActionGrid3D.cpp
//  cocos2d-x-Utils
//
//  Created by mac on 13-7-5.
//
//

#include "ParseActionGrid3D.h"

CCAction* ParserFlipX3D::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();\
	return CCFlipX3D::create(duration);
}

CCAction* ParserFlipY3D::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	return CCFlipY3D::create(duration);
}

CCAction* ParserLiquid::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	int wave = dict->valueForKey("Wave")->intValue();
	float amp = dict->valueForKey("Amp")->floatValue();
	CCSize gridSize = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	float ampRate = dict->valueForKey("AmpRate")->floatValue();
	CCLiquid* liquid = CCLiquid::create(duration, gridSize, wave, amp);
	liquid->setAmplitudeRate(ampRate);
	return liquid;
}

CCAction* ParserLens3D::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	CCPoint position = CCPointFromString(dict->valueForKey("Position")->getCString());
	float radius = dict->valueForKey("Radius")->floatValue();
	CCSize grid = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	float effect = dict->valueForKey("Effect")->floatValue();
	CCLens3D* lens = CCLens3D::create(duration, grid, position, radius);
	lens->setLensEffect(effect);
	return lens;
}

CCAction* ParserPageTurn3D::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	CCSize grid = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	return CCPageTurn3D::create(duration, grid);
}

CCAction* ParserRipple3D::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	CCPoint position = CCPointFromString(dict->valueForKey("Position")->getCString());
	float radius = dict->valueForKey("Radius")->floatValue();
	int wave = dict->valueForKey("Wave")->intValue();
	float amp = dict->valueForKey("Amp")->floatValue();
	CCSize gridSize = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	float ampRate = dict->valueForKey("AmpRate")->floatValue();
	CCRipple3D* ripple3D = CCRipple3D::create(duration, gridSize, position, radius, wave, amp);
	ripple3D->setAmplitudeRate(ampRate);
	return ripple3D;
}

CCAction* ParserShaky3D::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	int range = dict->valueForKey("Range")->intValue();
	bool shakeZ = dict->valueForKey("ShakeZ")->boolValue();
	CCSize gridSize = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	return CCShaky3D::create(duration, gridSize, range, shakeZ);
}

CCAction* ParserTwirl::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	CCPoint position = CCPointFromString(dict->valueForKey("Position")->getCString());
	int twirls = dict->valueForKey("Twirls")->intValue();
	float amp = dict->valueForKey("Amp")->floatValue();
	CCSize gridSize = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	float ampRate = dict->valueForKey("AmpRate")->floatValue();
	CCTwirl* twirl = CCTwirl::create(duration, gridSize, position, twirls, amp);
	twirl->setAmplitudeRate(ampRate);
	return twirl;
}

CCAction* ParserWaves::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	int wave = dict->valueForKey("Wave")->intValue();
	float amp = dict->valueForKey("Amp")->floatValue();
	float ampRate = dict->valueForKey("AmpRate")->floatValue();
	CCSize gridSize = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	bool horizontal = dict->valueForKey("Horizontal")->boolValue();
	bool vertical = dict->valueForKey("Vertical")->boolValue();
	CCWaves* waves = CCWaves::create(duration, gridSize, wave, amp, horizontal, vertical);
	waves->setAmplitudeRate(ampRate);
	return waves;
}

CCAction* ParserWaves3D::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	int wave = dict->valueForKey("Wave")->intValue();
	float amp = dict->valueForKey("Amp")->floatValue();
	float ampRate = dict->valueForKey("AmpRate")->floatValue();
	CCSize gridSize = CCSizeFromString(dict->valueForKey("GridSize")->getCString());
	CCWaves3D* waves3D = CCWaves3D::create(duration, gridSize, wave, amp);
	waves3D->setAmplitudeRate(ampRate);
	return waves3D;
}
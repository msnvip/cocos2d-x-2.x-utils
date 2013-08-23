//
//  ParseActionInstant.cpp
//  cocos2d-x-Utils
//
//  Created by mac on 13-7-5.
//
//

#include "ParseActionInstant.h"

CCAction* ParserShow::parseAction(cocos2d::CCDictionary *dict)
{
	return CCShow::create();
}

CCAction* ParserHide::parseAction(cocos2d::CCDictionary *dict)
{
	return CCHide::create();
}

CCAction* ParserToggleVisibility::parseAction(cocos2d::CCDictionary *dict)
{
	return CCToggleVisibility::create();
}

CCAction* ParserFlipX::parseAction(cocos2d::CCDictionary *dict)
{
	bool x = dict->valueForKey("X")->boolValue();
	return CCFlipX::create(x);
}

CCAction* ParserFlipY::parseAction(cocos2d::CCDictionary *dict)
{
	bool y = dict->valueForKey("Y")->boolValue();
	return  CCFlipY::create(y);
}

CCAction* ParserPlace::parseAction(cocos2d::CCDictionary *dict)
{
	CCPoint position = CCPointFromString(dict->valueForKey("Position")->getCString());
	return CCPlace::create(position);
}
//
//  ParseActionSpecial.cpp
//  cocos2d-x-Utils
//
//  Created by mac on 13-7-5.
//
//

#include "ParseActionSpecial.h"
#include "ActionContext.h"

CCAction* ParserRepeatForever::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	if (dynamic_cast<CCActionInterval*>(action))
	{
		return CCRepeatForever::create((CCActionInterval *)action);
	}
	assert(false);
}

CCAction* ParserSpeed::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	float speed = dict->valueForKey("Speed")->floatValue();
	if (dynamic_cast<CCActionInterval *>(action))
	{
		return CCSpeed::create((CCActionInterval *)action, speed);
	}
	assert(false);
}


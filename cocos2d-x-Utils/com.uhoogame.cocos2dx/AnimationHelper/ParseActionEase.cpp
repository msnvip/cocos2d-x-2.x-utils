//
//  ParseActionEase.cpp
//  cocos2d-x-Utils
//
//  Created by mac on 13-7-5.
//
//

#include "ParseActionEase.h"
#include "ActionContext.h"

CCAction* ParserEaseBackIn::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseBackIn::create((CCActionInterval *)action);
}

CCAction* ParserEaseBackInOut::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseBackInOut::create((CCActionInterval *)action);
}

CCAction* ParserEaseBackOut::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseBackOut::create((CCActionInterval *)action);
}

CCAction* ParserEaseBounceIn::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseBounceIn::create((CCActionInterval *)action);
}

CCAction* ParserEaseBounceInOut::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseBounceInOut::create((CCActionInterval *)action);
}

CCAction* ParserEaseBounceOut::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseBounceOut::create((CCActionInterval *)action);
}

CCAction* ParserEaseElasticIn::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseElasticIn::create((CCActionInterval *)action);
}

CCAction* ParserEaseElasticInOut::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseElasticInOut::create((CCActionInterval *)action);
}

CCAction* ParserEaseElasticOut::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseElasticOut::create((CCActionInterval *)action);
}

CCAction* ParserEaseExponentialIn::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseExponentialIn::create((CCActionInterval *)action);
}

CCAction* ParserEaseExponentialInOut::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseExponentialInOut::create((CCActionInterval *)action);
}

CCAction* ParserEaseExponentialOut::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseExponentialOut::create((CCActionInterval *)action);
}

CCAction* ParserEaseIn::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	float rate = dict->valueForKey("Rate")->floatValue();
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseIn::create((CCActionInterval *)action, rate);
}

CCAction* ParserEaseInOut::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	float rate = dict->valueForKey("Rate")->floatValue();
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseInOut::create((CCActionInterval *)action, rate);
}

CCAction* ParserEaseOut::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	float rate = dict->valueForKey("Rate")->floatValue();
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseOut::create((CCActionInterval *)action, rate);
}

CCAction* ParserEaseSineIn::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseSineIn::create((CCActionInterval *)action);
}

CCAction* ParserEaseSineInOut::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseSineInOut::create((CCActionInterval *)action);
}

CCAction* ParserEaseSineOut::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary *)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return CCEaseSineOut::create((CCActionInterval *)action);
}

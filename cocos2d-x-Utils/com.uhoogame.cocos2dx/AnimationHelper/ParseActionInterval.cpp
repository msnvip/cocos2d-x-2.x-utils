//
//  ParserMoveTo.cpp
//  cocos2d-x-Utils
//
//  Created by mac on 13-6-17.
//
//

#include "ParseActionInterval.h"
#include "CCActionExtension.h"
#include "ActionContext.h"

CCAction* ParserAnchorPointTo::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	CCPoint anchorPoint = CCPointFromString(dict->valueForKey("AnchorPoint")->getCString());
	CCAction* action = CCAnchorPointTo::create(duration, anchorPoint);
	return action;
}

CCAction* ParserAnchorPointBy::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	CCPoint anchorPoint = CCPointFromString(dict->valueForKey("AnchorPoint")->getCString());
	CCAction* action = CCAnchorPointBy::create(duration, anchorPoint);
	return action;
}

CCAction* ParserScaleTo::parseAction(CCDictionary* dict)
{
    
    float scaleX = dict->valueForKey("ScaleX")->floatValue();
    float scaleY = dict->valueForKey("ScaleY")->floatValue();
    float duration = dict->valueForKey("Duration")->floatValue();
    CCAction* action = CCScaleTo::create(duration, scaleX, scaleY);
    return action;
}

CCAction* ParserScaleBy::parseAction(cocos2d::CCDictionary *dict)
{
	float scaleX = dict->valueForKey("ScaleX")->floatValue();
    float scaleY = dict->valueForKey("ScaleY")->floatValue();
    float duration = dict->valueForKey("Duration")->floatValue();
    CCAction* action = CCScaleBy::create(duration, scaleX, scaleY);
    return action;
}

CCAction* ParserMoveTo::parseAction(cocos2d::CCDictionary *dict)
{
	CCPoint point = CCPointFromString(dict->valueForKey("Position")->getCString());
	float duration = dict->valueForKey("Duration")->floatValue();
	return CCMoveTo::create(duration, point);
}

CCAction* ParserMoveBy::parseAction(cocos2d::CCDictionary *dict)
{
	CCPoint point = CCPointFromString(dict->valueForKey("Position")->getCString());
	float duration = dict->valueForKey("Duration")->floatValue();
	return CCMoveBy::create(duration, point);
}

CCAction* ParserJumpTo::parseAction(cocos2d::CCDictionary *dict)
{
	CCPoint point = CCPointFromString(dict->valueForKey("Position")->getCString());
	float duration = dict->valueForKey("Duration")->floatValue();
	float height = dict->valueForKey("Height")->floatValue();
	unsigned int jumps = dict->valueForKey("Jumps")->uintValue();
	return CCJumpTo::create(duration, point, height, jumps);
}

CCAction* ParserJumpBy::parseAction(cocos2d::CCDictionary *dict)
{
	CCPoint point = CCPointFromString(dict->valueForKey("Position")->getCString());
	float duration = dict->valueForKey("Duration")->floatValue();
	float height = dict->valueForKey("Height")->floatValue();
	unsigned int jumps = dict->valueForKey("Jumps")->uintValue();
	return CCJumpBy::create(duration, point, height, jumps);
}

CCAction* ParserBezierBy::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	ccBezierConfig config;
	CCDictionary* configDict = (CCDictionary*)dict->objectForKey("BezierConfig");
	config.endPosition = CCPointFromString(configDict->valueForKey("EndPosition")->getCString());
	config.controlPoint_1 = CCPointFromString(configDict->valueForKey("ControlPoint1")->getCString());
	config.controlPoint_2 = CCPointFromString(configDict->valueForKey("ControlPoint2")->getCString());
	return CCBezierBy::create(duration, config);
}

CCAction* ParserBezierTo::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	ccBezierConfig config;
	CCDictionary* configDict = (CCDictionary*)dict->objectForKey("BezierConfig");
	config.endPosition = CCPointFromString(configDict->valueForKey("EndPosition")->getCString());
	config.controlPoint_1 = CCPointFromString(configDict->valueForKey("ControlPoint1")->getCString());
	config.controlPoint_2 = CCPointFromString(configDict->valueForKey("ControlPoint2")->getCString());
	return CCBezierTo::create(duration, config);
}

CCAction* ParserFadeOut::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	return CCFadeOut::create(duration);
}

CCAction* ParserFadeIn::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	return CCFadeIn::create(duration);
}

CCAction* ParserFadeTo::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	unsigned int opacity = dict->valueForKey("Opacity")->uintValue();
	return CCFadeTo::create(duration, opacity);
}

CCAction* ParserTintBy::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	GLshort red = dict->valueForKey("Red")->uintValue();
	GLshort green = dict->valueForKey("Green")->uintValue();
	GLshort blue = dict->valueForKey("Blue")->uintValue();
	return CCTintBy::create(duration, red, green, blue);
}

CCAction* ParserTintTo::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	GLshort red = dict->valueForKey("Red")->uintValue();
	GLshort green = dict->valueForKey("Green")->uintValue();
	GLshort blue = dict->valueForKey("Blue")->uintValue();
	return CCTintTo::create(duration, red, green, blue);
}

CCAction* ParserDelayTime::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	return CCDelayTime::create(duration);
}

CCAction* ParserRotateTo::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	float angle = dict->valueForKey("Angle")->floatValue();
	return CCRotateTo::create(duration, angle);
}

CCAction* ParserRotateBy::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	float angle = dict->valueForKey("Angle")->floatValue();
	return CCRotateTo::create(duration, angle);
}

CCAction* ParserSkewBy::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	float sx = dict->valueForKey("SX")->floatValue();
	float sy = dict->valueForKey("SY")->floatValue();
	return CCSkewBy::create(duration, sx, sy);
}

CCAction* ParserSkewTo::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	float sx = dict->valueForKey("SX")->floatValue();
	float sy = dict->valueForKey("SY")->floatValue();
	return CCSkewTo::create(duration, sx, sy);
}

CCAction* ParserBlink::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	unsigned int times = dict->valueForKey("Times")->uintValue();
	return CCBlink::create(duration, times);
}

CCAction* ParserSequence::parseAction(cocos2d::CCDictionary *dict)
{
	CCArray* actionDefs = (CCArray*)dict->objectForKey("Actions");
	CCArray* actions = CCArray::createWithCapacity(actionDefs->count());
	CCObject* obj = NULL;
	CCARRAY_FOREACH(actionDefs, obj)
	{
		CCDictionary* defDict = (CCDictionary*)obj;
		CCAction* action = ActionContext::getContext()->getAction(defDict);
		actions->addObject(action);
	}
	CCSequence* sequence = CCSequence::create(actions);
	return sequence;
}

CCAction* ParserRepeat::parseAction(cocos2d::CCDictionary *dict)
{
	unsigned int times = dict->valueForKey("Times")->uintValue();
	CCDictionary* actionDef = (CCDictionary*)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	CCRepeat* repeat = CCRepeat::create((CCFiniteTimeAction *)action, times);
	return repeat;
}

CCAction* ParserSpawn::parseAction(cocos2d::CCDictionary *dict)
{
	CCArray* actionDefs = (CCArray*)dict->objectForKey("Actions");
	CCArray* actions = CCArray::createWithCapacity(actionDefs->count());
	CCObject* obj = NULL;
	CCARRAY_FOREACH(actionDefs, obj)
	{
		CCDictionary* defDict = (CCDictionary*)obj;
		CCAction* action = ActionContext::getContext()->getAction(defDict);
		actions->addObject(action);
	}
	CCSpawn* spawn = CCSpawn::create(actions);
	return spawn;
}

CCAction* ParserReverseTime::parseAction(cocos2d::CCDictionary *dict)
{
	CCDictionary* actionDef = (CCDictionary*)dict->objectForKey("Action");
	CCAction* action = ActionContext::getContext()->getAction(actionDef);
	return  CCReverseTime::create((CCFiniteTimeAction *)action);
}

CCAction* ParserActionTween::parseAction(cocos2d::CCDictionary *dict)
{
	float duration = dict->valueForKey("Duration")->floatValue();
	const CCString* key = dict->valueForKey("Key");
	float from = dict->valueForKey("From")->floatValue();
	float to = dict->valueForKey("To")->floatValue();
	return CCActionTween::create(duration, key->getCString(), from, to);
}

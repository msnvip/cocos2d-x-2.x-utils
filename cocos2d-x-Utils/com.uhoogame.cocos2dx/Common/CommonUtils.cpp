//
//  CommonUtils.cpp
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-12.
//
//

#include <stdio.h>
#include <sstream>
#include <math.h>

#include "CommonUtils.h"

using namespace std;

float PTM_RATIO = 32;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 一些常用功能
////////////////////////////////////////////////////////////////////////////////////////////////////

Price createPriceWithDictionary(CCDictionary * dict)
{
	Price::CoinType coinType;
	uint32 value;
	
	CCString * strType = (CCString *)dict->objectForKey(PRICE_TYPE_KEY);
	if (strType->compare(PRICE_COIN) == 0)
	{
		coinType = Price::kCoinType_Coin;
	}
	else if (strType->compare(PRICE_GEM) == 0)
	{
		coinType = Price::kCoinType_Gem;
	}
	else
	{
		coinType = Price::kCoinType_Unknown;
	}
	
	CCString * strNumber = (CCString *)dict->objectForKey(PRICE_VALUE_KEY);
	value = strNumber->uintValue();
	return Price(coinType, value);
}

float32 floatValueFromDictionary(CCDictionary * dict, const string & key)
{
	CCString * result = dynamic_cast<CCString *>(dict->objectForKey(key));
	if (result != NULL)
	{
		return result->floatValue();
	}
	else
	{
		return 0.0f;
	}
}

int32 intValueFromDictionary(CCDictionary * dict, const string & key)
{
	CCString * result = dynamic_cast<CCString *>(dict->objectForKey(key));
	if (result != NULL)
	{
		return result->intValue();
	}
	else
	{
		return 0;
	}
}

uint32 uintValueFromDictionary(CCDictionary * dict, const string & key)
{
	CCString * result = dynamic_cast<CCString *>(dict->objectForKey(key));
	if (result != NULL)
	{
		return result->uintValue();
	}
	else
	{
		return 0;
	}
}

bool boolValueFromDictionary(CCDictionary * dict, const string & key)
{
	CCString * result = dynamic_cast<CCString *>(dict->objectForKey(key));
	if (result != NULL)
	{
		return result->boolValue();
	}
	else
	{
		return false;
	}
}

string stringValueFromDictionary(CCDictionary * dict, const string & key)
{
	CCString * result = dynamic_cast<CCString *>(dict->objectForKey(key));
	if (result != NULL)
	{
		return string(result->getCString());
	}
	else
	{
		return string();
	}
}

void tintAllSprite(CCNode * root, const ccColor4B & color)
{
	CCArray * children = root->getChildren();
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(children, pObj)
	{
		CCNode * child = dynamic_cast<CCNode *>(pObj);
		tintAllSprite(child, color);
	}
	
	if (dynamic_cast<CCRGBAProtocol *>(root) != NULL)
	{
		CCRGBAProtocol * p = dynamic_cast<CCRGBAProtocol *>(root);
		p->setColor(ccc3(color.r, color.g, color.b));
		p->setOpacity(color.a);
	}
}

void pauseAll(cocos2d::CCNode* node)
{
	CCObject* obj = NULL;
	CCArray* children = node->getChildren();
	CCARRAY_FOREACH(children, obj)
	{
		CCNode* child = (CCNode*)obj;
		pauseAll(child);
	}
	
	CCDirector::sharedDirector()->getActionManager()->pauseTarget(node);
	CCDirector::sharedDirector()->getScheduler()->pauseTarget(node);
}

void resumeAll(cocos2d::CCNode* node)
{
	CCObject* obj = NULL;
	CCArray* children = node->getChildren();
	CCARRAY_FOREACH(children, obj)
	{
		CCNode* child = (CCNode*)obj;
		resumeAll(child);
	}
	
	CCDirector::sharedDirector()->getActionManager()->resumeTarget(node);
	CCDirector::sharedDirector()->getScheduler()->resumeTarget(node);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// 几何/数学
////////////////////////////////////////////////////////////////////////////////////////////////////

float convertRadianToDegree(float radian)
{
	return radian / M_PI * 180.0f;
}

float convertDegreeToRadian(float degree)
{
	return degree / 180.0f * M_PI;
}

#if (ENABLED_BOX2D)

CCPoint pointFromVec(const b2Vec2 & vec)
{
	return ccp(vec.x, vec.y);
}

b2Vec2 vecFromPoint(const CCPoint & point)
{
	return b2Vec2(point.x, point.y);
}

CCPoint pointFromVec_meter(const b2Vec2 & vec)
{
	return ccp(vec.x * PTM_RATIO, vec.y * PTM_RATIO);
}

b2Vec2 vecFromPoint_meter(const CCPoint & point)
{
	return b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO);
}

#endif // ENABLED_BOX2D

float pointFromMeter(float meterUnit)
{
	return meterUnit * PTM_RATIO;
}

float meterFromPoint(float pointUnit)
{
	return pointUnit / PTM_RATIO;
}

bool CCRectContainsRect(cocos2d::CCRect& rect1, cocos2d::CCRect& rect2)
{
	if ((rect2.origin.x - rect1.origin.x <= rect1.size.width - rect2.size.width)
		&&rect2.origin.x >= rect1.origin.x
		&&rect2.origin.y >= rect1.origin.y
		&& (rect2.origin.y - rect1.origin.y <  rect1.size.height - rect2.size.height))
	{
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// 字符串处理
////////////////////////////////////////////////////////////////////////////////////////////////////

string int32ToString(int32 value)
{
	char str[32] = {0};
	sprintf(str, "%d", value);
	return string(str);
}

string uint32ToString(uint32 value)
{
	char str[32] = {0};
	sprintf(str, "%u", value);
	return string(str);
}

string uint64ToString(uint64 value)
{
	char str[32] = {0};
	sprintf(str, "%llu", value);
	return string(str);
}

string float32ToString(float32 value)
{
	char str[32] = {0};
	sprintf(str, "%f", value);
	return string(str);
}

int32 int32FromString(const std::string & value)
{
	istringstream iss(value);
	int32 number;
	iss >> number;
	return number;
}

uint32 uint32FromString(const std::string & value)
{
	istringstream iss(value);
	uint32 number;
	iss >> number;
	return number;
}

uint64 uint64FromString(const std::string & value)
{
	istringstream iss(value);
	uint64 number;
	iss >> number;
	return number;
}

float32 float32FromString(const std::string & value)
{
	istringstream iss(value);
	float32 number;
	iss >> number;
	return number;
}

void slitStringBySeperator(const string & origin, vector<string> & others, const string & seperator)
{
	size_t beg = 0;
	size_t end = 0;
	size_t originLen = origin.length();
	size_t seperatorLen = seperator.length();
	
	while (beg < originLen)
	{
		end = origin.find(seperator, beg);
		
		// 如果起始位置与终止位置在同一个地方, 那么将不记录字符串, 因为不存在截断的字符串.
		if (beg != end)
		{
			if (end == string::npos)
			{
				// 如果 (beg == 0 && end == string::npos), 那么表示的是没有搜索到分割符, 那么将不分离各个字符串.
				// 而下面的代码表示的是, 从当前位置切割字符串, 直到字符串末尾.
				if (beg != 0)
				{
					others.push_back(origin.substr(beg, end));
				}
				break;
			}
			else
			{
				others.push_back(origin.substr(beg, end - beg));
			}
		}
		
		beg = end + seperatorLen;
	}
}

string trimCharacterFromLast(const std::string & origin, char chTrim)
{
	for (size_t i = origin.length() - 1; i < 0xffffffff; --i)
	{
		if (origin[i] != chTrim)
		{
			return origin.substr(0, i + 1);
		}
	}
	
	static string s_reuslt("");
	return s_reuslt;
}

string trimStringWithCharacterFromHead(const std::string& origin, char chSign)
{
	size_t pos = origin.rfind(chSign);
	return origin.substr(0,pos);
}

string trimStringWithCharacterFromLast(const std::string& origin, char chSign)
{
	size_t pos = origin.rfind(chSign);
	return origin.substr(pos+1);
}

string stringByDeletingPathExtension(const std::string & origin)
{
	size_t pos = origin.rfind(".");
	return origin.substr(0, pos);
}

string stringByAppendingPathExtension(const std::string & origin, const std::string & extension)
{
	return origin + "." + extension;
}


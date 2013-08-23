#ifndef __AndroidaBoom_YHUIUnitComboBackground__
#define __AndroidaBoom_YHUIUnitComboBackground__

#include "cocos2d.h"

/*
 *单元图形组成背景生成
 *@author wangtiwei
 */
class YHUIUnitComboBackground :public cocos2d::CCSprite
{
public:
	YHUIUnitComboBackground(void);
	virtual ~YHUIUnitComboBackground(void);
	
	bool initWithUnitFrameNameAndSize(const char* frameName, cocos2d::CCSize size);
	
	static YHUIUnitComboBackground* createWithUnitFrameNameAndSize(const char* frameName, cocos2d::CCSize size);
};

#endif /*__AndroidaBoom_YHUIUnitComboBackground__*/

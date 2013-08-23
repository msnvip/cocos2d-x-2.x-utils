//
//  testAEPlugin.h
//  cocos2d-x-Utils
//
//  Created by mac on 13-7-15.
//
//

#ifndef __cocos2d_x_Utils__testAEPlugin__
#define __cocos2d_x_Utils__testAEPlugin__

#include "cocos2d.h"
USING_NS_CC;

class TestAEPlugin : CCLayer
{
public:
	static CCScene* scene();
	
	bool init();
	
	CREATE_FUNC(TestAEPlugin);
};

#endif /* defined(__cocos2d_x_Utils__testAEPlugin__) */

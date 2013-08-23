//
//  ActionParseBase.h
//  cocos2d-x-Utils
//
//  Created by mac on 13-6-18.
//
//

#ifndef __cocos2d_x_Utils__ActionParseBase__
#define __cocos2d_x_Utils__ActionParseBase__

#include <iostream>
#include "cocos2d.h"
#include "ActionContext.h"

using namespace cocos2d;

class ActionParseBase
{
public:
    
    virtual CCAction* parseAction(CCDictionary* dict) = 0;
	
	virtual ~ActionParseBase(){}
    
};

#endif /* defined(__cocos2d_x_Utils__ActionParseBase__) */

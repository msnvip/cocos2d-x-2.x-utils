//
//  ActionContext.h
//  cocos2d-x-Utils
//
//  Created by mac on 13-6-17.
//
//

#ifndef __cocos2d_x_Utils__ActionContext__
#define __cocos2d_x_Utils__ActionContext__

#include <string>
#include "cocos2d.h"

/**
 * CCAction 解析的上下文, 负责决定使用什么类型的解析对象
 * @author wangtiwei
 */
class ActionParseBase;
class ActionContext : public cocos2d::CCObject
{
public:
	
    static ActionContext* getContext();
	
	/// 必须初始化,注册
	void initialize();
	
    /// 根据类名得到CCAction 对象
	cocos2d::CCAction *getAction(const std::string& className, cocos2d::CCDictionary* dict);
	
	/// 根据字典得到CCAction 对象
	cocos2d::CCAction *getAction(cocos2d::CCDictionary* dict);
	
};

#endif /* defined(__cocos2d_x_Utils__ActionContext__) */

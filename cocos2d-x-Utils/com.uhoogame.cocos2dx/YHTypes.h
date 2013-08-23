//
//  YHTypes.h
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-12.
//
//

#ifndef AndroidaBooM_YHTypes_h
#define AndroidaBooM_YHTypes_h

#define ENABLED_BOX2D 1

#include "cocos2d.h"
#include "cocos-ext.h"

#if (ENABLED_BOX2D)
#include "Box2D.h"
#endif // ENABLED_BOX2D

class YHEvent;
class YHEventDispatcher;

#if (!ENABLED_BOX2D)

typedef char int8;
typedef unsigned char uint8;
typedef int int32;
typedef unsigned int uint32;
typedef short int16;
typedef unsigned short uint16;
typedef float float32;
typedef double float64;

#endif // ENABLED_BOX2D

typedef long long int64;
typedef unsigned long long uint64;

/**
 * 接口继承此类, 以得到实现此接口的 CCObject 对象, 非 CCObject 对象实现时 返回 NULL
 * 起的作用是, 为的是传入的接口也能 retain/release
 */
class ICCObject
{
public:

	/// 得到实现此接口的父类
	virtual cocos2d::CCObject * getCCObject() = 0;

};

/**
 * 一切对象的基类
 * @author Zhenyu Yao
 */
class YHObject : public cocos2d::CCObject
{
public:
	YHObject() {};
	virtual ~YHObject() {};
};

typedef void (cocos2d::CCObject::*ListenerSelector)(YHEvent * obj);

#define LISTENER_SELECTOR(__SEL__) (ListenerSelector)(&__SEL__)
#define RunListenerSelector(__Target__, __Selector__, __Object__) (__Target__->*__Selector__)(__Object__)
#define DIRECT_DISPATCH_EVENT(__TYPE__) YHEvent evt = YHEvent(__TYPE__); dispatchEvent(&evt);
#define DEFAULT_DISPATCHER_DIRECT_DISPATCH_EVENT(__TYPE__) YHEvent evt = YHEvent(__TYPE__); YHDefaultEventDispatcher::defaultEventDispatcher()->dispatchEvent(&evt);

#define SET_MEMORY_ZERO(__TARGET__) memset((void *)__TARGET__, 0, sizeof(__TARGET__))
#define DELETE_MAP_VALUE_MEMORY(__KEY_TYPE__, __VALUE_TYPE__, __VAR__) 															\
		map<__KEY_TYPE__, __VALUE_TYPE__>::iterator beg##__VAR__ = __VAR__.begin();												\
		map<__KEY_TYPE__, __VALUE_TYPE__>::iterator end##__VAR__ = __VAR__.end();												\
		while (beg##__VAR__ != end##__VAR__) { delete beg##__VAR__->second; beg##__VAR__->second = NULL; ++beg##__VAR__; }

#define ASSIGN_VECTOR_BEGIN_ITERATOR(__TYPE__, __VAR_NAME__, __VAR__) 											\
		vector<__TYPE__>::iterator __VAR_NAME__ = __VAR__.begin();
#define ASSIGN_VECTOR_END_ITERATOR(__TYPE__, __VAR_NAME__, __VAR__)												\
		vector<__TYPE__>::iterator __VAR_NAME__ = __VAR__.end();
#define ASSIGN_MAP_BEGIN_ITERATOR(__TYPE__, __VALUE__, __VAR_NAME__, __VAR__)									\
		map<__TYPE__, __VALUE__>::iterator __VAR_NAME__ = __VAR__.begin();
#define ASSIGN_MAP_END_ITERATOR(__TYPE__, __VALUE__, __VAR_NAME__, __VAR__)										\
		map<__TYPE__, __VALUE__>::iterator __VAR_NAME__ = __VAR__.end();

#endif



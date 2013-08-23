//
//  YHSocketClient.h
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-13.
//
//

#ifndef __cocos2d_x_Utils__YHSocketClient__
#define __cocos2d_x_Utils__YHSocketClient__

#include <string>
#include "cocos2d.h"
#include "utils/YHNetMessageQueue.h"
#include "utils/YHSocketConnectManager.h"
#include "utils/YHSocketSendManager.h"
#include "utils/YHSocketRecvManager.h"
#include "buffer/YHGameLogicPackage.h"

/**
 * Socket 通信功能封装
 * @author Zhenyu Yao
 */
class YHSocketClient : public cocos2d::CCObject
{
	
public:
	
	YHSocketClient();
	virtual ~YHSocketClient();
	
	/**
	 * 设置 connect 之后的回调函数, 无论连接成功与否, 都会调用
	 * @param target 回调对象
	 * @param selector 回调对象的执行函数
	 */
	virtual void setConnectedCallBack(cocos2d::CCObject * target, cocos2d::SEL_CallFuncO selector);
	
	/**
	 * 设置断开连接之后的回调函数
	 * @param target 回调对象
	 * @param selector 回调对象的执行函数
	 */
	virtual void setCloseCallBack(cocos2d::CCObject * target, cocos2d::SEL_CallFuncO selector);
	
	/**
	 * 连接远程终端
	 * @param address 远程终端的 url 地址
	 * @param port 远程终端的端口号
	 * @param asyn 是否使用异步连接, true 使用, false 不使用
	 */
	virtual void connect(const std::string & address, int port, bool asyn = false, bool ipv6 = false);
	
	/// 关闭连接
	virtual void close();
	
	/**
	 * 发送数据, 直接发送数据, 不做装包处理.
	 * @param bytes 发送的数据流
	 */
	virtual void send(YHByteArray * bytes);
	
	/**
	 * 接收数据, 已经经过拆包, 供游戏直接使用的数据. 返回的 YHByteArray 对象在使用完之后必须手动调用 release() 方法.
	 * @return 接收到的数据流
	 */
	virtual YHByteArray * recv();
	
	/// 远程终端的主机名, 无效返回空字符串
	const std::string getRemoteName();
	
	/// 本地终端的主机名, 无效返回空字符串
	const std::string getLocalName();
	
	/// 远程终端的端口号, 无效返回 -1
	int getRemotePort();
	
	/// 本地终端的端口号, 无效返回 -1
	int getLocalPort();
	
	/// 是否连接上远程终端
	bool isConnected();
	
private:
	
	/// YHSocketConnectManager 连接后的回调函数
	void onConnectedHandler(cocos2d::CCObject * sender);
	
	/// YHSocketConnectManager 断开连接后的回调函数
	void onClosedHandler(cocos2d::CCObject * sender);
	
private:
	
	YHSocketConnectManager * m_connectManager;
	YHSocketSendManager * m_sendManager;
	YHSocketRecvManager * m_recvManager;
	
	cocos2d::CCObject * m_openTarget;
	cocos2d::SEL_CallFuncO m_openSelector;
	
	cocos2d::CCObject * m_closeTarget;
	cocos2d::SEL_CallFuncO m_closeSelector;
};

#endif /* defined(__cocos2d_x_Utils__YHSocketClient__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file



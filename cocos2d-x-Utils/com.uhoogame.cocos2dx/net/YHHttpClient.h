//
//  YHHttpClient.h
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-15.
//
//

#ifndef __cocos2d_x_Utils__YHHttpClient__
#define __cocos2d_x_Utils__YHHttpClient__

#include "YHTypes.h"
#include "net/buffer/YHByteArray.h"
#include "net/buffer/YHGameLogicPackage.h"

/**
 * 对 CCHttpClient 的封装, 将接收到的数据解析为 YHGameLogicData, 放入队列中.
 * @author Zhenyu Yao
 */
class YHHttpClient : public cocos2d::CCObject
{
public:
	
	YHHttpClient();
	~YHHttpClient();
	
	/**
	 * 发送数据
	 * @param data 发送的数据
	 * @param len 发送数据的长度
	 * @param type 发送 http  协议的类型
	 */
	void sendData(YHByteArray * bytes,
				  cocos2d::extension::CCHttpRequest::HttpRequestType type = cocos2d::extension::CCHttpRequest::kHttpGet);
	
	/**
	 * 从接收数据队列中, 得到接收的数据. 在使用完 YHByteArray 对象之后, 必须手动调用 YHByteArray 的 release 操作, 以释放 YHByteArray 对象.
	 * @return 从队列中获得的数据
	 */
	YHByteArray * recvData();
	
	/// getter/setter url
	void setURL(const std::string & url)
	{
		m_url = url;
	}
	
	const std::string & getURL() const
	{
		return m_url;
	}
	
	/// getter/setter connect timeout
	void setTimeoutForConnect(int value)
	{
		m_httpClient->setTimeoutForConnect(value);
	}
	
	int getTimeoutForConnect()
	{
		return m_httpClient->getTimeoutForConnect();
	}
	
	/// getter/setter download timeout
	void setTimeoutForRead(int value)
	{
		m_httpClient->setTimeoutForRead(value);
	}
	
	int getTimeoutForRead()
	{
		return m_httpClient->getTimeoutForRead();
	}
	
private:
	
	/// 响应请求的回调函数
	void onResponseCallBack(cocos2d::extension::CCHttpClient * client,
							cocos2d::extension::CCHttpResponse * response);
	
private:
	
	std::string m_url;
	cocos2d::CCArray * m_queue;
	cocos2d::extension::CCHttpClient * m_httpClient;
};

#endif /* defined(__cocos2d_x_Utils__YHHttpClient__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file



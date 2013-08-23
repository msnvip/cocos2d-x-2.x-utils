//
//  ResourceManager.h
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-23.
//
//

#ifndef __AndroidaBooM__ResourceManager__
#define __AndroidaBooM__ResourceManager__

#include <set>
#include <string>

#include "Common/YHEventDispatcher.h"

/**
 * SpriteFrames 资源管理器
 * @author Zhenyu Yao
 */
class SpriteFramesResourceManager : public YHEventDispatcher
{
public:
	/// 资源装载完成事件
	static const std::string Event_LoadCompleted;
	
public:
	SpriteFramesResourceManager() {}
	~SpriteFramesResourceManager() {}
	
	/// 添加资源
	void								addResource(const std::string & resourceName);
	
	/// 批量添加资源
	void								addResources(const std::set<std::string> & resourceNames);
	
	/// 移除资源
	void								removeResource(const std::string & resourceName);
	
	/// 批量移除资源
	void								removeResources(const std::set<std::string> & resourceNames);
	
	/// 装载资源, 需要循环调用该方法以实现把所有的资源装载完成
	void								loading();
	
	/// 判断资源是否装载完
	bool								complete() const { return m_waittingLoadResources.size() == 0; }
	
	/// 卸载所有的资源
	void								unload();
	
private:

	std::set<std::string>				m_waittingLoadResources;
	std::set<std::string>				m_loadedResources;
};

#endif /* defined(__AndroidaBooM__ResourceManager__) */

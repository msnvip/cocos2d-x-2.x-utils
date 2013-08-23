
#ifndef __CCSpecialSprite_H__
#define __CCSpecialSprite_H__

#include "cocos2d.h"
#include "Common/CommonUtils.h"

using namespace cocos2d;

class AnimatorModuleData;
/**
 * 特殊的 Sprite 类, 为的是解决能在 CCSpriteBatchNode 中使用, 能够设置 contentSize, 但是又不贴图的需求.
 * @author Zhenyu Yao
 */
class CCSpecialSprite : public CCSprite
{
public:
	
	CCSPRITE_CREATE_FUNCTIONS(CCSpecialSprite);
	
	bool init1(CCDictionary* moduleDict);
	bool init2(AnimatorModuleData* moduleData);
	
	static CCSpecialSprite* create(CCDictionary* moduleDict);
	static CCSpecialSprite* create(AnimatorModuleData* moduleData);
	
public: // Override Functions
	
	/// 不绘制任何图形, 为的只是当容器能够在 CCSpriteBatchNode 中使用
	virtual void				draw();
	
	/// 设置子节点的颜色
	virtual void				setColor(const ccColor3B & color3);
	
	/// 设置子节点的透明度
	virtual void				setOpacity(GLubyte opacity);
	
	/// 添加进容器的时候负责给子节点着色和设置透明度
	virtual void				addChild(CCNode *pNode);
	virtual void				addChild(CCNode *pNode, int zOrder);
	virtual void				addChild(CCNode *pChild, int zOrder, int tag);
	
};

#endif // __CCSpecialSprite_H__



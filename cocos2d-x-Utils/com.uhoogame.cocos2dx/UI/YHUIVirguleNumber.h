#ifndef YHUIVirguleNumber_h__
#define YHUIVirguleNumber_h__

#include "cocos2d.h"

class YHUISpriteNumber;

/**
 * 中间有斜线分割数字的数字贴图
 * @author Zhenyu Yao
 */
class YHUIVirguleNumber : public cocos2d::CCSprite
{
public:
	YHUIVirguleNumber(void);
	virtual ~YHUIVirguleNumber(void);
	
	void setVirguleInterval(float val);
	float getVirguleInterval(){return m_virguleInterval;}
	
	float contentWidth();
	
	bool init(const std::string & fontName, cocos2d::CCSize fontSize, float fontInterval, const std::string & virguleName);
	
	static YHUIVirguleNumber * create(const std::string & fontName, cocos2d::CCSize fontSize, float fontInterval, const std::string & virguleName)
	{
		YHUIVirguleNumber * instance = new YHUIVirguleNumber();
		if (instance != NULL && instance->init(fontName, fontSize, fontInterval, virguleName))
		{
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return NULL;
	}
	
	/**
	 * 设置分割号左边的数字
	 * @param leftNumber 左边的数字
	 * @author Zhenyu Yao
	 */
	void setLeftNumber(int leftNumber);
	
	/**
	 * 设置分割号右边的数字
	 * @param rightNumber 右边的数字
	 * @author Zhenyu Yao
	 */
	void setRightNumber(int rightNumber);
	
	/**
	 * 设置左边数字的颜色
	 * @param color 填充颜色
	 * @author Zhenyu Yao
	 */
	void setLeftNumberColor(cocos2d::ccColor3B color);
	
	/**
	 * 设置右边数字的颜色
	 * @param color 填充颜色
	 * @author Zhenyu Yao
	 */
	void setRightNumberColor(cocos2d::ccColor3B color);
	
	
private:
	
	/**
	 * 重新排列
	 * @author Zhenyu Yao
	 */
	void realign();
	
private:
	YHUISpriteNumber * m_leftNumber;
	YHUISpriteNumber * m_rightNumber;
	cocos2d::CCSprite * m_virgule;
	
	/// 数字的长度, 以点为单位
	float m_contentWidth;
	
	/// 分号与数字间的间隔
	float m_virguleInterval;
	
	cocos2d::CCSize m_fontSize;
};
#endif // YHUIVirguleNumber_h__


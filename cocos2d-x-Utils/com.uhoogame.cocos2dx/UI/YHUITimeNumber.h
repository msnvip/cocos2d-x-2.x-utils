#ifndef YHUITimeNumber_h__
#define YHUITimeNumber_h__
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class YHUISpriteNumber;

/**
 * 时间格式的数字显示
 * @author Zhenyu Yao
 */
class YHUITimeNumber : public cocos2d::CCSprite
{
public:
	YHUITimeNumber(void);
	virtual ~YHUITimeNumber(void);
	
	float contentWidth();
	
	/// 以秒数设置显示时间
	void setTimeWithSecond(uint32 second);
	
	/// 以毫秒数显示时间
	void setTimeWithMilliSecond(uint32 milliSecond);
	
	/**
	 * 初始化
	 * @param hourSeparatorName 小时的分隔符
	 * @param hourInterval 与小时分隔符之间的间隔
	 * @param minSeparatorName 分钟的分隔符
	 * @param minInterval 与分钟分隔符之间的间隔
	 * @param secSeparatorName 秒的分隔符
	 * @param secInterval 与秒分隔符之间的间隔
	 * @param fontName 数字的显示文件
	 * @param fontSize 数字的大小
	 * @param fontInterval 数字之间的间距
	 * @author Zhenyu Yao
	 */
	bool init(const std::string& hourSeparatorName, float hourInterval,
			  const std::string& minSeparatorName, float minInterval,
			  const std::string& secSeparatorName, float secInterval,
			  const std::string& fontName, const cocos2d::CCSize& fontSize,
			  float fontInterval
			  );
	
	/**
	 * 生成 TimeNumber 对象
	 * @param hourSeparatorName 小时的分隔符
	 * @param hourInterval 与小时分隔符之间的间隔
	 * @param minSeparatorName 分钟的分隔符
	 * @param minInterval 与分钟分隔符之间的间隔
	 * @param secSeparatorName 秒的分隔符
	 * @param secInterval 与秒分隔符之间的间隔
	 * @param fontName 数字的显示文件
	 * @param fontSize 数字的大小
	 * @param fontInterval 数字之间的间距
	 * @return TimeNumber 对象
	 * @author Zhenyu Yao
	 */
	static YHUITimeNumber* timeNumber(const std::string& hourSeparatorName, float hourInterval,
									  const std::string& minSeparatorName, float minInterval,
									  const std::string& secSeparatorName, float secInterval,
									  const std::string& fontName, const cocos2d::CCSize& fontSize,
									  float fontInterval
									  );
	
private:
	/**
	 * 调整小时数字和小时分隔符的位置
	 * @author Zhenyu Yao
	 */
	void adjustHourPosition();
	
	/**
	 * 调整分钟数字和分钟分隔符的位置
	 * @author Zhenyu Yao
	 */
	void adjustMinPosition();
	
	/**
	 * 调整秒数字和秒分隔符的位置
	 * @author Zhenyu Yao
	 */
	void adjustSecPosition();
	
private:
	cocos2d::CCSprite* m_iconHour;
	cocos2d::CCSprite* m_iconMin;
	cocos2d::CCSprite* m_iconSec;
	
	float m_hourSeparatorInterval;
	float m_minSeparatorInterval;
	float m_secSeparatorInterval;
	
	YHUISpriteNumber* m_hourNumber;
	YHUISpriteNumber* m_minNumber;
	YHUISpriteNumber* m_secNumber;
	
	float m_contentWidth;
};
#endif // YHUITimeNumber_h__


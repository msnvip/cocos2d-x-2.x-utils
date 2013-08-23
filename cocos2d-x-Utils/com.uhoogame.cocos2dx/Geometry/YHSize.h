//
//  YHSize.h
//  GeometryLibrary
//
//  Created by Zhenyu Yao on 13-2-27.
//  Copyright (c) 2013年 Zhenyu Yao. All rights reserved.
//

#ifndef __GeometryLibrary__YHSize__
#define __GeometryLibrary__YHSize__

/**
 * Size
 * @author Zhenyu Yao
 */
class YHSize
{

public:
	
	YHSize() { m_width = 0.0f; m_height = 0.0f; }
	YHSize(float width, float height) { m_width = width; m_height = height; }
	YHSize(const YHSize & size) { m_width = size.getWidth(); m_height = size.getHeight(); }
	
	/**
	 * 生成当前对象的副本
	 * @return YHSize 对象
	 * @author Zhenyu Yao
	 */
	YHSize				clone() const { return YHSize(m_width, m_height); }
	
	/**
	 * 判断 w, h 是否都为 0
	 * @return 都为 0 返回 true, 否则返回 false
	 * @author Zhenyu Yao
	 */
	bool				isEmpty() const { return m_width == 0 && m_height == 0; }
	
	/* 设置/获取长度和宽度 */
	
	float				getWidth() const { return m_width; }
	float				getHeight() const { return m_height; }
	void				setWidth(float width) { m_width = width; }
	void				setHeight(float height) { m_height = height; }
	
	/* 运算符重载, 单个数值 */
	
	YHSize operator + (const float value) const
	{
		return YHSize(m_width + value, m_height + value);
	}
	
	YHSize operator - (const float value) const
	{
		return YHSize(m_width - value, m_height - value);
	}
	
	YHSize operator * (const float value) const
	{
		return YHSize(m_width * value, m_height * value);
	}
	
	YHSize operator / (const float value) const
	{
		return YHSize(m_width / value, m_height / value);
	}
	
	YHSize & operator += (const float value)
	{
		m_width += value, m_height += value;
		return *this;
	}
	
	YHSize & operator -= (const float value)
	{
		m_width -= value, m_height -= value;
		return *this;
	}
	
	YHSize & operator *= (const float value)
	{
		m_width *= value, m_height *= value;
		return *this;
	}
	
	YHSize & operator /= (const float value)
	{
		m_width /= value, m_height /= value;
		return *this;
	}
	
	/* 运算符重载, 逻辑判断 */
	
	bool operator == (const YHSize & s2) const
	{
		return m_width == s2.getWidth() && m_height == s2.getHeight();
	}
	
	bool operator != (const YHSize & s2) const
	{
		return !(*this == s2);
	}
	
	/* 运算符重载, YHSize */
	
	YHSize operator + (const YHSize & s2) const
	{
		return YHSize(m_width + s2.getWidth(), m_height + s2.getHeight());
	}
	
	YHSize operator - (const YHSize & s2) const
	{
		return YHSize(m_width - s2.getWidth(), m_height - s2.getHeight());
	}
	
	YHSize operator * (const YHSize & s2) const
	{
		return YHSize(m_width * s2.getWidth(), m_height * s2.getHeight());
	}
	
	YHSize operator / (const YHSize & s2) const
	{
		return YHSize(m_width / s2.getWidth(), m_height / s2.getHeight());
	}
	
	YHSize & operator += (const YHSize & s2)
	{
		m_width += s2.getWidth(), m_height += s2.getHeight();
		return *this;
	}
	
	YHSize & operator -= (const YHSize & s2)
	{
		m_width -= s2.getWidth(), m_height -= s2.getHeight();
		return *this;
	}
	
	YHSize & operator *= (const YHSize & s2)
	{
		m_width *= s2.getWidth(), m_height *= s2.getHeight();
		return *this;
	}
	
	YHSize & operator /= (const YHSize & s2)
	{
		m_width /= s2.getWidth(), m_height /= s2.getHeight();
		return *this;
	}
	
private:
	
	float				m_width;
	float				m_height;
	
};


#endif /* defined(__GeometryLibrary__YHSize__) */

////////////////////////////////////////////////////////////////////////////////////////////////////
// end file



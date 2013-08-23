//
//  YHRect.h
//  GeometryLibrary
//
//  Created by Zhenyu Yao on 13-2-27.
//  Copyright (c) 2013年 Zhenyu Yao. All rights reserved.
//

#ifndef __GeometryLibrary__YHRect__
#define __GeometryLibrary__YHRect__

#include "YHVector2.h"
#include "YHSize.h"

/**
 * Rectangle
 * @author Zhenyu Yao
 */
class YHRect
{
	
public:
	
	/* 构造函数 */
	
	YHRect() {}
	YHRect(float x, float y, float width, float height) { m_position = YHVector2(x, y); m_size = YHSize(width, height); }
	YHRect(const YHVector2 & v, const YHSize & s) { m_position = v; m_size = s; }
	YHRect(const YHRect & rect) { m_position = rect.m_position; m_size = rect.m_size; }
	
	/* 设置/获得 位置, 大小 参数 */
	
	float				getX() const { return m_position.getX(); }
	float				getY() const { return m_position.getY(); }
	float				getWidth() const { return m_size.getWidth(); }
	float 				getHeight() const { return m_size.getHeight(); }
	YHVector2 			getPosition() const { return m_position; }
	YHVector2 &			getPosition() { return m_position; }
	YHSize				getSize() const { return m_size; }
	YHSize &			getSize() { return m_size; }
	
	void				setX(float x) { m_position.setX(x); }
	void				setY(float y) { m_position.setY(y); }
	void				setWidth(float width) { m_size.setWidth(width); }
	void				setHeight(float height) { m_size.setHeight(height); }
	void				setPosition(const YHVector2 & p) { m_position = p; }
	void 				setSize(const YHSize & s) { m_size = s; }
	
	/**
	 * 判断是否包含指定的 Point, 与边相切不算包含在内
	 * @param point 判断的点
	 * @return 在 Rect 中返回 YES, 否则返回 NO
	 * @author Zhenyu Yao
	 */
	bool				containsPoint(const YHVector2 & point) const;
	
	/**
	 * 判断是否包含指定的 Rect, 与边相切不算包含在内
	 * @param rect 被包含的 YHRect 对象
	 * @return 包含返回 YES, 否则返回 NO
	 * @author Zhenyu Yao
	 */
	bool				containsRect(const YHRect & rect) const;
	
	/**
	 * 判断两个 Rect 是否相交, 与边相切不算相交
	 * @param rect 判断与之相交的 YHRect 对象
	 * @return 相交返回 YES, 否则返回 NO
	 * @author Zhenyu Yao
	 */
	bool				intersectsRect(const YHRect & rect) const;
	
	/**
	 * 如果两个矩形相交, 那么获得相交的矩形
	 * @param rect 判断与之相交的 YHRect 对象
	 * @return 如果没有相交, 返回的 YHRect 对象的 x, y, w, h 值都为 0, 否则 YHRect 对象具有相应的值
	 * @author Zhenyu Yao
	 */
	YHRect				getIntersectsRect(const YHRect & rect) const;
	
	/**
	 * 生成 YHRect 对象的副本
	 * @return YHRect 对象
	 * @author Zhenyu Yao
	 */
	YHRect				clone() const { return YHRect(m_position, m_size); }
	
	/**
	 * 判断是否 x, y, w, h 的值都为 0
	 * @return 都为 0 返回 true, 否则返回 false
	 * @author Zhenyu Yao
	 */
	bool				isEmpty() const { return m_position.isEmpty() && m_size.isEmpty(); }
	
	/* 运算符重载, 逻辑运算符 */
	
	bool operator == (const YHRect & rect) const
	{
		return m_position == rect.getPosition() && m_size == rect.getSize();
	}
	
	bool operator != (const YHRect & rect) const
	{
		return !(*this == rect);
	}
	
private:
	
	/**
	 * 找到两个相交矩形左下角点
	 * @param rect 相交的 YHRect 对象
	 * @return YHVector2 对象
	 * @author Zhenyu Yao
	 */
	YHVector2			findIntersectLeftBottom(const YHRect & rect) const;
	
	/**
	 * 找到两个相交矩形右上角点
	 * @param rect 相交的 YHRect 对象
	 * @return YHVector2 对象
	 * @author Zhenyu Yao
	 */
	YHVector2			findIntersectRightTop(const YHRect & rect) const;
	
	YHVector2			m_position;
	YHSize				m_size;
};

#endif /* defined(__GeometryLibrary__YHRect__) */

////////////////////////////////////////////////////////////////////////////////////////////////////
// end file



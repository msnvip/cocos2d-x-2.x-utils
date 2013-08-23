//
//  YHVector2.h
//  GeometryLibrary
//
//  Created by Zhenyu Yao on 13-2-26.
//
//

#ifndef __GeometryLibrary__YHVector2__
#define __GeometryLibrary__YHVector2__

/**
 * 2D 向量
 * @author Zhenyu Yao
 */
class YHVector2
{
public:
	
	/**
	 * 获得两个向量间的夹角弧度
	 * @param v1 向量 1
	 * @param v2 向量 2
	 * @return 夹角弧度
	 * @author Zhenyu Yao
	 */
	static float angleBetweenVectors(const YHVector2 & v1, const YHVector2 & v2);
	
public:
	
	YHVector2() {m_x = 0; m_y = 0;}
	YHVector2(float x, float y) {m_x = x; m_y = y;}
	YHVector2(const YHVector2 & v) {m_x = v.getX(); m_y = v.getY();}
	
	// 设置/获得向量的坐标
	float						getX() const { return m_x; }
	float						getY() const { return m_y; }
	void						setX(float x) { m_x = x; }
	void						setY(float y) { m_y = y; }
	
	// 复制当前的向量, 重新生成一个当前的副本
	YHVector2					clone() const { return YHVector2(m_x, m_y); }
	
	// 设置 x, y 的值都为 0
	YHVector2 &					zero() { m_x = 0.0f; m_y = 0.0f; return *this; }
	
	// 设置/获得向量的长度
	void						setLength(float length);
	float						getLength() const;
	float						getLengthSQ() const { return m_x * m_x + m_y * m_y; }
	
	// 设置/获得向量的角度
	void						setAngle(float angle);
	float						getAngle() const;
	
	/**
	 * 标准化
	 * @return 对自身引用的向量
	 * @author Zhenyu Yao
	 */
	YHVector2 &					normalize();
	
	/**
	 * 确认向量的长度不大于给定长度的值
	 * @param max 给定的长度
	 * @return 对自身引用的向量
	 * @author Zhenyu Yao
	 */
	YHVector2 &					truncate(float max);
	
	/**
	 * 向量的 x, y 值互换
	 * @return 对自身引用的向量
	 * @author Zhenyu Yao
	 */
	YHVector2 &					reverse();
	
	/**
	 * 判断向量是否是标准化的
	 * @return YES 标准化, NO 非标准化
	 * @author Zhenyu Yao
	 */
	bool						isNormalized() const { return getLength() == 1.0f; }
	
	/**
	 * 判断 x, y 值是否为 0
	 * @return 都为 0 返回 true, 否则返回 false
	 * @author Zhenyu Yao
	 */
	bool						isEmpty() const { return m_x == 0 && m_y == 0; }
	
	/**
	 * 向量的点乘
	 * @param v2 参加点乘的向量
	 * @return 点乘后的标量数值, 大于 0 方向基本相同, 小于 0 方向基本相反, 等于 0 正交
	 * @author Zhenyu Yao
	 */
	float						dotProd(const YHVector2 & v2) const { return m_x * v2.getX() + m_y * v2.getY(); }
	
	/**
	 * 将当前向量顺时针/逆时针, 90度旋转
	 * @param cw YES, 顺时针方向, NO, 逆时针方向
	 * @return 对自身引用的向量
	 * @author Zhenyu Yao
	 */
	YHVector2 &					perp(bool cw);
	
	/**
	 * 计算两个向量间的距离
	 * @param v2 另一个向量
	 * @return 向量间的距离
	 * @author Zhenyu Yao
	 */
	float						dist(const YHVector2 & v2) const;
	float						distSQ(const YHVector2 & v2) const;
	
	/* 操作符重载, 与数值的运算 */
	
	YHVector2 operator + (const float value) const
	{
		return YHVector2(m_x + value, m_y + value);
	}
	
	YHVector2 operator - (const float value) const
	{
		return YHVector2(m_x - value, m_y - value);
	}
	
	YHVector2 operator * (const float value) const
	{
		return YHVector2(m_x * value, m_y * value);
	}
	
	YHVector2 operator / (const float value) const
	{
		return YHVector2(m_x / value, m_y / value);
	}
	
	YHVector2 & operator += (const float value)
	{
		m_x += value, m_y += value;
		return *this;
	}
	
	YHVector2 & operator -= (const float value)
	{
		m_x -= value, m_y -= value;
		return *this;
	}
	
	YHVector2 & operator *= (const float value)
	{
		m_x *= value, m_y *= value;
		return *this;
	}
	
	YHVector2 & operator /= (const float value)
	{
		m_x /= value, m_y /= value;
		return *this;
	}
	
	/* 操作符重载, 逻辑判断 */
	
	bool operator == (const YHVector2 & v2) const
	{
		return m_x == v2.getX() && m_y == v2.getY();
	}
	
	bool operator != (const YHVector2 & v2) const
	{
		return !(*this == v2);
	}
	
	/* 操作符重载, 与 YHVector2 的运算 */
	
	YHVector2 operator + (const YHVector2 & v2) const
	{
		return YHVector2(m_x + v2.getX(), m_y + v2.getY());
	}
	
	YHVector2 operator - (const YHVector2 & v2) const
	{
		return YHVector2(m_x - v2.getX(), m_y - v2.getY());
	}
	
	YHVector2 operator * (const YHVector2 & v2) const
	{
		return YHVector2(m_x * v2.getX(), m_y * v2.getY());
	}
	
	YHVector2 operator / (const YHVector2 & v2) const
	{
		return YHVector2(m_x / v2.getX(), m_y / v2.getY());
	}
	
	YHVector2 operator += (const YHVector2 & v2)
	{
		m_x += v2.getX(), m_y += v2.getY();
		return *this;
	}
	
	YHVector2 operator -= (const YHVector2 & v2)
	{
		m_x -= v2.getX(), m_y -= v2.getY();
		return *this;
	}
	
	YHVector2 operator *= (const YHVector2 & v2)
	{
		m_x *= v2.getX(), m_y *= v2.getY();
		return *this;
	}
	
	YHVector2 operator /= (const YHVector2 & v2)
	{
		m_x /= v2.getX(), m_y /= v2.getY();
		return *this;
	}
	
private:
	float			m_x;
	float			m_y;
};

#endif /* defined(__GeometryLibrary__YHVector2__) */

////////////////////////////////////////////////////////////////////////////////////////////////////
// end file



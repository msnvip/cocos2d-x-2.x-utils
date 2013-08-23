//
//  YHVector2.cpp
//  GeometryLibrary
//
//  Created by Zhenyu Yao on 13-2-26.
//
//

#include "YHVector2.h"
#include <math.h>

/* 静态成员函数定义 */

float YHVector2::angleBetweenVectors(const YHVector2 & v1, const YHVector2 & v2)
{
	float angle = v1.clone().normalize().dotProd(v2.clone().normalize());
	return acosf(angle);
}

/* 类成员函数定义 */

void YHVector2::setLength(float length)
{
	float angle = getAngle();
	m_x = cosf(angle) * length;
	m_y = sinf(angle) * length;
}

float YHVector2::getLength() const
{
	return sqrtf(getLengthSQ());
}

void YHVector2::setAngle(float angle)
{
	float length = getLength();
	m_x = cosf(angle) * length;
	m_y = sinf(angle) * length;
}

float YHVector2::getAngle() const
{
	return atan2(m_y, m_x);
}

YHVector2 & YHVector2::normalize()
{
	float length = getLength();
	
	if (length == 0)
	{
		m_x = 1.0f;
		return *this;
	}
	
	m_x /= length;
	m_y /= length;
	return *this;
}

YHVector2 & YHVector2::truncate(float max)
{
	float length = getLength();
	if (length > max)
	{
		setLength(max);
	}
	
	return *this;
}

YHVector2 & YHVector2::reverse()
{
	float tmp = m_x;
	m_x = m_y;
	m_y = tmp;
	return *this;
}

YHVector2 & YHVector2::perp(bool cw)
{
	float tmp = m_x;
	
	if (cw)
	{
		m_x = m_y;
		m_y = -tmp;
	}
	else
	{
		m_x = -m_y;
		m_y = tmp;
	}
	
	return *this;
}

float YHVector2::dist(const YHVector2 & v2) const
{
	return sqrtf(distSQ(v2));
}

float YHVector2::distSQ(const YHVector2 & v2) const
{
	float dx = m_x - v2.getX();
	float dy = m_y - v2.getY();
	return dx * dx + dy * dy;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// end file



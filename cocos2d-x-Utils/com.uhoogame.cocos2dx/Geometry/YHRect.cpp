//
//  YHRect.cpp
//  GeometryLibrary
//
//  Created by Zhenyu Yao on 13-2-27.
//  Copyright (c) 2013年 Zhenyu Yao. All rights reserved.
//

#include "YHRect.h"

bool YHRect::containsPoint(const YHVector2 & point) const
{
	if ((m_position.getX() < point.getX() && m_position.getX() + m_size.getWidth() > point.getX())
		&& (m_position.getY() < point.getY() && m_position.getY() + m_size.getHeight() > point.getY()))
	{
		return true;
	}
	
	return false;
}

bool YHRect::containsRect(const YHRect & rect) const
{
	if ((rect.getX() - m_position.getX() < m_size.getWidth() - rect.getWidth())
		&& (rect.getY() - m_position.getY() <  m_size.getWidth() - rect.getHeight()))
	{
		return true;
	}
	
	return false;
}

bool YHRect::intersectsRect(const YHRect & rect) const
{
	if (m_position.getX() + m_size.getWidth() <= rect.getX()
		|| m_position.getX() >= rect.getX() + rect.getWidth()
		|| m_position.getY() + m_size.getHeight() <= rect.getY()
		|| m_position.getY() >= rect.getY() + rect.getHeight())
	{
		return false;
	}
		
	return true;
}

YHRect YHRect::getIntersectsRect(const YHRect & rect) const
{
	if (intersectsRect(rect))
	{
		YHVector2 leftBottom = findIntersectLeftBottom(rect);
		YHVector2 rightTop = findIntersectRightTop(rect);
		return YHRect(leftBottom, YHSize(rightTop.getX() - leftBottom.getX(), rightTop.getY() - leftBottom.getY()));
	}
	
	return YHRect();
}

YHVector2 YHRect::findIntersectLeftBottom(const YHRect & rect) const
{
	YHVector2 returnValue;
	returnValue.setX(m_position.getX() > rect.getX() ? m_position.getX() : rect.getX());
	returnValue.setY(m_position.getY() > rect.getY() ? m_position.getY() : rect.getY());
	return returnValue;
}

YHVector2 YHRect::findIntersectRightTop(const YHRect & rect) const
{
	YHVector2 returnValue;
	returnValue.setX(m_position.getX() + m_size.getWidth() < rect.getX() + rect.getWidth() ?
					 m_position.getX() + m_size.getWidth() : rect.getX() + rect.getWidth());
	returnValue.setY(m_position.getY() + m_size.getHeight() < rect.getY() + rect.getHeight() ?
					 m_position.getY() + m_size.getHeight() : rect.getY() + rect.getHeight());
	return returnValue;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// end file



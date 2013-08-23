//
//  YHParabolaEquation.cpp
//  GeometryLibrary
//
//  Created by Zhenyu Yao on 13-3-1.
//  Copyright (c) 2013年 Zhenyu Yao. All rights reserved.
//

#include "YHParabolaEquation.h"
#include <math.h>

/* YHParabolaEquation */

YHVector2 YHParabolaEquation::estimateVerticalTime(const YHEntity & entity, float y) const
{
	float delta = y - entity.getY();
	float a = 0.5f * entity.getAccY();
	float b = entity.getVelY();
	float c = -delta;
	
	YHVector2 time;
	float result = sloveQuadratic(a, b, c, time);
	if (!result)
	{
		time.setX(-1.0f);
		time.setY(-1.0f);
	}
	
	return time;
}

YHVector2 YHParabolaEquation::estimateHorizontalTime(const YHEntity & entity, float x) const
{
	float delta = x - entity.getX();
	float a = 0.5f * entity.getAccX();
	float b = entity.getVelX();
	float c = -delta;
	
	YHVector2 time;
	float result = sloveQuadratic(a, b, c, time);
	if (!result)
	{
		time.setX(-1.0f);
		time.setY(-1.0f);
	}
	
	return time;
}

YHVector2 YHParabolaEquation::estimateContactTime(const YHEntity & entityA, const YHEntity & entityB) const
{
	// 计算两个 Entity 水平方向上发生碰撞的时间
	YHEntity tmpEntity = YHEntity(YHVector2(0, 0),
								  YHVector2(entityB.getVelX() - entityA.getVelX(), 0),
								  YHVector2(entityB.getAccX() - entityA.getAccX(), 0));
	YHVector2 target = YHVector2(entityA.getX() - entityB.getX(), 0);
	YHVector2 horizontaTime = estimateHorizontalTime(tmpEntity, target.getX());
	
	// 计算两个 Entity 垂直方向上发生碰撞的时间
	tmpEntity = YHEntity(YHVector2(0, 0),
						 YHVector2(0, entityB.getVelY() - entityA.getVelY()),
						 YHVector2(0, entityB.getAccY() - entityA.getAccY()));
	target = YHVector2(0, entityA.getY() - entityB.getY());
	YHVector2 verticalTime = estimateVerticalTime(tmpEntity, target.getY());
	
	// 判断时间是否是有效值
	YHVector2 time = YHVector2(-1.0f, -1.0f);
	if (equalToFloat(horizontaTime.getX(), verticalTime.getX(), 2))
	{
		time.setX(horizontaTime.getX());
	}
	
	if (equalToFloat(horizontaTime.getX(), verticalTime.getY(), 2))
	{
		if (time.getX() == -1.0f)
		{
			time.setX(horizontaTime.getX());
		}
		else
		{
			time.setY(horizontaTime.getX());
		}
	}
	
	if (equalToFloat(horizontaTime.getY(), verticalTime.getX(), 2))
	{
		if (time.getX() == -1.0f)
		{
			time.setX(horizontaTime.getY());
		}
		else
		{
			time.setY(horizontaTime.getY());
		}
	}
	
	if (equalToFloat(horizontaTime.getY(), verticalTime.getY(), 2))
	{
		if (time.getX() == -1.0f)
		{
			time.setX(horizontaTime.getY());
		}
		else
		{
			time.setY(horizontaTime.getY());
		}
	}
	
	return time;
}

bool YHParabolaEquation::estimateFirstEntityVelYWhenContact(const YHEntity & first, const YHEntity & second, YHVector2 & vel) const
{
	// 首先求出水平方向上两个实体会发生碰撞的时间 t
	float a = 0.5f * (first.getAcc().getX() - second.getAcc().getX());
	float b = first.getVel().getX() - second.getVel().getX();
	float c = first.getPos().getX() - second.getPos().getX();
	
	YHVector2 time;
	bool result = sloveQuadratic(a, b, c, time);
	if (!result)
	{
		return false;
	}
	
	// 把时间 t 带入到 (p2 - p1) = (v1 - v2) * t + 0.5f * (a1 - a2) * t * t 公式中, 求出 v1, 这时 v1 就是需要的纵向速度
	a = 0.5f * (first.getAcc().getY() - second.getAcc().getY());
	c = first.getPos().getY() - second.getPos().getY();
	
	float t = time.getX();
	b = -(a * t * t + c) / t;
	vel.setX(b + second.getVel().getY());
	
	t = time.getY();
	b = -(a * t * t + c) / t;
	vel.setY(b + second.getVel().getY());
	
	return true;
}

float YHParabolaEquation::estimateVel(const YHEntity & entity, float time, float target, bool vertical) const
{
	float a = 0.5f * (vertical ? entity.getAccY() : entity.getAccX());
	float c = -(target - (vertical ? entity.getPos().getY() : entity.getPos().getX()));
	float b = (-c - a * time * time) / time;
	return b;
}

bool YHParabolaEquation::equalToFloat(float value1, float value2, int digitNumber) const
{
	float scale = powf(10, digitNumber);
	value1 *= scale;
	value2 *= scale;
	return (int)value1 == (int)value2;
}

bool YHParabolaEquation::sloveQuadratic(float a, float b, float c, YHVector2 & root) const
{
	if (a == 0)
	{
		if (b == 0)
		{
			if (c == 0)
			{
				root.setX(0);
				root.setY(0);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			root.setX(-c / b);
			root.setY(-c / b);
			return true;
		}
	}
	
	float sq = b * b - 4.0f * a * c;
	if (sq < 0.0f)
	{
		return false;
	}
	
	float x1 = (-b + sqrtf(sq)) / (2.0f * a);
	float x2 = (-b - sqrtf(sq)) / (2.0f * a);
	root.setX(x1);
	root.setY(x2);
	return true;
}

float YHParabolaEquation::sloveQuadraticResult(float a, float b, float c, float x) const
{
	float result = a * x * x + b * x + c;
	return result;
}

/* YHParabolaEulerEquation */

YHVector2 YHParabolaEulerEquation::estimatePosition(const YHEntity & entity, float dt) const
{
	return entity.estimatePositionWithEuler(dt);
}

/* YHParabolaRK2Equation */

YHVector2 YHParabolaRK2Equation::estimatePosition(const YHEntity & entity, float dt) const
{
	return entity.estimatePositionWithRK2(dt);
}

/* YHParabolaRK4Equation */

YHVector2 YHParabolaRK4Equation::estimatePosition(const YHEntity & entity, float dt)const
{
	return entity.estimatePositionWithRK4(dt);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// end file



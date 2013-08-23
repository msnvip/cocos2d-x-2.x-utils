//
//  YHEntity.cpp
//  GeometryLibrary
//
//  Created by Zhenyu Yao on 13-2-28.
//  Copyright (c) 2013年 Zhenyu Yao. All rights reserved.
//

#include "YHEntity.h"

void YHEntity::updateWithEuler(float dt)
{
	calculateWithEuler(m_pos, m_vel, m_acc, dt);
}

void YHEntity::updateWithRK2(float dt)
{
	calculateWithRK2(m_pos, m_vel, m_acc, dt);
}

void YHEntity::updateWithRK4(float dt)
{
	calculateWithRK4(m_pos, m_vel, m_acc, dt);
}

YHVector2 YHEntity::estimatePositionWithEuler(float dt) const
{
	YHVector2 estimatePos = m_pos.clone();
	YHVector2 vel = m_vel.clone();
	YHVector2 acc = m_acc.clone();
	calculateWithEuler(estimatePos, vel, acc, dt);
	return estimatePos;
}

YHVector2 YHEntity::estimatePositionWithRK2(float dt) const
{
	YHVector2 estimatePos = m_pos.clone();
	YHVector2 vel = m_vel.clone();
	YHVector2 acc = m_acc.clone();
	calculateWithRK2(estimatePos, vel, acc, dt);
	return estimatePos;
}

YHVector2 YHEntity::estimatePositionWithRK4(float dt) const
{
	YHVector2 estimatePos = m_pos.clone();
	YHVector2 vel = m_vel.clone();
	YHVector2 acc = m_acc.clone();
	calculateWithRK4(estimatePos, vel, acc, dt);
	return estimatePos;
}

YHEntity YHEntity::clone() const
{
	return YHEntity(m_pos.clone(), m_vel.clone(), m_acc.clone());
}

void YHEntity::calculateWithEuler(YHVector2 & pos, YHVector2 & vel, YHVector2 & acc, float dt) const
{
	pos.setX(pos.getX() + vel.getX() * dt);
	pos.setY(pos.getY() + vel.getY() * dt);
	
	vel.setX(vel.getX() + acc.getX() * dt);
	vel.setY(vel.getY() + acc.getY() * dt);
}

void YHEntity::calculateWithRK2(YHVector2 & pos, YHVector2 & vel, YHVector2 & acc, float dt) const
{
	pos.setX(pos.getX() + vel.getX() * dt + 0.5f * acc.getX() * dt * dt);
	pos.setY(pos.getY() + vel.getY() * dt + 0.5f * acc.getY() * dt * dt);
	
	vel.setX(vel.getX() + acc.getX() * dt);
	vel.setY(vel.getY() + acc.getY() * dt);
}

void YHEntity::calculateWithRK4(YHVector2 & pos, YHVector2 & vel, YHVector2 & acc, float dt) const
{
	YHVector2 pos2 = YHVector2(pos.getX() + vel.getX() * 0.5f * dt, pos.getY() + vel.getY() * 0.5f * dt);
	YHVector2 vel2 = YHVector2(vel.getX() + acc.getX() * 0.5f * dt, vel.getY() + acc.getY() * 0.5f * dt);
	YHVector2 acc2 = acceleration(pos2, vel2, acc, dt);
	
	YHVector2 pos3 = YHVector2(pos.getX() + vel2.getX() * 0.5f * dt, pos.getY() + vel2.getY() * 0.5f * dt);
	YHVector2 vel3 = YHVector2(vel.getX() + acc2.getX() * 0.5f * dt, vel.getY() + acc2.getY() * 0.5f * dt);
	YHVector2 acc3 = acceleration(pos3, vel3, acc, dt);
	
	YHVector2 pos4 = YHVector2(pos.getX() + vel3.getX() * dt, pos.getY() + vel3.getY() * dt);
	YHVector2 vel4 = YHVector2(vel.getX() + acc3.getX() * dt, vel.getY() + acc3.getY() * dt);
	YHVector2 acc4 = acceleration(pos4, vel4, acc, dt);
	
	pos.setX(pos.getX() + (vel.getX() + 2.0f * vel2.getX() + 2.0f * vel3.getX() + vel4.getX()) / 6.0f * dt);
	pos.setY(pos.getY() + (vel.getY() + 2.0f * vel2.getY() + 2.0f * vel3.getY() + vel4.getY()) / 6.0f * dt);
	
	vel.setX(vel.getX() + (acc.getX() + 2.0f * acc2.getX() + 2.0f * acc3.getX() + acc4.getX()) / 6.0f * dt);
	vel.setY(vel.getY() + (acc.getY() + 2.0f * acc2.getY() + 2.0f * acc3.getY() + acc4.getY()) / 6.0f * dt);
}

YHVector2 YHEntity::acceleration(const YHVector2 & pos, const YHVector2 & vel, const YHVector2 & acc, float dt) const
{
	return acc.clone();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// end file



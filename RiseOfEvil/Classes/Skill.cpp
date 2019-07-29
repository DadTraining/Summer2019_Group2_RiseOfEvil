#include "Skill.h"

Skill::Skill(int type)
{
	typeSkill = type;
	Init();
}

Skill::~Skill()
{
}

void Skill::Init()
{
	switch (typeSkill)
	{
	case SLOW_SKILL:
		m_sprite = Sprite::create("range_of_barrack_tower.png");
		m_sprite->setOpacity(30);
		break;
	case BURN_SKILL:
		m_sprite = Sprite::create("range_of_barrack_tower.png");
		m_sprite->setOpacity(30);
		break;
	case INCREASE_ATTACKSPEED_SKILL:
		m_sprite = Sprite::create("range_of_barrack_tower.png");
		m_sprite->setOpacity(30);
		break;
	case INCREASE_ATTACKDAMAGE_SKILL:
		m_sprite = Sprite::create("range_of_barrack_tower.png");
		m_sprite->setOpacity(30);
		break;
	}
}

Sprite * Skill::getSprite()
{
	return m_sprite;
}

void Skill::effect(Objects*)
{
}

//void Skill::increaseAttackSpeedSkill(Tower * tower, vector<Tower*>listTower)
//{
//	for (int i = 0; i < listTower.size(); i++)
//	{
//		float increaseAttackSpeed = listTower[i]->GetAttackSpeed() + listTower[i]->GetAttackSpeed() * 20 / 100;
//		if (tower->GetSprite()->getPosition().distance(listTower[i]->GetSprite()->getPosition()) < 150)
//		{
//			listTower[i]->SetAttackSpeed(increaseAttackSpeed);
//		}
//	}
//
//}
//
//void Skill::increaseAttackDamageSkill(Tower * tower, vector<Tower*> listTower)
//{
//	for (int i = 0; i < listTower.size(); i++)
//	{
//		int increaseMinimumAtk = listTower[i]->GetMinimumAtk() + (int)listTower[i]->GetMinimumAtk() * 20 / 100;
//		int increaseMaximumAtk = listTower[i]->GetMaximumAtk() + (int)listTower[i]->GetMaximumAtk() * 20 / 100;
//		if (tower->GetSprite()->getPosition().distance(listTower[i]->GetSprite()->getPosition()) < 150)
//		{
//			listTower[i]->SetMinimumAtk(increaseMinimumAtk);
//			listTower[i]->SetMaximumAtk(increaseMaximumAtk);
//		}
//	}
//}
//
//void Skill::slowSkill(Tower * tower, vector<Monster*> listMonster)
//{
//	for (int i = 0; i < listMonster.size(); i++)
//	{
//		float decreaseSpeedMonster = listMonster[i]->GetMovementSpeed() - listMonster[i]->GetMovementSpeed() * 10 / 100;
//		if (tower->GetSprite()->getPosition().distance(listMonster[i]->GetSprite()->getPosition()) < 150)
//		{
//			listMonster[i]->SetMovementSpeed(decreaseSpeedMonster);
//		}
//		// if monster out range increase speed 
//	}
//}
//
//void Skill::burnSkill(Tower * tower, vector<Monster*> listMonster, float deltaTime)
//{
//}
//
//void Skill::burnSkill(Tower * tower, vector<Monster*> listMonster, float deltaTime)
//{
//	for (int i = 0; i < listMonster.size(); i++)
//	{
//		if (countTimeToReduceHPForBurnSkill >= 1)
//		{
//			if (tower->GetSprite()->getPosition().distance(listMonster[i]->GetSprite()->getPosition()) < 150)
//			{
//				listMonster[i]->SetHitPoint(listMonster[i]->GetHitPoint() - 5);
//				countTimeToReduceHPForBurnSkill = 0;
//			}
//		}
//		else
//		{
//			countTimeToReduceHPForBurnSkill += deltaTime;
//		}
//	}
//}
//
//void Skill::bossSkill(Monster * boss, vector<Monster*> listMonster, float deltaTime)
//{
//	for (int i = 0; i < listMonster.size(); i++)
//	{
//		if (boss->GetSprite()->getPosition().distance(listMonster[i]->GetSprite()->getPosition()) < 150)
//		{
//			listMonster[i]->SetMSpeed(listMonster[i]->GetMSpeed() + 10);
//			if (listMonster[i]->GetHitPoint() < listMonster[i]->GetMaxHitPoint())
//			{
//				if (countTimeToIncreaseHP > 1)
//				{
//					listMonster[i]->SetHitPoint(listMonster[i]->GetHitPoint() + 5);
//					countTimeToIncreaseHP = 0;
//				}
//				else
//				{
//					countTimeToIncreaseHP += deltaTime;
//				}
//			}
//		}
//	}
//}

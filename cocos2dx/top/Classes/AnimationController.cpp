#include "AnimationController.h"

USING_NS_CC;

const char *AnimationController::NAME = "AnimationController";

AnimationController::AnimationController()
	: m_pArmature(nullptr)
{
	this->setName(AnimationController::NAME);
}

AnimationController::~AnimationController()
{
	
}

void AnimationController::load( const char *armatureName )
{
	auto owner = this->getOwner();
	if (owner && armatureName)
	{
		if (m_animationName.compare(armatureName) != 0)
		{
			auto *armature = cocostudio::Armature::create(armatureName);
			if (!armature)
			{
				return;
			}

			if (m_pArmature)
			{
				owner->removeChild(m_pArmature, true);
				m_pArmature = nullptr;
			}

			owner->addChild(armature);
			m_pArmature = armature;
			m_animationName = armatureName;
		}
	}
}

void AnimationController::play( const char *movementName, int playMode /*= Default*/ )
{
	if (m_pArmature)
	{
		if (m_pArmature->getAnimation()->getAnimationData()->getMovement(movementName))
		{
			m_pArmature->getAnimation()->play(movementName, -1, playMode);;
		}
	}
}

void AnimationController::setMovementCallback( const std::function<void(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID)> &callback )
{
	if (m_pArmature)
	{
		m_pArmature->getAnimation()->setMovementEventCallFunc(callback);
	}
}

void AnimationController::pause()
{
	if (m_pArmature)
	{
		m_pArmature->getAnimation()->pause();
	}
}

void AnimationController::resume()
{
	if (m_pArmature)
	{
		m_pArmature->getAnimation()->resume();
	}
}

void AnimationController::stop()
{
	if (m_pArmature)
	{
		m_pArmature->getAnimation()->stop();
	}
}


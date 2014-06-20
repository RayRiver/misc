#include "AnimationController.h"

#include "cocos2d.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaEngine.h"
#include "LuaValueList.h"

USING_NS_CC;

AnimationController* AnimationController::create( void )
{
	AnimationController * ret = new AnimationController();
	if (ret != nullptr && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

AnimationController::AnimationController()
	: m_pArmature(nullptr)
	, m_animationSpeedScale(1.0f)
{
	this->setName("AnimationController");
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



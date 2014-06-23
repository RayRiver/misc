#include "AnimationController.h"

#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "LuaValueList.h"
#include "LuaScriptHandlerMgr.h"
#include "EventDef.h"

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

bool AnimationController::checkCollider(Rect rect)
{
	if (!m_pArmature) return false;

	auto owner = getOwner();
	if (!owner) return false;
	auto owner_x = owner->getPositionX();
	auto owner_y = owner->getPositionY();

	auto &boneDict = m_pArmature->getBoneDic();
	for (const auto &element : boneDict)
	{
		auto bone = element.second;
		auto detector = bone->getColliderDetector();

		if (!detector) { continue; }

		auto bodyList = detector->getColliderBodyList();
		for (const auto &object : bodyList)
		{
			auto body = static_cast<cocostudio::ColliderBody*>(object);

			auto vertexList = body->getCalculatedVertexList();

			// 生成临时碰撞区
			float minx = 0, miny = 0, maxx = 0, maxy = 0;
			size_t length = vertexList.size();
			for (size_t i = 0; i<length; i++)
			{
				Vec2 vertex = vertexList.at(i);
				if (i == 0)
				{
					minx = maxx = vertex.x;
					miny = maxy = vertex.y;
				}
				else
				{
					minx = vertex.x < minx ? vertex.x : minx;
					miny = vertex.y < miny ? vertex.y : miny;
					maxx = vertex.x > maxx ? vertex.x : maxx;
					maxy = vertex.y > maxy ? vertex.y : maxy;
				}
			}
			Rect temp = Rect(minx, miny, maxx - minx, maxy - miny);
			temp.origin.x = temp.origin.x + owner_x;
			temp.origin.y = temp.origin.y + owner_y;

			//temp.origin = m_pArmature->convertToWorldSpace(temp.origin);

			if (temp.intersectsRect(rect))
			{
				return true;
			}
		}
	}
	return false;
}

void AnimationController::setMovementEventCallFunc( LUA_FUNCTION handler )
{
	if (m_pArmature)
	{
		ScriptHandlerMgr::getInstance()->removeObjectHandler((void *)this, EVENT_USEREXT_CUSTOM_ANIAMTION_ONMOVEMENT);
		ScriptHandlerMgr::getInstance()->addObjectHandler((void *)this, handler, EVENT_USEREXT_CUSTOM_ANIAMTION_ONMOVEMENT);
		m_pArmature->getAnimation()->setMovementEventCallFunc([=](cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID) {
#if CC_ENABLE_SCRIPT_BINDING
			if (_scriptType == kScriptTypeLua)
			{
				int nHandler = cocos2d::ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, EVENT_USEREXT_CUSTOM_ANIAMTION_ONMOVEMENT);
				if (0 != nHandler) 
				{
					cocos2d::LuaStack *stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
					stack->pushLuaValue(LuaValue::intValue(movementType));
					stack->pushLuaValue(LuaValue::stringValue(movementID));
					int ret = stack->executeFunctionByHandler(nHandler, 2);
					stack->clean();
				}
			}
#endif // CC_ENABLE_SCRIPT_BINDIN	
		});
	}
}

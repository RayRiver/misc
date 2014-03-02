#include "B2Sprite.h"
#include "Box2D/Box2D.h"

using namespace std;
USING_NS_CC;

B2Sprite::B2Sprite()
: _ignoreBodyRotation(false)
, _pB2Body(nullptr)
, _PTMRatio(0.0f)
, m_type(0)
{}

B2Sprite* B2Sprite::create()
{
    B2Sprite* pRet = new B2Sprite();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

B2Sprite* B2Sprite::createWithTexture(Texture2D *pTexture)
{
    B2Sprite* pRet = new B2Sprite();
    if (pRet && pRet->initWithTexture(pTexture))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

B2Sprite* B2Sprite::createWithTexture(Texture2D *pTexture, const Rect& rect)
{
    B2Sprite* pRet = new B2Sprite();
    if (pRet && pRet->initWithTexture(pTexture, rect))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

B2Sprite* B2Sprite::createWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
    B2Sprite* pRet = new B2Sprite();
    if (pRet && pRet->initWithSpriteFrame(pSpriteFrame))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

B2Sprite* B2Sprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    B2Sprite* pRet = new B2Sprite();
    if (pRet && pRet->initWithSpriteFrameName(pszSpriteFrameName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

B2Sprite* B2Sprite::create(const char *pszFileName)
{
    B2Sprite* pRet = new B2Sprite();
    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

B2Sprite* B2Sprite::create(const char *pszFileName, const Rect& rect)
{
    B2Sprite* pRet = new B2Sprite();
    if (pRet && pRet->initWithFile(pszFileName, rect))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

// this method will only get called if the sprite is batched.
// return YES if the physic's values (angles, position ) changed.
// If you return NO, then getNodeToParentTransform won't be called.
bool B2Sprite::isDirty() const
{
    return true;
}

bool B2Sprite::isIgnoreBodyRotation() const
{
    return _ignoreBodyRotation;
}

void B2Sprite::setIgnoreBodyRotation(bool bIgnoreBodyRotation)
{
    _ignoreBodyRotation = bIgnoreBodyRotation;
}

// Override the setters and getters to always reflect the body's properties.
const Point& B2Sprite::getPosition() const
{
    return getPosFromPhysics();
}

void B2Sprite::getPosition(float* x, float* y) const
{
    if (x == NULL || y == NULL) {
        return;
    }
    const Point& pos = getPosFromPhysics();
    *x = pos.x;
    *y = pos.y;
}

float B2Sprite::getPositionX() const
{
    return getPosFromPhysics().x;
}

float B2Sprite::getPositionY() const
{
    return getPosFromPhysics().y;
}

//
// box2d only
//

b2Body* B2Sprite::getB2Body() const
{
    return _pB2Body;
}

void B2Sprite::setB2Body(b2Body *pBody)
{
    _pB2Body = pBody;
}

float B2Sprite::getPTMRatio() const
{
    return _PTMRatio;
}

void B2Sprite::setPTMRatio(float fRatio)
{
     _PTMRatio = fRatio;
}

//
// Common to Box2d and Chipmunk
//

const Point& B2Sprite::getPosFromPhysics() const
{
    static Point s_physicPosion;

    b2Vec2 pos = _pB2Body->GetPosition();
    float x = pos.x * _PTMRatio;
    float y = pos.y * _PTMRatio;
    s_physicPosion = Point(x,y);

    return s_physicPosion;
}

void B2Sprite::setPosition(const Point &pos)
{
    float angle = _pB2Body->GetAngle();
    _pB2Body->SetTransform(b2Vec2(pos.x / _PTMRatio, pos.y / _PTMRatio), angle);
}

float B2Sprite::getRotation() const
{
    return (_ignoreBodyRotation ? Sprite::getRotation() :
            CC_RADIANS_TO_DEGREES(_pB2Body->GetAngle()));
}

void B2Sprite::setRotation(float fRotation)
{
    if (_ignoreBodyRotation)
    {
        Sprite::setRotation(fRotation);
    }
    else
    {
        b2Vec2 p = _pB2Body->GetPosition();
        float radians = CC_DEGREES_TO_RADIANS(fRotation);
        _pB2Body->SetTransform(p, radians);
    }
}

// returns the transform matrix according the Chipmunk Body values
const kmMat4& B2Sprite::getNodeToParentTransform() const
{
    // Although scale is not used by physics engines, it is calculated just in case
	// the sprite is animated (scaled up/down) using actions.
	// For more info see: http://www.cocos2d-iphone.org/forum/topic/68990


    b2Vec2 pos  = _pB2Body->GetPosition();

	float x = pos.x * _PTMRatio;
	float y = pos.y * _PTMRatio;

	if (_ignoreAnchorPointForPosition)
    {
		x += _anchorPointInPoints.x;
		y += _anchorPointInPoints.y;
	}

	// Make matrix
	float radians = _pB2Body->GetAngle();
	float c = cosf(radians);
	float s = sinf(radians);

	if (!_anchorPointInPoints.equals(Point::ZERO))
    {
		x += ((c * -_anchorPointInPoints.x * _scaleX) + (-s * -_anchorPointInPoints.y * _scaleY));
		y += ((s * -_anchorPointInPoints.x * _scaleX) + (c * -_anchorPointInPoints.y * _scaleY));
	}

	// Rot, Translate Matrix
    
    kmScalar mat[] = {  (kmScalar)c * _scaleX, (kmScalar)s * _scaleX, 0,  0,
        (kmScalar)-s * _scaleY, (kmScalar)c * _scaleY,  0,  0,
        0,  0,  1,  0,
        x,	y,  0,  1};
    
    
    kmMat4Fill(&_transform, mat);

	return _transform;
}


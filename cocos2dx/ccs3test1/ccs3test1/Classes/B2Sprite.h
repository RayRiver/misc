#ifndef __B2SPRITE_H__
#define __B2SPRITE_H__

#include "cocos2d.h"

struct cpBody;
class b2Body;

class B2Sprite : public cocos2d::Sprite
{
public:

    static B2Sprite* create();
    /** Creates an sprite with a texture.
     The rect used will be the size of the texture.
     The offset will be (0,0).
     */
    static B2Sprite* createWithTexture(cocos2d::Texture2D *pTexture);

    /** Creates an sprite with a texture and a rect.
     The offset will be (0,0).
     */
    static B2Sprite* createWithTexture(cocos2d::Texture2D *pTexture, const cocos2d::Rect& rect);

    /** Creates an sprite with an sprite frame. */
    static B2Sprite* createWithSpriteFrame(cocos2d::SpriteFrame *pSpriteFrame);

    /** Creates an sprite with an sprite frame name.
     An SpriteFrame will be fetched from the SpriteFrameCache by name.
     If the SpriteFrame doesn't exist it will raise an exception.
     @since v0.9
     */
    static B2Sprite* createWithSpriteFrameName(const char *pszSpriteFrameName);

    /** Creates an sprite with an image filename.
     The rect used will be the size of the image.
     The offset will be (0,0).
     */
    static B2Sprite* create(const char *pszFileName);

    /** Creates an sprite with an image filename and a rect.
     The offset will be (0,0).
     */
    static B2Sprite* create(const char *pszFileName, const cocos2d::Rect& rect);

    B2Sprite();

    virtual bool isDirty() const;

    /** Keep the sprite's rotation separate from the body. */
    bool isIgnoreBodyRotation() const;
    void setIgnoreBodyRotation(bool bIgnoreBodyRotation);

    //
    // Chipmunk specific
    //
    /** Body accessor when using regular Chipmunk */
    cpBody* getCPBody() const;
    void setCPBody(cpBody *pBody);

    //
    // Box2d specific
    //
    /** Body accessor when using box2d */
    b2Body* getB2Body() const;
    void setB2Body(b2Body *pBody);

    float getPTMRatio() const;
    void setPTMRatio(float fPTMRatio);

    // overrides
    virtual const cocos2d::Point& getPosition() const override;
    virtual void getPosition(float* x, float* y) const override;
    virtual float getPositionX() const override;
    virtual float getPositionY() const override;
    virtual void setPosition(const cocos2d::Point &position) override;
    virtual float getRotation() const override;
    virtual void setRotation(float fRotation) override;
    virtual const kmMat4& getNodeToParentTransform() const override;

protected:
    const cocos2d::Point& getPosFromPhysics() const;

protected:
    bool    _ignoreBodyRotation;

    // box2d specific
    b2Body  *_pB2Body;
    float   _PTMRatio;
};

#endif // __B2SPRITE_H__

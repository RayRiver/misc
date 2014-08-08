#ifndef ListScene_h__
#define ListScene_h__

#include "cocos2d.h"

class ListScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(ListScene);
};

#endif // ListScene_h__


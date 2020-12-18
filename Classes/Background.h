#pragma once
#include "cocos2d.h"

class Background : public cocos2d::Sprite
{
public:
	static Background* create();
    void update();

private:

    void initBackground();

    cocos2d::ParallaxNode* paraNodeClose;
    cocos2d::ParallaxNode* paraNodeMid;
    cocos2d::ParallaxNode* paraNodeFar;
    float closeSpeed;
    float midSpeed;
    float farSpeed;

};
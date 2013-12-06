#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "SimpleDPad.h"
#include "HudLayer.h"

class GameLayer : public cocos2d::CCLayer, public SimpleDPadDelegate
{
public:
	GameLayer(void);
	~GameLayer(void);

	CREATE_FUNC(GameLayer);
	bool init();
	void initTileMap();
	void initHero();
	void initRobots();
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	virtual void didChangeDirectionTo(SimpleDPad *simpleDPad, cocos2d::CCPoint direction);
	virtual void isHoldingDirection(SimpleDPad *simpleDPad, cocos2d::CCPoint direction);
	virtual void simpleDPadTouchEnded(SimpleDPad *simpleDPad);

	void update(float dt);
	void updatePositions();
	void setViewpointCenter(cocos2d::CCPoint position);
	void reorderActors();
	void updateRobots(float dt);

	void endGame();
	void restartGame(cocos2d::CCObject* pSender);

	cocos2d::CCTMXTiledMap *_tileMap;
	cocos2d::CCSpriteBatchNode *_actors;
	Hero *_hero;
	CC_SYNTHESIZE(HudLayer*, _hud, Hud);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, _robots, Robots);
};

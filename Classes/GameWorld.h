#ifndef CCISO_GAMEWORLD_H_
#define CCISO_GAMEWORLD_H_

#include "cocos2d.h"
#include "GameConfig.h"
#include "CCAstar.h"
#include "CCZIndex.h"

#include "Player.h"

#define Background_ZOrder -10
#define Intermediate_ZOrder 0
#define Foreground_ZOrder 10

USING_NS_CC;

NS_YH_BEGIN

class GameWorld: public CCLayer
{
public:
	GameWorld();
	~GameWorld();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	virtual bool init(int mapId);
    // implement the "static node()" method manually
    CREATE_FUNC(GameWorld);

	 // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void menuRunCallback(CCObject* pSender);
    void menuStopCallback(CCObject* pSender);
    void menuMoveToCallback(CCObject* pSender);

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); 
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent); 
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); 

	

	void setup();
	void setupUtil();
	void setupGameWorlds();
	void loadMapData();
	void loadBackground();
	void loadInterMediate();
	void loadForeground();

	void addInterMediateStaticEntity(WorldEntity* entity);
	void addInterMediateDynamicEntity(Unit* entity);
	void removeInterMediateDynamicEntity(Unit* entity);
	void removeInterMediateStaticEntity(WorldEntity* entity);
	void addPlayerAtCoord(CCPoint coord);
	void addTeammateAtCoord(CCPoint coord);
	void removeTeammate(Player* player);
	void movePlayerToViewLocation(CCPoint location);
	void moveEntity(Unit* entity,CCPoint coord);
	void moveViewEntity(Unit* entity,CCPoint location);
	//void addBuildingAt(CCPoint coord);
	//void removeBuilding(Building* building);

	CCArray* searchPathsFrom(int fromX,int fromY,int toX,int toY);
	CCArray* searchPathsFrom(CCPoint from,CCPoint to);
	CCArray* mapPathsToViewPaths(CCArray* paths);

	void showBarrier();
	void showGameOver();

	//get set
	virtual void setMapColumn(int iMapColumn);
	virtual int getMapColumn();
	virtual void setMapRow(int iMapRow);
	virtual int getMapRow();
	virtual void setMapId(int iMapId);
	virtual int getMapId();
	virtual void setBackground(CCLayer* pBackground);
	virtual CCLayer* getBackground();
	virtual void setIntermediate(CCLayer* pIntermediate);
	virtual CCLayer* getIntermediate();
	virtual void setForeground(CCLayer* pForeground);
	virtual CCLayer* getForeground();

private:
	//��ͼ���
	int m_iMapColumn;
	int m_iMapRow;
	int m_iMapId;
	CCLayer* m_pBackground;//�����㣬���ص�����Դ
	CCLayer* m_pIntermediate;//�м�㣬��ʾ��ɫ������ȿɱ�Ԫ��
	CCLayer* m_pForeground;//ǰ����,������ĳЩ������ڵ�Ԫ�ء�ͨ��Ϊ�ա�

	//Ѱ·
	CCAstar* m_pAstar;
	//�����ڵ�
	CCZIndex* m_pZIndex;

	Player* m_pPlayer;

	//touch
	CCPoint m_oLastTouchLocation;
	bool m_bIsTouchMoved;

	//units
	CCArray* m_pUnits;
	/*CCArray* m_pBuildings;
	CCArray* m_pMonsters;
	CCArray* m_pResources;*/
};

NS_YH_END

#endif // CCISO_GAMEWORLD_H_

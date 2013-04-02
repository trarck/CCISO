#ifndef ISO_CCISOTile_H_
#define ISO_CCISOTile_H_

#include "cocos2d.h"

NS_CC_BEGIN

class CCISOTileset;

class CCISOTile : public CCObject{

public:
    CCISOTile(int id);
    
    CCISOTile(int id,CCSprite* sprite,CCISOTileset* tileset);
    
    ~CCISOTile();
   
    CCSize size(){return m_pSprite->getContentSize();}

public:
    
    virtual void setId(int nId);
    
    virtual int getId();
    
    virtual void setTileset(CCISOTileset* pTileset);
    
    virtual CCISOTileset* getTileset();
    
    virtual void setSprite(CCSprite* pSprite);
    
    virtual CCSprite* getSprite();
    
protected:
    
    int m_nId;
    
    //weak reference
    CCISOTileset* m_pTileset;
    
    CCSprite* m_pSprite;

};


NS_CC_END

#endif //ISO_CCISOTile_H_

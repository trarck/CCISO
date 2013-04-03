#ifndef ISO_CCISOTile_H_
#define ISO_CCISOTile_H_

#include "cocos2d.h"

NS_CC_BEGIN

class CCISOTileset;

class CCISOTile : public CCObject{

public:
    CCISOTile();
    
    ~CCISOTile();
    
    bool init();
    
    bool init(int id,CCISOTileset* tileset);
    
    bool init(int id,CCISOTileset* tileset,CCSprite* sprite);
  
   
    CCSize size(){return m_pSprite->getContentSize();}

public:
    
    virtual void setId(int nId);
    
    virtual int getId();
    
    virtual void setTileset(CCISOTileset* pTileset);
    
    virtual CCISOTileset* getTileset();
    
    virtual void setSprite(CCSprite* pSprite);
    
    virtual CCSprite* getSprite();
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    
protected:
    
    int m_nId;
    
    //weak reference
    CCISOTileset* m_pTileset;
    
    CCSprite* m_pSprite;

    /**
     * 属性
     */
    CCDictionary* m_pProperties;
};


NS_CC_END

#endif //ISO_CCISOTile_H_

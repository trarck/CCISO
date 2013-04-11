#ifndef ISO_CCISOTile_H_
#define ISO_CCISOTile_H_

#include "cocos2d.h"

NS_CC_BEGIN

class CCISOTileset;

/**
 * 直接使用texure。如果使用sprite，则无法共用。
 *
 */
class CCISOTile : public CCObject{

public:
    CCISOTile();
    
    ~CCISOTile();
    
    bool init();
    
    bool init(int id,CCISOTileset* tileset);
    
    bool init(int id,CCISOTileset* tileset,CCTexture2D* texture);
    
    bool init(int id,CCISOTileset* tileset,CCTexture2D* texture,CCRect& textureRect);
   
    CCSize size(){return m_tTextureRect.size;}

public:
    
    virtual int getGId();
    
    
    virtual void setId(int nId);
    
    virtual int getId();    
    
    virtual void setTileset(CCISOTileset* pTileset);
    
    virtual CCISOTileset* getTileset();
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    
    inline void setTexture(CCTexture2D* pTexture)
    {
        CC_SAFE_RETAIN(pTexture);
        CC_SAFE_RELEASE(m_pTexture);
        m_pTexture = pTexture;
    }
    
    inline CCTexture2D* getTexture()
    {
        return m_pTexture;
    }
    
    inline void setTextureRect(CCRect& tTextureRect)
    {
        m_tTextureRect = tTextureRect;
    }
    
    inline CCRect& getTextureRect()
    {
        return m_tTextureRect;
    }
    
protected:
    
    int m_nId;
    
    //支持tile大小不同
    CCTexture2D* m_pTexture;
    
    CCRect m_tTextureRect;
    
    //weak reference
    CCISOTileset* m_pTileset;
    
    /**
     * 属性
     */
    CCDictionary* m_pProperties;
};


NS_CC_END

#endif //ISO_CCISOTile_H_

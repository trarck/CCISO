#ifndef ISO_CCISOMapInfo_H_
#define ISO_CCISOMapInfo_H_

#include "cocos2d.h"
#include "CCISOTileLayer.h"

NS_CC_BEGIN

class CCISOMapInfo : public CCObject{

public:
    
    CCISOMapInfo();
    
    ~CCISOMapInfo();
    
    virtual bool init();
    
    virtual void setOrientation(int nOrientation);
    virtual int getOrientation();
    
    virtual void setMapSize(const CCSize& tMapSize);
    virtual const CCSize& getMapSize();
    
    virtual void setTileSize(const CCSize& tTileSize);
    virtual const CCSize& getTileSize();
    
    virtual void setLayers(CCArray* pLayers);
    virtual CCArray* getLayers();
    
    virtual void setTilesets(CCArray* pTilesets);
    virtual CCArray* getTilesets();
    
    virtual void setObjectGroups(CCArray* pObjectLayers);
    virtual CCArray* getObjectGroups();
    
    virtual void setObjectLayers(CCArray* pObjectLayers);
    virtual CCArray* getObjectLayers();
    
    virtual void setParentElement(int nParentElement);
    virtual int getParentElement();
    
    virtual void setParentGID(unsigned int uParentGID);
    virtual unsigned int getParentGID();
    
    virtual void setLayerAttribs(int nLayerAttribs);
    virtual int getLayerAttribs();
    
    virtual void setStoringCharacters(bool bStoringCharacters);
    virtual bool getStoringCharacters();
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    
    CCDictionary* getTileProperties();
    void setTileProperties(CCDictionary* tileProperties);
    
    
protected:
    int m_nOrientation;
    CCSize m_tMapSize;
    CCSize m_tTileSize;
    CCArray* m_pLayers;
    CCArray* m_pTilesets;
    CCArray* m_pObjectLayers;
    int m_nParentElement;
    unsigned int m_uParentGID;
    int m_nLayerAttribs;
    bool m_bStoringCharacters;
    CCDictionary* m_pProperties;
	CCDictionary* m_pTileProperties;
    
};


NS_CC_END

#endif //ISO_CCISOMapInfo_H_

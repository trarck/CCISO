#ifndef ISO_CCISOMapInfo_H_
#define ISO_CCISOMapInfo_H_

#include "cocos2d.h"
#include "CCISOTileLayer.h"

NS_CC_BEGIN

enum {
    ISOParseLayerAttribNone = 1 << 0,
    ISOParseLayerAttribBase64 = 1 << 1,
    ISOParseLayerAttribGzip = 1 << 2,
    ISOParseLayerAttribZlib = 1 << 3,
};

enum {
    ISOParsePropertyNone,
    ISOParsePropertyMap,
    ISOParsePropertyTileset,
    ISOParsePropertyLayer,
    ISOParsePropertyObjectGroup,
    ISOParsePropertyObject,
    ISOParsePropertyTile,
    ISOParsePropertyImage
};


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
    
    virtual void setObjectGroups(CCArray* pObjectGroups);
    virtual CCArray* getObjectGroups();
       
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
        
    
protected:
    int m_nOrientation;
    CCSize m_tMapSize;
    CCSize m_tTileSize;
    CCArray* m_pLayers;
    CCArray* m_pTilesets;
    CCArray* m_pObjectGroups;

    CCDictionary* m_pProperties;
	CCDictionary* m_pTileProperties;
    
};


NS_CC_END

#endif //ISO_CCISOMapInfo_H_

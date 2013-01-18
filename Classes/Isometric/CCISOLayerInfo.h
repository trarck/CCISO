#ifndef ISO_CCISOLayerInfo_H_
#define ISO_CCISOLayerInfo_H_

#include "cocos2d.h"
#include "CCISOTileLayer.h"

NS_CC_BEGIN

class CCISOLayerInfo : public CCObject{

public:
    
    CCISOLayerInfo();
    ~CCISOLayerInfo();
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();

public:
    std::string         m_sName;
    CCSize              m_tLayerSize;
    unsigned int*       m_pTiles;
    bool                m_bVisible;
    unsigned char       m_cOpacity;
    bool                m_bOwnTiles;
    unsigned int        m_uMinGID;
    unsigned int        m_uMaxGID;
    CCPoint             m_tOffset;

    CCDictionary* m_pProperties;
};


NS_CC_END

#endif //ISO_CCISOLayerInfo_H_

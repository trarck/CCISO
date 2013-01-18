#ifndef ISO_CCISOTilesetInfo_H_
#define ISO_CCISOTilesetInfo_H_

#include "cocos2d.h"
#include "CCISOTileLayer.h"

NS_CC_BEGIN

class CCISOTilesetInfo : public CCObject{

public:
    
    CCISOTilesetInfo();
    ~CCISOTilesetInfo();
    CCRect rectForGID(unsigned int gid);

public:
    std::string        m_sName;
    unsigned int    m_uFirstGid;
    CCSize            m_tTileSize;
    unsigned int    m_uSpacing;
    unsigned int    m_uMargin;
    //! filename containing the tiles (should be spritesheet / texture atlas)
    std::string        m_sSourceImage;
    //! size in pixels of the image
    CCSize            m_tImageSize;
};


NS_CC_END

#endif //ISO_CCISOTilesetInfo_H_

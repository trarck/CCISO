#include "CCISOCoordinate.h"
#include "CCISOTileset.h"


NS_CC_BEGIN

CCISOTileset::CCISOTileset()
:m_sName("")
,m_sFileName("")
,m_sImageSource("")
,m_nTileWidth(0)
,m_nTileHeight(0)
,m_nTileSpacing(0)
,m_nMargin(0)
,m_tTileOffset(CCPointZero)
//,m_nImageWidth(0)
//,m_nImageHeight(0)
,m_tImageSize(CCSizeZero)
,m_nColumnCount(0)
,m_pTiles(NULL)
,m_uFirstGid(0)
,m_uLastGid(0)
{
    
}

CCISOTileset::~CCISOTileset()
{
    CCLOG("CCISOTileset destroy");
}

//void CCISOTileset::cleanImageSourceTiles()
//{
//    if(!m_sImageSource.empty()){
//        int column=columnCountForWidth(m_tImageSize.width);
//        int row=rowCountForHeight(m_tImageSize.height);
//        
//        int imageTileCount=row*column;
//        
//        if(m_pTiles->count()>imageTileCount){
//            int leftCount=m_pTiles->count()-imageTileCount;
//            //还有独立的tile定义.剩下的放入新的tiles里
//            CCArray* newTiles=new CCArray(leftCount);
//            CCObject* pObj;
//                                                            
//            for(CCObject** arr = m_pTiles->data->arr+imageTileCount, **end = m_pTiles->data->arr + m_pTiles->data->num-1;
//                arr <= end && ((pObj = *arr) != NULL/* || true*/);                                                
//                arr++){
//                newTiles->addObject(pObj);
//            }
//            setTiles(newTiles);
//            newTiles->release();
//        }else{
//            m_pTiles->removeAllObjects();
//        }
//    }
//}

void CCISOTileset::loadFromImageSource()
{
    if(!m_sImageSource.empty()){
        
        setTexture(CCTextureCache::sharedTextureCache()->addImage(m_sImageSource.c_str()));
        
        if(m_tImageSize.width==0 || m_tImageSize.height==0){
            m_tImageSize=m_pTexture->getContentSize();
        }
        
        int column=columnCountForWidth(m_tImageSize.width);
        int row=rowCountForHeight(m_tImageSize.height);
        
        int idx=0;
        int oldTilesSize=m_pTiles->count();
        for (int j=0; j<row; ++j) {
            for(int i=0;i<column;++i){
                CCISOTile* tile=new CCISOTile();
                tile->init(idx, this,tileSpriteForId(idx));
                if(idx<oldTilesSize){
                    m_pTiles->replaceObjectAtIndex(idx, tile);
                }else{
                    m_pTiles->addObject(tile);
                }
                tile->release();
                ++idx;
            }
        }
        m_uLastGid=lastGid();
    }
}

int CCISOTileset::columnCountForWidth(float width)
{
    CCAssert(m_nTileWidth > 0,"CCISOTileset::columnCountForWidth m_nTileWidth must big then 0");
    return (int)(width - m_nMargin + m_nTileSpacing) / (m_nTileWidth + m_nTileSpacing);
}

int CCISOTileset::rowCountForHeight(float height)
{
    CCAssert(m_nTileHeight > 0,"CCISOTileset::columnRowForHeight m_nTileHeight must big then 0");
    return (int)(height - m_nMargin + m_nTileSpacing) / (m_nTileHeight + m_nTileSpacing);
}

CCRect CCISOTileset::rectForId(unsigned int id)
{
    CCRect rect;
    rect.size = CCSizeMake(m_nTileWidth, m_nTileHeight);
    int max_x = (int)((m_tImageSize.width - m_nMargin*2 + m_nTileSpacing) / (m_tImageSize.width + m_nTileSpacing));
    rect.origin.x = (id % max_x) * (m_nTileWidth + m_nTileSpacing) + m_nMargin;
    rect.origin.y = (id / max_x) * (m_nTileHeight + m_nTileSpacing) + m_nMargin;
    return rect;
}

CCSprite* CCISOTileset::tileSpriteForId(unsigned int id)
{
    CCSprite* sprite=new CCSprite();
    CCRect rect=rectForId(id);
    sprite->initWithTexture(m_pTexture,rect);
    sprite->autorelease();
    
    return sprite;
}

CCISOTile* CCISOTileset::tileForId(unsigned int id)
{
    return (CCISOTile*)m_pTiles->objectAtIndex(id);
//    //dynamic
//       CCSprite* sprite=tileSpriteForId(id);
//    CCISOTile* tile=new CCISOTile();
//    tile->init(id, this, sprite);
//    tile->autorelease();
//    return tile;
}

unsigned int CCISOTileset::lastGid()
{
    return m_uFirstGid+m_pTiles->count()-1;
//    CCAssert(m_tImageSize.width>0 && m_tImageSize.height>0, "CCISOTileset::lastGid the image size shuold not 0");
//    int column=columnCountForWidth(m_tImageSize.width);
//    int row=rowCountForHeight(m_tImageSize.height);
//    CCAssert(column*row>0, "CCISOTileset::lastGid column*row must big then 0");
//    return m_uFirstGid+(column*row-1);
}

bool CCISOTileset::contains(unsigned int gid)
{
    return m_uFirstGid<=gid && m_uLastGid>=gid;
}

CCRect CCISOTileset::rectForGid(unsigned int gid)
{
    return rectForId(gid - m_uFirstGid);
}

CCSprite* CCISOTileset::tileSpriteForGid(unsigned int gid)
{
    return tileSpriteForGid(gid - m_uFirstGid);
}

CCISOTile* CCISOTileset::tileForGid(unsigned int gid)
{
    return tileForId(gid - m_uFirstGid);
}

void CCISOTileset::appendTile(const char* imageName)
{
    CCSprite* sprite=CCSprite::create(imageName);
    appendTile(sprite);
}

void CCISOTileset::appendTile(CCSprite* sprite)
{
    CCISOTile* tile=new CCISOTile();
    tile->init(tileCount(), this, sprite);
    m_pTiles->addObject(tile);
    tile->release();
    
    m_uLastGid=lastGid();
}

void CCISOTileset::setTile(unsigned int id,const char* imageName)
{
    CCSprite* sprite=CCSprite::create(imageName);
    setTile(id, sprite);
}

void CCISOTileset::setTile(unsigned int id,CCSprite* sprite)
{
    CCISOTile* tile=(CCISOTile*)m_pTiles->objectAtIndex(id);
    if(tile){
        tile->setSprite(sprite);
    }else{
        CCISOTile* tile=new CCISOTile();
        tile->init(id, this, sprite);
        m_pTiles->replaceObjectAtIndex(id, tile);
        tile->release();
    }
}

void CCISOTileset::addTile(unsigned int id,const char* imageName)
{
    CCSprite* sprite=CCSprite::create(imageName);
    addTile(id, sprite);
}

void CCISOTileset::addTile(unsigned int id,CCSprite* sprite)
{
    //如果index大于tile count，则中间插入空的
    unsigned int tileCount=this->tileCount();
    if(id<tileCount){
        //replace
        setTile(id, sprite);
    }else if(id==tileCount){
        appendTile(sprite);
    }else{
        //补充空的tile
        unsigned int padCount=id-tileCount;
        for(int i=0;i<padCount;++i){
            m_pTiles->addObject(NULL);
        }
        //增加新的tile
        appendTile(sprite);
    }
}

void CCISOTileset::addTile(CCISOTile* tile)
{
    //如果index大于tile count，则中间插入空的
    unsigned int tileCount=this->tileCount();
    unsigned int id=tile->getId();
    if(id<tileCount){
        //replace
        m_pTiles->replaceObjectAtIndex(id, tile);
    }else if(id==tileCount){
        m_pTiles->addObject(tile);
    }else{
        //补充空的tile
        unsigned int padCount=id-tileCount;
        for(int i=0;i<padCount;++i){
            m_pTiles->addObject(NULL);
        }
        //增加新的tile
        m_pTiles->addObject(tile);
    }
}


void CCISOTileset::setFileName(const char* pFileName)
{
    m_sFileName = pFileName;
}

std::string& CCISOTileset::getFileName()
{
    return m_sFileName;
}

void CCISOTileset::setImageSource(const char* pImageSource)
{
    m_sImageSource = pImageSource;    
}

std::string& CCISOTileset::getImageSource()
{
    return m_sImageSource;
}

void CCISOTileset::setTileWidth(int nTileWidth)
{
    m_nTileWidth = nTileWidth;
}

int CCISOTileset::getTileWidth()
{
    return m_nTileWidth;
}

void CCISOTileset::setTileHeight(int nTileHeight)
{
    m_nTileHeight = nTileHeight;
}

int CCISOTileset::getTileHeight()
{
    return m_nTileHeight;
}

void CCISOTileset::setTileSpacing(int nTileSpacing)
{
    m_nTileSpacing = nTileSpacing;
}

int CCISOTileset::getTileSpacing()
{
    return m_nTileSpacing;
}

void CCISOTileset::setMargin(int nMargin)
{
    m_nMargin = nMargin;
}

int CCISOTileset::getMargin()
{
    return m_nMargin;
}

void CCISOTileset::setTileOffset(CCPoint tTileOffset)
{
    m_tTileOffset = tTileOffset;
}

CCPoint CCISOTileset::getTileOffset()
{
    return m_tTileOffset;
}

//void CCISOTileset::setImageWidth(int nImageWidth)
//{
//    m_nImageWidth = nImageWidth;
//}
//
//int CCISOTileset::getImageWidth()
//{
//    return m_nImageWidth;
//}
//
//void CCISOTileset::setImageHeight(int nImageHeight)
//{
//    m_nImageHeight = nImageHeight;
//}
//
//int CCISOTileset::getImageHeight()
//{
//    return m_nImageHeight;
//}

void CCISOTileset::setColumnCount(int nColumnCount)
{
    m_nColumnCount = nColumnCount;
}

int CCISOTileset::getColumnCount()
{
    return m_nColumnCount;
}

void CCISOTileset::setTiles(CCArray* pTiles)
{
    CC_SAFE_RETAIN(pTiles);
    CC_SAFE_RELEASE(m_pTiles);
    m_pTiles = pTiles;
}

CCArray* CCISOTileset::getTiles()
{
    return m_pTiles;
}

void CCISOTileset::setFirstGid(unsigned int uFirstGid)
{
    m_uFirstGid = uFirstGid;
}

unsigned int CCISOTileset::getFirstGid()
{
    return m_uFirstGid;
}

unsigned int CCISOTileset::getLastGid()
{
    return this->m_uLastGid;
}

void CCISOTileset::setLastGid(unsigned int gid)
{
    this->m_uLastGid=gid;
}

void CCISOTileset::setTileProperties(CCDictionary* pTileProperties)
{
    m_pTileProperties=pTileProperties;
}

CCDictionary* CCISOTileset::getTileProperties()
{
    return m_pTileProperties;
}

void CCISOTileset::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* CCISOTileset::getProperties()
{
    return m_pProperties;
}

NS_CC_END

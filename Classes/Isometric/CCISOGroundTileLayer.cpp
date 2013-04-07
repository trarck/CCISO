#include "CCISOCoordinate.h"
#include "CCISOGroundTileLayer.h"
#include "sprite_nodes/CCSprite.h"
#include "textures/CCTextureCache.h"
#include "shaders/CCShaderCache.h"
#include "shaders/CCGLProgram.h"
#include "support/CCPointExtension.h"
#include "support/data_support/ccCArray.h"
#include "support/CCNotificationCenter.h"
#include "CCEventType.h"
#include "CCDirector.h"
#include "CCISOTileMap.h"

NS_CC_BEGIN

// CCISOGroundTileLayer - atlasIndex and Z
static inline int compareInts(const void * a, const void * b)
{
    return ((*(int*)a) - (*(int*)b));
}


CCISOGroundTileLayer::CCISOGroundTileLayer()
:m_pTiles(NULL)
{
	
}

CCISOGroundTileLayer::~CCISOGroundTileLayer()
{
    CC_SAFE_RELEASE(m_pProperties);
    
    CC_SAFE_DELETE_ARRAY(m_pTiles);
}

bool CCISOGroundTileLayer::init(CCISOTileMap *pMap)
{
    setMap(pMap);
    return true;
}



void CCISOGroundTileLayer::releaseLayer()
{
    if (m_pTiles)
    {
        delete [] m_pTiles;
        m_pTiles = NULL;
    }
    
    CCISOTileLayer::releaseLayer();
}

void CCISOGroundTileLayer::setupTiles()
{
    // Parse cocos2d properties
    this->parseInternalProperties();
    
    for (unsigned int y=0; y < m_tLayerSize.height; y++)
    {
        for (unsigned int x=0; x < m_tLayerSize.width; x++)
        {
            unsigned int pos = (unsigned int)(x + m_tLayerSize.width * y);
            unsigned int gid = m_pTiles[ pos ];
            
            // gid are stored in little endian.
            // if host is big endian, then swap
            //if( o == CFByteOrderBigEndian )
            //    gid = CFSwapInt32( gid );
            /* We support little endian.*/
            
            // XXX: gid == 0 --> empty tile
            if (gid != 0)
            {
                this->appendTileForGID(gid, ccp(x, y));
                
                // Optimization: update min and max GID rendered by the layer
                m_uMinGID = MIN(gid, m_uMinGID);
                m_uMaxGID = MAX(gid, m_uMaxGID);
            }
        }
    }
}

void CCISOGroundTileLayer::setupTileSprite(CCSprite* sprite, CCPoint mapCoord, unsigned int gid)
{
    sprite->setPosition(isoGameToViewPoint(mapCoord));
    sprite->setVertexZ((float)this->vertexZForPos(mapCoord));
    sprite->setAnchorPoint(CCPointZero);
    sprite->setOpacity(m_cOpacity);
    
    sprite->setFlipX(false);
    sprite->setFlipX(false);
    sprite->setRotation(0.0f);
    sprite->setAnchorPoint(ccp(0,0));
    
    // Rotation in tiled is achieved using 3 flipped states, flipping across the horizontal, vertical, and diagonal axes of the tiles.
    if (gid & kCCTMXTileDiagonalFlag)
    {
        // put the anchor in the middle for ease of rotation.
        sprite->setAnchorPoint(ccp(0.5f,0.5f));
        CCPoint viewPos=isoGameToViewPoint(mapCoord);
        sprite->setPosition(ccp(viewPos.x + sprite->getContentSize().height/2,
                                viewPos.y + sprite->getContentSize().width/2 ) );
        
        unsigned int flag = gid & (kCCTMXTileHorizontalFlag | kCCTMXTileVerticalFlag );
        
        // handle the 4 diagonally flipped states.
        if (flag == kCCTMXTileHorizontalFlag)
        {
            sprite->setRotation(90.0f);
        }
        else if (flag == kCCTMXTileVerticalFlag)
        {
            sprite->setRotation(270.0f);
        }
        else if (flag == (kCCTMXTileVerticalFlag | kCCTMXTileHorizontalFlag) )
        {
            sprite->setRotation(90.0f);
            sprite->setFlipX(true);
        }
        else
        {
            sprite->setRotation(270.0f);
            sprite->setFlipX(true);
        }
    }
    else
    {
        if (gid & kCCTMXTileHorizontalFlag)
        {
            sprite->setFlipX(true);
        }
        
        if (gid & kCCTMXTileVerticalFlag)
        {
            sprite->setFlipY(true);
        }
    }
}


CCSprite * CCISOGroundTileLayer::tileAt(const CCPoint& pos)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "ISOTileLayer: invalid position");
    
    CCSprite *tile = NULL;
    unsigned int gid = this->tileGIDAt(pos);
    
    // if GID == 0, then no tile is present
    if (gid)
    {
        int z = (int)(pos.x + pos.y * m_tLayerSize.width);
        tile = (CCSprite*) this->getChildByTag(z);
        
        // tile not created yet. create it
        if (! tile)
        {
            CCISOTileset* tileset=m_pMap->getTilesetGroup()->getTilesetByGid(gid);
            tile = tileset->tileSpriteForGid(gid);
            tile->setPosition(isoGameToViewPoint(pos));
            tile->setVertexZ((float)vertexZForPos(pos));
            tile->setAnchorPoint(CCPointZero);
            tile->setOpacity(m_cOpacity);
            
            this->addChild(tile);
        }
    }
    
    return tile;
}

CCSprite* CCISOGroundTileLayer::tileAt(float x,float y)
{
    return tileAt(ccp(x,y));
}

unsigned int CCISOGroundTileLayer::tileGIDAt(const CCPoint& pos)
{
    return tileGIDAt(pos, NULL);
}

unsigned int CCISOGroundTileLayer::tileGIDAt(const CCPoint& pos, ccTMXTileFlags* flags)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    
    int idx = (int)(pos.x + pos.y * m_tLayerSize.width);
    // Bits on the far end of the 32-bit global tile ID are used for tile flags
    unsigned int tile = m_pTiles[idx];
    
    // issue1264, flipped tiles can be changed dynamically
    if (flags)
    {
        *flags = (ccTMXTileFlags)(tile & kCCFlipedAll);
    }
    
    return (tile & kCCFlippedMask);
}

// CCISOGroundTileLayer - adding helper methods
CCSprite * CCISOGroundTileLayer::insertTileForGID(unsigned int gid, const CCPoint& pos)
{
    CCISOTileset* tileset=m_pMap->getTilesetGroup()->getTilesetByGid(gid);
    CCSprite *tile = tileset->tileSpriteForGid(gid);
    
    intptr_t z = (intptr_t)(pos.x + pos.y * m_tLayerSize.width);
    
    setupTileSprite(tile, pos, gid);
    
    addChild(tile,0,z);
    return tile;
}

CCSprite * CCISOGroundTileLayer::updateTileForGID(unsigned int gid, const CCPoint& pos)
{
    int z = (int)(pos.x + pos.y * m_tLayerSize.width);

    this->removeChildByTag(z, true);
  
    CCISOTileset* tileset=m_pMap->getTilesetGroup()->getTilesetByGid(gid);
    CCSprite *newTile = tileset->tileSpriteForGid(gid);
    
    setupTileSprite(newTile ,pos ,gid);

    addChild(newTile,0,z);
    
    m_pTiles[z] = gid;
    
    return newTile;
}

// used only when parsing the map. useless after the map was parsed
// since lot's of assumptions are no longer true
CCSprite * CCISOGroundTileLayer::appendTileForGID(unsigned int gid, const CCPoint& pos)
{
    int z = (int)(pos.x + pos.y * m_tLayerSize.width);
    
    CCISOTileset* tileset=m_pMap->getTilesetGroup()->getTilesetByGid(gid);
    
    CCISOTile* tile=tileset->tileForGid(gid);    
    
    CCSprite *tileSprite = tile->getSprite();
    
    setupTileSprite(tileSprite ,pos ,gid);
 
    addChild(tileSprite,0,z);
    
    return tileSprite;
}


// CCISOGroundTileLayer - adding / remove tiles
void CCISOGroundTileLayer::setTileGID(unsigned int gid, const CCPoint& pos)
{
    setTileGID(gid, pos, (ccTMXTileFlags)0);
}

void CCISOGroundTileLayer::setTileGID(unsigned int gid, float x,float y)
{
    setTileGID(gid, x,y, (ccTMXTileFlags)0);
}

void CCISOGroundTileLayer::setTileGID(unsigned int gid, float x,float y, ccTMXTileFlags flags)
{
    setTileGID(gid, ccp(x,y), flags);
}

void CCISOGroundTileLayer::setTileGID(unsigned int gid, const CCPoint& pos, ccTMXTileFlags flags)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
   
}



void CCISOGroundTileLayer::removeTileAt(float x,float y)
{
    removeTileAt(ccp(x,y));
}

void CCISOGroundTileLayer::removeTileAt(const CCPoint& pos)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    
    unsigned int gid = tileGIDAt(pos);
    
    if (gid)
    {
        unsigned int z = (unsigned int)(pos.x + pos.y * m_tLayerSize.width);
        
        // remove tile from GID map
        m_pTiles[z] = 0;
        removeChildByTag(z, true);
        
    }
}


void CCISOGroundTileLayer::setTiles(unsigned int* pTiles)
{
    m_pTiles = pTiles;
}

unsigned int* CCISOGroundTileLayer::getTiles()
{
    return m_pTiles;
}

NS_CC_END

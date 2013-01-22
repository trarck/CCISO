#include "CCISOCoordinate.h"
#include "CCISOTileSimpleGroundLayer.h"

NS_CC_BEGIN

// CCISOTileSimpleGroundLayer - atlasIndex and Z
static inline int compareInts(const void * a, const void * b)
{
    return ((*(int*)a) - (*(int*)b));
}


CCISOTileSimpleGroundLayer * CCISOTileSimpleGroundLayer::layerWithTilesetInfo(CCISOTilesetInfo *tilesetInfo, CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo)
{
    return CCISOTileSimpleGroundLayer::create(tilesetInfo, layerInfo, mapInfo);
}

CCISOTileSimpleGroundLayer * CCISOTileSimpleGroundLayer::create(CCISOTilesetInfo *tilesetInfo, CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo)
{
    CCISOTileSimpleGroundLayer *pRet = new CCISOTileSimpleGroundLayer();
    if (pRet->init(tilesetInfo, layerInfo, mapInfo))
    {
        pRet->autorelease();
        return pRet;
    }
    return NULL;
}

CCISOTileSimpleGroundLayer::CCISOTileSimpleGroundLayer()
:m_iStartX(0)
,m_iStartY(0)
,m_tLayerSize(CCSizeZero)
,m_tMapTileSize(CCSizeZero)
,m_pTiles(NULL)
,m_pTileSet(NULL)
,m_pProperties(NULL)
,m_sLayerName("")
,m_pReusedTile(NULL)
,m_pSpriteBatchNode(NULL)
,m_pAtlasIndexArray(NULL)
{
	
}

CCISOTileSimpleGroundLayer::~CCISOTileSimpleGroundLayer()
{
    CC_SAFE_RELEASE(m_pTileSet);
    CC_SAFE_RELEASE(m_pReusedTile);
    CC_SAFE_RELEASE(m_pProperties);
    CC_SAFE_RELEASE(m_pSpriteBatchNode);
//    if (m_pAtlasIndexArray)
//    {
//        ccCArrayFree(m_pAtlasIndexArray);
//        m_pAtlasIndexArray = NULL;
//    }
    
    CC_SAFE_DELETE_ARRAY(m_pTiles);
}

bool CCISOTileSimpleGroundLayer::init()
{
    m_tTileSize=CCSizeZero;
	m_tOffset=CCPointZero;
    
	return true;
}

bool CCISOTileSimpleGroundLayer::init(CCISOTilesetInfo *tilesetInfo, CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo)
{
    m_pSpriteBatchNode=new CCSpriteBatchNode();
    // XXX: is 35% a good estimate ?
    CCSize size = layerInfo->m_tLayerSize;
    float totalNumberOfTiles = size.width * size.height;
    float capacity = totalNumberOfTiles * 0.35f + 1; // 35 percent is occupied ?
    
    CCTexture2D *texture = NULL;
    if( tilesetInfo )
    {
        texture = CCTextureCache::sharedTextureCache()->addImage(tilesetInfo->m_sSourceImage.c_str());
    }
    
    if (m_pSpriteBatchNode->initWithTexture(texture, (unsigned int)capacity))
    {
        // layerInfo
        m_sLayerName = layerInfo->m_sName;
        m_tLayerSize = size;
        m_pTiles = layerInfo->m_pTiles;
        m_uMinGID = layerInfo->m_uMinGID;
        m_uMaxGID = layerInfo->m_uMaxGID;
        m_cOpacity = layerInfo->m_cOpacity;
        this->initOffset(layerInfo->m_tOffset);
        
        setProperties(CCDictionary::createWithDictionary(layerInfo->getProperties()));
        m_fContentScaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();
        
        // tilesetInfo
        m_pTileSet = tilesetInfo;
        CC_SAFE_RETAIN(m_pTileSet);
        
        // mapInfo
        m_tMapTileSize = mapInfo->getTileSize();
        m_uLayerOrientation = mapInfo->getOrientation();
        
        
        m_pAtlasIndexArray = ccCArrayNew((unsigned int)totalNumberOfTiles);
        
        this->setContentSize(CCSizeMake(m_tLayerSize.width * m_tMapTileSize.width, m_tLayerSize.height * m_tMapTileSize.height));
        
        m_bUseAutomaticVertexZ = false;
        m_nVertexZvalue = 0;
        
        return true;
    }
    return false;
}


void CCISOTileSimpleGroundLayer::initOffset(const CCPoint& tOffset)
{
//    this->setPosition(tOffset);
	this->setOffset(tOffset);
	CCPoint startMapCoord=isoViewToGamePoint(tOffset);
	m_iStartX=(int)startMapCoord.x;
	m_iStartY=(int)startMapCoord.y;
}

void CCISOTileSimpleGroundLayer::initOffset(float x,float y)
{
	this->initOffset(ccp(x,y));
}


void CCISOTileSimpleGroundLayer::releaseMap()
{
    if (m_pTiles)
    {
        delete [] m_pTiles;
        m_pTiles = NULL;
    }
    
    if (m_pAtlasIndexArray)
    {
        ccCArrayFree(m_pAtlasIndexArray);
        m_pAtlasIndexArray = NULL;
    }
}

void CCISOTileSimpleGroundLayer::setupTiles()
{
    // Optimization: quick hack that sets the image size on the tileset
    m_pTileSet->m_tImageSize = m_pSpriteBatchNode->getTextureAtlas()->getTexture()->getContentSizeInPixels();
    
    // By default all the tiles are aliased
    // pros:
    //  - easier to render
    // cons:
    //  - difficult to scale / rotate / etc.
    m_pSpriteBatchNode->getTextureAtlas()->getTexture()->setAliasTexParameters();
    
    //CFByteOrder o = CFByteOrderGetCurrent();
    
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
    
    CCAssert( m_uMaxGID >= m_pTileSet->m_uFirstGid &&
             m_uMinGID >= m_pTileSet->m_uFirstGid, "TMX: Only 1 tileset per layer is supported");
}

void CCISOTileSimpleGroundLayer::setupTileSprite(CCSprite* sprite, CCPoint mapCoord, unsigned int gid)
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

CCSprite* CCISOTileSimpleGroundLayer::reusedTileWithRect(CCRect rect)
{
    if (! m_pReusedTile)
    {
        m_pReusedTile = new CCSprite();
        m_pReusedTile->initWithTexture(m_pSpriteBatchNode->getTextureAtlas()->getTexture(), rect, false);
        m_pReusedTile->setBatchNode(m_pSpriteBatchNode);
    }
    else
    {
        // XXX: should not be re-init. Potential memory leak. Not following best practices
        // XXX: it shall call directory  [setRect:rect]
        m_pReusedTile->initWithTexture(m_pSpriteBatchNode->getTextureAtlas()->getTexture(), rect, false);
        
        // Since initWithTexture resets the batchNode, we need to re add it.
        // but should be removed once initWithTexture is not called again
        m_pReusedTile->setBatchNode(m_pSpriteBatchNode);
    }
    
    return m_pReusedTile;
}


CCSprite * CCISOTileSimpleGroundLayer::tileAt(const CCPoint& pos)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "ISOTileLayer: invalid position");
    CCAssert(m_pTiles && m_pAtlasIndexArray, "ISOTileLayer: the tiles map has been released");
    
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
            CCRect rect = m_pTileSet->rectForGID(gid);
//            rect = CC_RECT_PIXELS_TO_POINTS(rect);
            
            tile = new CCSprite();
            tile->initWithTexture(m_pSpriteBatchNode->getTexture(), rect);
            tile->setBatchNode(m_pSpriteBatchNode);
            tile->setPosition(isoGameToViewPoint(pos));
            tile->setVertexZ((float)vertexZForPos(pos));
            tile->setAnchorPoint(CCPointZero);
            tile->setOpacity(m_cOpacity);
            
            unsigned int indexForZ = this->atlasIndexForExistantZ(z);
            this->addSpriteWithoutQuad(tile, indexForZ, z);
            tile->release();
        }
    }
    
    return tile;
}

CCSprite* CCISOTileSimpleGroundLayer::tileAt(float x,float y)
{
    return tileAt(ccp(x,y));
}

unsigned int CCISOTileSimpleGroundLayer::tileGIDAt(const CCPoint& pos)
{
    return tileGIDAt(pos, NULL);
}

unsigned int CCISOTileSimpleGroundLayer::tileGIDAt(const CCPoint& pos, ccTMXTileFlags* flags)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCAssert(m_pTiles && m_pAtlasIndexArray, "TMXLayer: the tiles map has been released");
    
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

// CCISOTileSimpleGroundLayer - adding helper methods
CCSprite * CCISOTileSimpleGroundLayer::insertTileForGID(unsigned int gid, const CCPoint& pos)
{
    CCRect rect = m_pTileSet->rectForGID(gid);
//    rect = CC_RECT_PIXELS_TO_POINTS(rect);
    
    intptr_t z = (intptr_t)(pos.x + pos.y * m_tLayerSize.width);
    
    CCSprite *tile = reusedTileWithRect(rect);
    
    setupTileSprite(tile, pos, gid);
    
    // get atlas index
    unsigned int indexForZ = this->atlasIndexForNewZ(z);
    
    // Optimization: add the quad without adding a child
    this->addQuadFromSprite(tile, indexForZ);
    
    // insert it into the local atlasindex array
    ccCArrayInsertValueAtIndex(m_pAtlasIndexArray, (void*)z, indexForZ);
    
    // update possible children
    CCArray* pChildren=m_pSpriteBatchNode->getChildren();
    if (pChildren && pChildren->count()>0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(pChildren, pObject)
        {
            CCSprite* pChild = (CCSprite*) pObject;
            if (pChild)
            {
                unsigned int ai = pChild->getAtlasIndex();
                if ( ai >= indexForZ )
                {
                    pChild->setAtlasIndex(ai+1);
                }
            }
        }
    }
    m_pTiles[z] = gid;
    return tile;
}

CCSprite * CCISOTileSimpleGroundLayer::updateTileForGID(unsigned int gid, const CCPoint& pos)
{
    CCRect rect = m_pTileSet->rectForGID(gid);
    rect = CCRectMake(rect.origin.x / m_fContentScaleFactor, rect.origin.y / m_fContentScaleFactor, rect.size.width/ m_fContentScaleFactor, rect.size.height/ m_fContentScaleFactor);
    int z = (int)(pos.x + pos.y * m_tLayerSize.width);
    
    CCSprite *tile = reusedTileWithRect(rect);
    
    setupTileSprite(tile ,pos ,gid);
    
    // get atlas index
    unsigned int indexForZ = atlasIndexForExistantZ(z);
    tile->setAtlasIndex(indexForZ);
    tile->setDirty(true);
    tile->updateTransform();
    m_pTiles[z] = gid;
    
    return tile;
}

// used only when parsing the map. useless after the map was parsed
// since lot's of assumptions are no longer true
CCSprite * CCISOTileSimpleGroundLayer::appendTileForGID(unsigned int gid, const CCPoint& pos)
{
    CCRect rect = m_pTileSet->rectForGID(gid);
//    rect = CC_RECT_PIXELS_TO_POINTS(rect);
    
    intptr_t z = (intptr_t)(pos.x + pos.y * m_tLayerSize.width);
    
    CCSprite *tile = reusedTileWithRect(rect);
    
    setupTileSprite(tile ,pos ,gid);
    
    // optimization:
    // The difference between appendTileForGID and insertTileforGID is that append is faster, since
    // it appends the tile at the end of the texture atlas
    unsigned int indexForZ = m_pAtlasIndexArray->num;
    
    // don't add it using the "standard" way.
    addQuadFromSprite(tile, indexForZ);
    
    // append should be after addQuadFromSprite since it modifies the quantity values
    ccCArrayInsertValueAtIndex(m_pAtlasIndexArray, (void*)z, indexForZ);
    
    return tile;
}


unsigned int CCISOTileSimpleGroundLayer::atlasIndexForExistantZ(unsigned int z)
{
    int key=z;
    int *item = (int*)bsearch((void*)&key, (void*)&m_pAtlasIndexArray->arr[0], m_pAtlasIndexArray->num, sizeof(void*), compareInts);
    
    CCAssert(item, "TMX atlas index not found. Shall not happen");
    
    int index = ((size_t)item - (size_t)m_pAtlasIndexArray->arr) / sizeof(void*);
    return index;
}
unsigned int CCISOTileSimpleGroundLayer::atlasIndexForNewZ(int z)
{
    // XXX: This can be improved with a sort of binary search
    unsigned int i=0;
    for (i=0; i< m_pAtlasIndexArray->num ; i++)
    {
        int val = (size_t) m_pAtlasIndexArray->arr[i];
        if (z < val)
        {
            break;
        }
    }
    
    return i;
}

// CCISOTileSimpleGroundLayer - adding / remove tiles
void CCISOTileSimpleGroundLayer::setTileGID(unsigned int gid, const CCPoint& pos)
{
    setTileGID(gid, pos, (ccTMXTileFlags)0);
}

void CCISOTileSimpleGroundLayer::setTileGID(unsigned int gid, float x,float y)
{
    setTileGID(gid, x,y, (ccTMXTileFlags)0);
}

void CCISOTileSimpleGroundLayer::setTileGID(unsigned int gid, float x,float y, ccTMXTileFlags flags)
{
    setTileGID(gid, ccp(x,y), flags);
}

void CCISOTileSimpleGroundLayer::setTileGID(unsigned int gid, const CCPoint& pos, ccTMXTileFlags flags)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCAssert(m_pTiles && m_pAtlasIndexArray, "TMXLayer: the tiles map has been released");
    CCAssert(gid == 0 || gid >= m_pTileSet->m_uFirstGid, "TMXLayer: invalid gid" );
    
    ccTMXTileFlags currentFlags;
    unsigned int currentGID = tileGIDAt(pos, &currentFlags);
    
    if (currentGID != gid || currentFlags != flags)
    {
        unsigned gidAndFlags = gid | flags;
        
        // setting gid=0 is equal to remove the tile
        if (gid == 0)
        {
            removeTileAt(pos);
        }
        // empty tile. create a new one
        else if (currentGID == 0)
        {
            insertTileForGID(gidAndFlags, pos);
        }
        // modifying an existing tile with a non-empty tile
        else
        {
            unsigned int z = (unsigned int)(pos.x + pos.y * m_tLayerSize.width);
            CCSprite *sprite = (CCSprite*)m_pSpriteBatchNode->getChildByTag(z);
            if (sprite)
            {
                CCRect rect = m_pTileSet->rectForGID(gid);
                rect = CC_RECT_PIXELS_TO_POINTS(rect);
                
                sprite->setTextureRect(rect, false, rect.size);
                if (flags)
                {
                    setupTileSprite(sprite, sprite->getPosition(), gidAndFlags);
                }
                m_pTiles[z] = gidAndFlags;
            }
            else
            {
                updateTileForGID(gidAndFlags, pos);
            }
        }
    }
}


void CCISOTileSimpleGroundLayer::removeChild(CCNode* node, bool cleanup)
{
    CCSprite *sprite = (CCSprite*)node;
    // allows removing nil objects
    if (! sprite)
    {
        return;
    }
    
    CCAssert(m_pSpriteBatchNode->getChildren()->containsObject(sprite), "Tile does not belong to TMXLayer");
    
    unsigned int atlasIndex = sprite->getAtlasIndex();
    unsigned int zz = (size_t)m_pAtlasIndexArray->arr[atlasIndex];
    m_pTiles[zz] = 0;
    ccCArrayRemoveValueAtIndex(m_pAtlasIndexArray, atlasIndex);
    m_pSpriteBatchNode->removeChild(sprite, cleanup);
}

void CCISOTileSimpleGroundLayer::removeTileAt(float x,float y)
{
    removeTileAt(ccp(x,y));
}

void CCISOTileSimpleGroundLayer::removeTileAt(const CCPoint& pos)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCAssert(m_pTiles && m_pAtlasIndexArray, "TMXLayer: the tiles map has been released");
    
    unsigned int gid = tileGIDAt(pos);
    
    if (gid)
    {
        unsigned int z = (unsigned int)(pos.x + pos.y * m_tLayerSize.width);
        unsigned int atlasIndex = atlasIndexForExistantZ(z);
        
        // remove tile from GID map
        m_pTiles[z] = 0;
        
        // remove tile from atlas position array
        ccCArrayRemoveValueAtIndex(m_pAtlasIndexArray, atlasIndex);
        
        // remove it from sprites and/or texture atlas
        CCSprite *sprite = (CCSprite*)getChildByTag(z);
        if (sprite)
        {
            m_pSpriteBatchNode->removeChild(sprite, true);
        }
        else
        {
            m_pSpriteBatchNode->getTextureAtlas()->removeQuadAtIndex(atlasIndex);
            
            // update possible children
            CCArray* pChildren=m_pSpriteBatchNode->getChildren();
            if (pChildren && pChildren->count()>0)
            {
                CCObject* pObject = NULL;
                CCARRAY_FOREACH(pChildren, pObject)
                {
                    CCSprite* pChild = (CCSprite*) pObject;
                    if (pChild)
                    {
                        unsigned int ai = pChild->getAtlasIndex();
                        if ( ai >= atlasIndex )
                        {
                            pChild->setAtlasIndex(ai-1);
                        }
                    }
                }
            }
        }
    }
}




void CCISOTileSimpleGroundLayer::addQuadFromSprite(CCSprite *sprite, unsigned int index)
{
    CCAssert( sprite != NULL, "Argument must be non-NULL");
    CCAssert( dynamic_cast<CCSprite*>(sprite), "CCSpriteBatchNode only supports CCSprites as children");
    
    CCTextureAtlas* pobTextureAtlas=m_pSpriteBatchNode->getTextureAtlas();
    
    while(index >= pobTextureAtlas->getCapacity() || pobTextureAtlas->getCapacity() == pobTextureAtlas->getTotalQuads())
    {
        m_pSpriteBatchNode->increaseAtlasCapacity();
    }
    //
    // update the quad directly. Don't add the sprite to the scene graph
    //
    sprite->setBatchNode(m_pSpriteBatchNode);
    sprite->setAtlasIndex(index);
    
    ccV3F_C4B_T2F_Quad quad = sprite->getQuad();
    pobTextureAtlas->insertQuad(&quad, index);
    
    // XXX: updateTransform will update the textureAtlas too using updateQuad.
    // XXX: so, it should be AFTER the insertQuad
    sprite->setDirty(true);
    sprite->updateTransform();
}


void CCISOTileSimpleGroundLayer::addSpriteWithoutQuad(CCSprite*child, unsigned int z, int aTag)
{
    CCAssert( child != NULL, "Argument must be non-NULL");
    CCAssert( dynamic_cast<CCSprite*>(child), "CCSpriteBatchNode only supports CCSprites as children");
    
    // quad index is Z
    child->setAtlasIndex(z);
    
    // XXX: optimize with a binary search
    int i=0;
    
    CCArray* pobDescendants=m_pSpriteBatchNode->getDescendants();
    
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(pobDescendants, pObject)
    {
        CCSprite* pChild = (CCSprite*) pObject;
        if (pChild && (pChild->getAtlasIndex() >= z))
        {
            ++i;
        }
    }
    
    pobDescendants->insertObject(child, i);
    
    // IMPORTANT: Call super, and not self. Avoid adding it to the texture atlas array
    m_pSpriteBatchNode->addChild(child, z, aTag);
    //#issue 1262 don't use lazy sorting, tiles are added as quads not as sprites, so sprites need to be added in order
    m_pSpriteBatchNode->reorderBatch(false);
}

void CCISOTileSimpleGroundLayer::setTiles(unsigned int* pTiles)
{
    m_pTiles = pTiles;
}

unsigned int* CCISOTileSimpleGroundLayer::getTiles()
{
    return m_pTiles;
}

void CCISOTileSimpleGroundLayer::setTileSet(CCISOTilesetInfo* pTileSet)
{
    CC_SAFE_RETAIN(pTileSet);
    CC_SAFE_RELEASE(m_pTileSet);
    m_pTileSet = pTileSet;
}

CCISOTilesetInfo* CCISOTileSimpleGroundLayer::getTileSet()
{
    return m_pTileSet;
}

void CCISOTileSimpleGroundLayer::setTileSets(CCArray* pTileSets)
{
    CC_SAFE_RETAIN(pTileSets);
    CC_SAFE_RELEASE(m_pTileSets);
    m_pTileSets = pTileSets;
}

CCArray* CCISOTileSimpleGroundLayer::getTileSets()
{
    return m_pTileSets;
}

NS_CC_END

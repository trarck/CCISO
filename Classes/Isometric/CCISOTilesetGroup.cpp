#include "CCISOCoordinate.h"
#include "CCISOTilesetGroup.h"


NS_CC_BEGIN

CCISOTilesetGroup::CCISOTilesetGroup()
:m_pTilesets(NULL)
{

}

bool CCISOTilesetGroup::init()
{
    m_pTilesets=new CCArray();
    return true;
}

CCISOTilesetGroup::~CCISOTilesetGroup()
{
    CCLOG("CCISOTilesetGroup destroy");
    CC_SAFE_RELEASE(m_pTilesets);
}

void CCISOTilesetGroup::addTileset(CCISOTileset* tileset)
{
    m_pTilesets->addObject(tileset);
}

void CCISOTilesetGroup::insertTileset(int index,CCISOTileset* tileset)
{
    m_pTilesets->insertObject(tileset, index);
}

int CCISOTilesetGroup::indexOfTileset(CCISOTileset* tileset)
{
   return m_pTilesets->indexOfObject(tileset);
}

void CCISOTilesetGroup::removeTilesetAt(int index)
{
    m_pTilesets->removeObjectAtIndex(index);
}

void CCISOTilesetGroup::replaceTileset(CCISOTileset* oldTileset,CCISOTileset* newTileset)
{
    unsigned int index=m_pTilesets->indexOfObject(oldTileset);
    
    m_pTilesets->replaceObjectAtIndex(index, newTileset);
}


CCISOTileset* CCISOTilesetGroup::getTilesetByGid(unsigned int gid)
{
   
    CCISOTileset* tileset = NULL;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH_REVERSE(m_pTilesets, pObj)
    {
        tileset = (CCISOTileset*)pObj;
        if (tileset)
        {
            if(tileset->contains(gid)){
                return tileset;
            }
        }
    }
    return tileset;
}

NS_CC_END

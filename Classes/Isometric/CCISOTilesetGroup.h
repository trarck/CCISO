#ifndef ISO_CCISOTilesetGroup_H_
#define ISO_CCISOTilesetGroup_H_

#include "cocos2d.h"
#include "CCISOTileset.h"

NS_CC_BEGIN


class CCISOTilesetGroup : public CCObject{

public:
    
    CCISOTilesetGroup();
    
    ~CCISOTilesetGroup();
    
    bool init();
    
    void addTileset(CCISOTileset* tileset);
    
    void insertTileset(int index,CCISOTileset* tileset);
    
    int indexOfTileset(CCISOTileset* tileset);
    
    void removeTilesetAt(int index);
    
    void replaceTileset(CCISOTileset* oldTileset,CCISOTileset* newTileset);
    
    int tilesetCount(){return m_pTilesets->count();}
    
    CCISOTileset* getTilesetByIndex(int index){ return (CCISOTileset *)m_pTilesets->objectAtIndex(index); }
    
    CCISOTileset *tilesetAt(int index){ return (CCISOTileset *)m_pTilesets->objectAtIndex(index); }
    
    CCISOTileset* getTilesetByGid(unsigned int gid);
    
    CCArray* getTilesets(){return m_pTilesets;}

public:
    CCArray* m_pTilesets;
};


NS_CC_END

#endif //ISO_CCISOTilesetGroup_H_

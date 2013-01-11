#ifndef ISO_CCISOTileLayerDynamic_H_
#define ISO_CCISOTileLayerDynamic_H_

#include "cocos2d.h"
#include "CCISOTileLayer.h"

NS_CC_BEGIN


class CCISOTileLayerDynamic : public CCISOTileLayer {

public:
	
	CCISOTileLayerDynamic();
	~CCISOTileLayerDynamic(void);
	
    virtual bool init();

	virtual void setPosition(const CCPoint& newPosition);

//	bool beforeUpdateContent();
//	void doUpdateContent();

	int calcComponentTilesCount();
	void createComponentTiles();
	
    virtual void draw();
    
    virtual void setComponentTileColumn(int iComponentTileColumn);
    virtual int getComponentTileColumn();
    
    virtual void setComponentTileRow(int iComponentTileRow);
    virtual int getComponentTileRow();
    
    virtual void setComponenTileExtendCount(int iComponenTileExtendCount);
    virtual int getComponenTileExtendCount();


protected:
    int m_iComponentTileColumn;
    int m_iComponentTileRow;
    //x,y增加相同的格子数
    int m_iComponenTileExtendCount;
    
};



NS_CC_END

#endif //ISO_CCISOTileLayerDynamic_H_

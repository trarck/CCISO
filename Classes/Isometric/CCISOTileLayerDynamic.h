#ifndef ISO_CCISOTileLayerDynamic_H_
#define ISO_CCISOTileLayerDynamic_H_

#include "cocos2d.h"
#include "CCISOTileLayer"

NS_CC_BEGIN


class CCISOTileLayerDynamic : public CCISOTileLayer {

public:
	
	CCISOTileLayerDynamic();
	~CCISOTileLayerDynamic(void);
	
    virtual bool init();

	virtual void setPosition(const CCPoint& newPosition);

	bool beforeUpdateContent();
	void doUpdateContent();

	int calcComponentTilesCount();
	void createComponentTiles();
	
    virtual void draw();

protected:
    int 
};



NS_CC_END

#endif //ISO_CCISOTileLayerDynamic_H_

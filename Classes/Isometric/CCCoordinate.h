

#ifndef ISO_CCCoordinate_H_
#define ISO_CCCoordinate_H_

#include "cocos2d.h"

NS_CC_BEGIN

typedef struct {
	int x;
	int y;
} CCCell;

class CCCoordinate : public CCObject {

public:
    
    CCCoordinate();
    ~CCCoordinate(void);
    
	static CCCoordinate* sharedCoordinate();
	
    bool init();
    
	bool init(int width,int height);
	bool init(int xUnit,int yUnit,int zUnit);

	void setTileSize(int width ,int height);
	void setCoordinateUnit(int xUnit ,int yUnit ,int zUnit);
	void setCoordinateUnit(int xUnit ,int yUnit);

	CCPoint screenToMap(float x ,float y);
	CCPoint screenToMap(CCPoint point);
	CCPoint screenToMapGrid(float x ,float y);
	CCPoint screenToMapGrid(CCPoint point);
	CCCell screenToMapCell(float x ,float y);

	CCPoint mapToScreen(float x ,float y ,float z);
	CCPoint mapToScreen(float x ,float y);
	CCPoint mapToScreen(CCPoint point);

	CCSize mapToscreenSize(int l ,int b ,int h);
	CCPoint mapToscreenAnchor(int l ,int b ,int h);

private:
	int m_xUnit;
	int m_yUnit;
	int m_zUnit;
	
	int m_tileWidth;
	int m_tileHeight;
};





NS_CC_END

#endif //ISO_CCCoordinate_H_

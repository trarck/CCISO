#ifndef ISO_CCISOBatchDynamicTileLayer_H_
#define ISO_CCISOBatchDynamicTileLayer_H_

#include "cocos2d.h"
#include "CCISODynamicTileLayer.h"
#include "CCISOTileset.h"

NS_CC_BEGIN

/**
 * 动态更新可显示区域,只渲染显示区域的tile.
 * 使用batchnode来优化组件显示。
 */
class CCISOBatchDynamicTileLayer : public CCISODynamicTileLayer {

public:
	
	CCISOBatchDynamicTileLayer();
    
	~CCISOBatchDynamicTileLayer(void);
	
    virtual bool init();
    
    virtual bool init(CCSize& mapTileSize,CCPoint& offset);
public:
    inline void setTileset(CCISOTileset* pTileset)
	{
		CC_SAFE_RETAIN(pTileset);
		CC_SAFE_RELEASE(m_pTileset);
		m_pTileset = pTileset;
	}

	inline CCISOTileset* getTileset()
	{
		return m_pTileset;
	}
protected:

    CCISOTileset* m_pTileset;
};



NS_CC_END

#endif //ISO_CCISOBatchDynamicTileLayer_H_

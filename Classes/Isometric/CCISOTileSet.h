#ifndef ISO_CCISOTileset_H_
#define ISO_CCISOTileset_H_

#include "cocos2d.h"
#include "CCISOTile.h"

NS_CC_BEGIN


/**
 * tile的二种表示方式
 * 1.整张图片。每个tile的id按照从左到右，从下到下增加。静态的物体。
 * 2.分开的图片。可以是精灵动画。比较灵活，占用一定内存
 */
class CCISOTileset : public CCObject{

public:
    
    CCISOTileset();
    
    ~CCISOTileset();

    bool isExternal() const { return !m_tFileName.empty(); }
    
    int tileCount() const { return m_pTiles->count(); }
    
    void addTile(const char* imageName);
    
    void setTileImage(unsigned int index,const char* imageName);
    
    void addTile(CCSprite* sprite);
    
    void setTileImage(unsigned int index,CCSprite* sprite);
    
    /**
     * 是否包含某个id
     */
    bool contains(unsigned int gid);
    
    CCRect rectForGid(unsigned int gid);
    
    CCISOTile* tileForGid(unsigned int gid);
    
    
    int columnCountForWidth(int width);
    
    int rowCountForHeight(int height);
    
    unsigned int lastGid();
    
public:
    
    virtual void setName(const char* pName);
    virtual std::string& getName();
    virtual void setFileName(const char* pFileName);
    virtual std::string& getFileName();
    virtual void setImageSource(const char* pImageSource);
    virtual std::string& getImageSource();
    virtual void setTileWidth(int nTileWidth);
    virtual int getTileWidth();
    virtual void setTileHeight(int nTileHeight);
    virtual int getTileHeight();
    virtual void setTileSpacing(int nTileSpacing);
    virtual int getTileSpacing();
    virtual void setMargin(int nMargin);
    virtual int getMargin();
    virtual void setTileOffset(CCPoint tTileOffset);
    virtual CCPoint getTileOffset();
    virtual void setImageWidth(int nImageWidth);
    virtual int getImageWidth();
    virtual void setImageHeight(int nImageHeight);
    virtual int getImageHeight();
    virtual void setColumnCount(int nColumnCount);
    virtual int getColumnCount();
    virtual void setTiles(CCArray* pTiles);
    virtual CCArray* getTiles();
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    

    virtual void setFirstGid(unsigned int uFirstGid);
    virtual unsigned int getFirstGid();
    
    virtual unsigned int getLastGid();
    /**
     * set zero to clear lastGid
     */
    virtual void setLastGid(unsigned int uLastGid);
    
    
    virtual void setTileProperties(CCDictionary* pTileProperties);
    virtual CCDictionary* getTileProperties();
public:
    /**
     * 名称
     */
    std::string m_tName;
    
    /**
     * 单独定义的文件名
     */
    std::string m_tFileName;
    
    /**
     * 每个tile的宽
     */
    int m_nTileWidth;
    
    /**
     * 每个tile的高
     */
    int m_nTileHeight;
    
    /**
     * 在tile图片里每个tile的内部空白
     */
    int m_nTileSpacing;
    
    /**
     * 整个tile图片边框的空白
     */
    int m_nMargin;
    
    /**
     * 整个tile图片的偏移
     */
    CCPoint m_tTileOffset;
    
    /**
     * tile拼成的图片名
     */
    std::string m_tImageSource;
    
    /**
     * tile拼成的图片宽
     */
    int m_nImageWidth;
    
    /**
     * tile拼成的图片高
     */
    int m_nImageHeight;
    
    /**
     * tile拼成的图片
     */
    CCTexture2D* m_pTexture;
    
    /**
     * 图片的格子栏数
     */
    int m_nColumnCount;
    
    /**
     * 所有小格子
     */
    CCArray* m_pTiles;
    
    /**
     * 开始的gid
     */
    unsigned int m_uFirstGid;
    
    /**
     * 结束的gid
     */
    unsigned int m_uLastGid;
    
    /**
     * 属性
     */
    CCDictionary* m_pProperties;
    
    /**
     * tile的属性
     */
    CCDictionary* m_pTileProperties;
    
};


NS_CC_END

#endif //ISO_CCISOTileset_H_

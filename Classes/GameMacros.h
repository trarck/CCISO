
#ifndef CCISO_GAMEMACRO_H_
#define CCISO_GAMEMACRO_H_

#ifdef __cplusplus
    #define NS_YH_BEGIN                     namespace yhge {
    #define NS_YH_END                       }
    #define USING_NS_YH                     using namespace yhge
#else
    #define NS_YH_BEGIN 
    #define NS_YH_END 
    #define USING_NS_YH
#endif 

#define FLOAT_ZERO_FLAG 0.00001

//tile width 
#ifndef TileWidth
#define TileWidth 64 
#endif
//tile height
#ifndef TileHeight
#define TileHeight 32 
#endif


#endif //CCISO_GAMEMACRO_H_

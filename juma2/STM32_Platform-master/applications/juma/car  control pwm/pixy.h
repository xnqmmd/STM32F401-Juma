#ifndef __PIXY_H
#define __PIXY_H	 
#include "stm32f4xx.h" 


typedef struct Pixy_Color//单色块位置大小信息
{
	uint16_t Pixy_Color_Sig;//1-7 for normal signatures
	uint16_t Pixy_Color_PosX;  //0 to 319
	uint16_t Pixy_Color_PosY;  //0 to 319
	uint16_t Pixy_Color_Width; //1 to 320
	uint16_t Pixy_Color_Height;//1 to 320
}Pixy_Color;


typedef struct Pixy_ColorCode//色条位置大小信息
{
	uint16_t Pixy_ColorCode_Sig;//Same as follow
	uint16_t Pixy_ColorCode_PosX;
	uint16_t Pixy_ColorCode_PosY;
	uint16_t Pixy_ColorCode_Width;
	uint16_t Pixy_ColorCode_Height;
	uint16_t Pixy_ColorCode_Angle;//The angle of the object detected object only when the detected object is a color code
}Pixy_ColorCode;


	
#endif

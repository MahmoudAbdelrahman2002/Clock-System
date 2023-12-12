/********************************************************************************************/
/********************************************************************************************/
/**************************		Date:    27/11/2023            			*************/
/**************************		Layer:   MCAL								   	*************/
/**************************		SWC:	 DMA									*************/
/**************************		Version: 1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

#ifndef DMA1_INTERFACE_H_
#define DMA1_INTERFACE_H_

/******************************************************************************/
/************************ @DMA1_STREAM_t ***************************************/
/******************************************************************************/
typedef enum
{
	STREAM0=0,
	STREAM1,
	STREAM2,
	STREAM3,
	STREAM4,
	STREAM5,
	STREAM6,
	STREAM7,
}DMA1_STREAM_t;

/******************************************************************************/
/************************ @DMA1_CHANNEL_t ***************************************/
/******************************************************************************/

typedef enum
{
	CHANNEL0=0,
	CHANNEL1,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4,
	CHANNEL5,
	CHANNEL6,
	CHANNEL7,
}DMA1_CHANNEL_t;

/******************************************************************************/
/************************ @DMA1_PRIORITY_t ***************************************/
/******************************************************************************/


typedef enum
{
	LOW_PRIORITY=0,
	MEDIAM_PRIORITY,
	HIGH_PRIORITY,
	VERY_HIGH_PRIORITY,
}DMA1_PRIORITY_t;

/******************************************************************************/
/************************ @DMA1_INCREAMENT_MEM_t ***************************************/
/******************************************************************************/

typedef enum
{
	DISABLE_INCREAMENT_MEMORY=0,
	ENABLE_INCREAMENT_MEMORY=1
}DMA1_INCREAMENT_MEM_t;
/******************************************************************************/
/************************ @DMA1_INCREAMENT_PERIPHRAL_t ***************************************/
/******************************************************************************/
typedef enum
{
	DISABLE_INCREAMENT_PERIPHRAL=0,
	ENABLE_INCREAMENT_PERIPHRAL=1
}DMA1_INCREAMENT_PERIPHRAL_t;

/******************************************************************************/
/************************ @DMA1_MODE_t ***************************************/
/******************************************************************************/

typedef enum
{
	ENABLE_DIERCT_MODE=0,
	DISABLE_DIERCT_MODE=1,
}DMA1_MODE_t;

/******************************************************************************/
/************************ @DMA1_THRSHOLDEL_LEVEL_t ***************************************/
/******************************************************************************/

typedef enum
{
  QUADRIC=0,
  HALF=1,
  FULL=3,

}DMA1_THRSHOLDEL_LEVEL_t;
/******************************************************************************/
/************************ @DMA1_TRANSIMITION_MODE_t ***************************************/
/******************************************************************************/

typedef enum
{
PERIPHRAL_TO_MEMORY=0,
MEMORY_TO_PERIPHRAL=1,
MEMORY_TO_MEMORY=2,
}DMA1_TRANSIMITION_MODE_t;
/******************************************************************************/
/************************ @DMA1_TRANSIMITION_SIZE_t ***************************************/
/******************************************************************************/


typedef enum
{
ONE_BYTE=0,
TWO_BYTE=1,
THREE_BYTE=2,
FOUR_BYTE=3,
}DMA1_TRANSIMITION_SIZE_t;
/********************************************************/
/******* @DMA1_CONFIGRATION_t *********************************/
/********************************************************/
typedef struct
{
	DMA1_STREAM_t streamNum;
	DMA1_MODE_t mode;
	DMA1_PRIORITY_t priority;
	DMA1_THRSHOLDEL_LEVEL_t thresholder;
	DMA1_TRANSIMITION_MODE_t transimition_mode;
	DMA1_INCREAMENT_PERIPHRAL_t Periphral_state;
	DMA1_INCREAMENT_MEM_t Memory_state;
	DMA1_CHANNEL_t channelNum;
	DMA1_TRANSIMITION_SIZE_t Transmition_size;
}DMA1_CONFIGRATION_t;
/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
uint8_t DMA1_init(DMA1_CONFIGRATION_t* config);
void DMA1_send_Data(DMA1_CONFIGRATION_t*,uint32_t* src_address,uint32_t* destination_address,uint16_t  size);
uint8_t DMA1_setCallBack(DMA1_STREAM_t streem,void (*ptr)(void));


#endif /* DMA1_INTERFACE_H_ */
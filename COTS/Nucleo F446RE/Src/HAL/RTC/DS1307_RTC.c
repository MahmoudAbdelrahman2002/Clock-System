/*
 * DS1307_RTC.c
 *
 *  Created on: Dec 2, 2023
 *      Author: abdoa
 */

#include <stdint.h>
#include "../../LIB/Stm32F466xx.h"
#include "DS1307_RTC_interface.h"
#include "DS1307_RTC_config.h"
#include "DS1307_RTC_private.h"
#include "../../MCAL/I2C/I2C_Interface.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../MCAL/DMA/DMA1_interface.h"
#include "../../MCAL/RCC/RCC_interface.h"


static void ds1307_i2c_pin_config();
static void ds1307_i2c_config();
static void ds1307_dma_config();
static void ds1307_write(uint8_t value ,uint8_t address);
static uint8_t ds1307_read(uint8_t address );
static uint8_t binary_to_bcd(uint8_t value);
static uint8_t bcd_to_binary(uint8_t value);

//DMA config for I2C_rx
DMA1_CONFIGRATION_t i2c1RX_dma_config ={
			.Memory_state= DISABLE_INCREAMENT_MEMORY,
			.Periphral_state = DISABLE_INCREAMENT_PERIPHRAL,
			.Transmition_size =ONE_BYTE,
			.channelNum =CHANNEL1,
			.mode =ENABLE_DIERCT_MODE,
			.priority= MEDIAM_PRIORITY,
			.streamNum = STREAM0,
			.transimition_mode =PERIPHRAL_TO_MEMORY};

//DMA config for I2C_tx
DMA1_CONFIGRATION_t i2c1TX_dma_config ={
			.Memory_state= DISABLE_INCREAMENT_MEMORY,
			.Periphral_state = DISABLE_INCREAMENT_PERIPHRAL,
			.Transmition_size =ONE_BYTE,
			.channelNum =CHANNEL1,
			.mode =ENABLE_DIERCT_MODE,
			.priority= MEDIAM_PRIORITY,
			.streamNum = STREAM7,
			.transimition_mode =MEMORY_TO_PERIPHRAL};

// sda pin config for i2c
GPIO_PinConfig_t sda_config = {.AltFunc =AF4,
		.Mode = ALTERNATE_FUNCTION,
		.OutputType =OPEN_DRAIN,
		.PinNum= DS1307_I2C_SDA_PIN,
		.Port= DS1307_I2C_SDA_PORT,
		.PullType= DS1307_I2C_PUPD,
		.Speed = FAST
};

// scl pin config for i2c
GPIO_PinConfig_t scl_config = {.AltFunc =AF4,
		.Mode = ALTERNATE_FUNCTION,
		.OutputType =OPEN_DRAIN,
		.PinNum= DS1307_I2C_SCL_PIN,
		.Port= DS1307_I2C_SDA_PORT,
		.PullType= DS1307_I2C_PUPD,
		.Speed = FAST
};
GPIO_PinConfig_t led = {
		.Mode = OUTPUT,
		.OutputType =PUSH_PULL,
		.PinNum= PIN5,
		.Port= PORTA,
		.PullType= NOPULL,
		.Speed = FAST
};

// i2c config
I2C_Configs_t i2c_config ={.ADD_Mode = ADDRESSING_MODE_7BITS,
			.Chip_Address = MCU_ADDRESS,
			.I2C_Mode = MASTER_MODE_STANDARD,
			.I2C_Num = I2C_NUMBER_1,
			.I2C_Pclk_MHZ = 16,
			.SCL_Frequency_KHZ =100,
			.Stretch_state =CLK_STRETCH_ENABLED};

uint8_t ds1307_RTC_init(){ //Error State return CH bit. If it's is 1 so init failed
	//init I2C pins

	RCC_AHB1EnableCLK(RCC_AHB1ENR_GPIOBEN);
	RCC_AHB1EnableCLK(RCC_AHB1ENR_GPIOAEN);
	RCC_AHB1EnableCLK(RCC_AHB1ENR_DMA1EN);
	ds1307_i2c_pin_config();
	RCC_APB1EnableCLK(RCC_APB1ENR_I2C1EN);

	//init i2c driver + dma
	ds1307_i2c_config();
	I2C_Enable_DMA(I2C_Num);
	//init dma for both I2C_RX & I2C_TX
	ds1307_dma_config();


	// make clk halt = 0
	ds1307_write(0x00,DS1307_SEC_ADD);
	//read clk halt bit
	uint8_t clkState =55;
	clkState = ds1307_read(DS1307_SEC_ADD);
return clkState;
}

void ds1307_RTC_set_DateANDTime(DS1307_RTC_date_t* u8_rtc_date,DS1307_RTC_time_t* u8_rtc_time){
	uint8_t seconds = binary_to_bcd(u8_rtc_time->SEC);
	seconds &=~(1<<7);
	ds1307_write(seconds, DS1307_SEC_ADD);

	uint8_t min =binary_to_bcd(u8_rtc_time->MIN);
	ds1307_write(min, DS1307_MIN_ADD);

	uint8_t hours =binary_to_bcd(u8_rtc_time->HOUR);
	if(u8_rtc_time->time_format==_24_Hour_Mode){//_24->0 12->1
		hours&=~(1<<TIME_FORMAT_MASK);}
	else{
		hours|=(1<<TIME_FORMAT_MASK);
		if(u8_rtc_time->time_format==_12_Hour_Mode_PM){ // pm->1 am->0
			hours|=(1<<_12_HOUR_MASK);
		}
		else{
			hours&=~(1<<_12_HOUR_MASK);
		}

	}
	ds1307_write(hours, DS1307_HR_ADD);


	//////////////////		DATE	///////////////////
	ds1307_write(binary_to_bcd(u8_rtc_date->DATE), DS1307_DATE_ADD);
	ds1307_write(binary_to_bcd(u8_rtc_date->DAY),DS1307_DAY_ADD);
	ds1307_write(binary_to_bcd(u8_rtc_date->MONTH),DS1307_MONTH_ADD);
	ds1307_write(binary_to_bcd(u8_rtc_date->YEAR),DS1307_YEAR_ADD);

}
void ds1307_RTC_get_DateANDTime(DS1307_RTC_date_t* u8_rtc_date,DS1307_RTC_time_t* u8_rtc_time){

	uint8_t seconds = ds1307_read(DS1307_SEC_ADD);
	seconds &=~(1<<7); // clear the CH bit
	u8_rtc_time->SEC = bcd_to_binary(seconds);
	u8_rtc_time->MIN = bcd_to_binary(ds1307_read(DS1307_MIN_ADD));
	uint8_t hours =  ds1307_read(DS1307_HR_ADD);
	if(hours & 1<<TIME_FORMAT_MASK){//_24->0 12->1
		hours &=~(1<<TIME_FORMAT_MASK);
		if(hours & (1<<_12_HOUR_MASK)){// pm->1 am->0
			hours &=~(1<<_12_HOUR_MASK);
			u8_rtc_time->time_format=_12_Hour_Mode_PM;
		}
		else{
			u8_rtc_time->time_format=_12_Hour_Mode_AM;

		}
	}
	else{
		u8_rtc_time->time_format=_24_Hour_Mode;
	}
	u8_rtc_time->HOUR = bcd_to_binary(hours);

	//////////////////		DATE	///////////////////

	u8_rtc_date->DATE= bcd_to_binary(ds1307_read(DS1307_DATE_ADD));
	u8_rtc_date->DAY= bcd_to_binary(ds1307_read(DS1307_DAY_ADD));
	u8_rtc_date->MONTH= bcd_to_binary(ds1307_read(DS1307_MONTH_ADD));
	u8_rtc_date->YEAR= bcd_to_binary(ds1307_read(DS1307_YEAR_ADD));
}

// function to configure the data and clk pins of the I2C by GPIO
static void ds1307_i2c_pin_config(){
	GPIO_u8PinInit(&scl_config);
	GPIO_u8PinInit(&sda_config);
	GPIO_u8PinInit(&led);
	GPIO_u8SetPinValue(PORTA, PIN5, PIN_HIGH);
}

// function to configure the I2C module
static void ds1307_i2c_config(){
	I2C_Init(&i2c_config);
}

//function to configure DMA for I2C1_rx and I2C1_tx
static void ds1307_dma_config(){
	DMA1_init(&i2c1RX_dma_config);
	DMA1_init(&i2c1TX_dma_config);
}

/*
 * @function 		:	ds1307_write
 * @brief			:	write in ds1307_RTC
 * @param			:	value: value to be write in the RTC
 * 					:	address: REG address that the value is going to be written in
 */
static void ds1307_write(uint8_t value ,uint8_t reg_address ){
	uint8_t tx[2]= {reg_address,value};
	//transmit slaveAddress, RegAddress then Value
	I2C_Master_Transmit_DMA(&i2c_config, DS1307_I2C_SALVE_ADDRESS_W, tx, 2, &i2c1TX_dma_config);
}
/*
 * @function 		:	ds1307_read
 * @brief			:	read from ds1307_RTC
 * @param			:	address: REG address that is going to be read
 */
static uint8_t ds1307_read(uint8_t reg_address ){
	uint8_t recived_data;
	//combined msg write the slave address with WRITE(LSB 0), reg address then send the slave address with READ(LSB 1) to read it

	//send Address packet with write
	I2C_SendAddressPacketMTransmitter_DMA(&i2c_config, DS1307_I2C_SALVE_ADDRESS_W, &i2c1TX_dma_config);

	//send regAdress to access
	I2C_SendDataPacket_DMA(&i2c_config, reg_address, &i2c1TX_dma_config);

	//send repeated start with Address packet with read
	I2C_SendAddressPacketMReceiver_DMA(&i2c_config, DS1307_I2C_SALVE_ADDRESS_R,&i2c1TX_dma_config );

	//receive data
	I2C_Master_Receive_DMA(&i2c_config, &recived_data, &i2c1RX_dma_config);
	return recived_data;
}

//function to convert binary to BCD
//NOTE the data should be stored in BCD in RTC regs
static uint8_t binary_to_bcd(uint8_t value){
	uint8_t bcd;
	bcd = value %10;
	value /=10;
	bcd|=value<<4;
	return bcd;

}

//function to convert BCD to binary
static uint8_t bcd_to_binary(uint8_t value){
	uint8_t binary;
	binary= value &(0x0f);
	binary+= (value>>4)*10;
	return binary;

}

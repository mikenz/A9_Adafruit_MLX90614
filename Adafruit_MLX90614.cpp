/***************************************************
  This is a library for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749

  These sensors use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_MLX90614.h"
#include "api_debug.h"
#include "api_os.h"

Adafruit_MLX90614::Adafruit_MLX90614(uint8_t i2caddr) : _addr(i2caddr) {
}

void Adafruit_MLX90614::begin(I2C_ID_t i2c)
{
  _i2c = i2c;
  _i2cConfig.freq = I2C_FREQ_100K;
  I2C_Init(_i2c, _i2cConfig);
}

//////////////////////////////////////////////////////

float Adafruit_MLX90614::readObjectTempC(void) {
  return readTemp(MLX90614_TOBJ1);
}


float Adafruit_MLX90614::readAmbientTempC(void) {
  return readTemp(MLX90614_TA);
}

float Adafruit_MLX90614::readTemp(uint8_t reg) {
  float temp;

  temp = read16(reg);
  temp *= .02;
  temp  -= 273.15;
  return temp;
}

/*********************************************************************/

uint16_t Adafruit_MLX90614::read16(uint8_t reg)
{
  uint8_t res[3];
  I2C_Error_t error = I2C_ReadMem(_i2c, _addr, reg, 1, &res[0], 3, I2C_DEFAULT_TIME_OUT);
  if (error != I2C_ERROR_NONE)
  {
    Trace(1, "Adafruit_MLX90614::read16 readmem error: 0X%02x", error);
    return 0;
  }
  return res[0] | res[1] << 8;
}


// McpDigitalPot 2-channel Digital Potentiometer
// ww1.microchip.com/downloads/en/DeviceDoc/22059b.pdf

// The default SPI Control Register - SPCR = B01010000;
// interrupt disabled,spi enabled,msb 1st,master,clk low when idle,
// sample on leading edge of clk,system clock/4 rate (fastest).
// Enable the digital pins 11-13 for SPI (the MOSI,MISO,SPICLK)


#include <string.h>
#include "driver/spi_master.h"
#include "driver/gpio.h"

#include "McpDigitalPot.h"

#define PIN_NUM_MISO 25
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  19

void my_spi_pre_transfer_callback(spi_transaction_t *t) 
{
  /* do something ? */
}

//---------- constructor ----------------------------------------------------

McpDigitalPot::McpDigitalPot(uint8_t slave_select_pin, float rAB_ohms)
{
  initSpi(slave_select_pin);
  initResistance(rAB_ohms, rW_ohms_typical);
}

McpDigitalPot::McpDigitalPot(uint8_t slave_select_pin, float rAB_ohms, float rW_ohms)
{
  initSpi(slave_select_pin);
  initResistance(rAB_ohms, rW_ohms);
}

//------------------ protected -----------------------------------------------

uint16_t McpDigitalPot::byte2uint16(uint8_t high_byte, uint8_t low_byte)
{
  return (uint16_t)high_byte<<8 | (uint16_t)low_byte;
}

uint8_t McpDigitalPot::uint16_high_byte(uint16_t uint16)
{
  return (uint8_t)(uint16>>8);
}

uint8_t McpDigitalPot::uint16_low_byte(uint16_t uint16)
{
  return (uint8_t)(uint16 & 0x00FF);
}

void McpDigitalPot::initSpi(uint8_t slave_select_pin)
{
  // init SPI
  esp_err_t ret;

  spi_bus_config_t buscfg = {
    mosi_io_num: PIN_NUM_MOSI,
    miso_io_num: PIN_NUM_MISO,
    sclk_io_num: PIN_NUM_CLK,
    quadwp_io_num: -1,
    quadhd_io_num: -1
  };

  spi_device_interface_config_t devcfg;
  memset(&devcfg, 0, sizeof(devcfg));
  devcfg.clock_speed_hz = 10000000;                     // Clock out at 10 MHz
  devcfg.mode = 0;                                      // SPI mode 0
  devcfg.spics_io_num = slave_select_pin;               // CS pin
  devcfg.queue_size = 7;                                // We want to be able to queue 7 transactions at a time
  devcfg.pre_cb = my_spi_pre_transfer_callback;         // Specify pre-transfer callback to handle D/C line

    // Initialize the SPI bus
  ret = spi_bus_initialize(HSPI_HOST, &buscfg, 1);
  assert(ret == ESP_OK);

  // Attach the LCD to the SPI bus
  ret = spi_bus_add_device(HSPI_HOST, &devcfg, &_spi_handle);
  assert(ret == ESP_OK);
}

void McpDigitalPot::initResistance(float rAB_ohms, float rW_ohms)
{
  this->rAB_ohms             = rAB_ohms;
  this->rW_ohms              = rW_ohms;
  this->rAW_ohms_max         = rAB_ohms - rW_ohms;
  this->scale                = rAW_ohms_max;
}

float McpDigitalPot::wiperPositionIncrement()
{
  return (rAW_ohms_max - rW_ohms) / resolution;
}

unsigned int McpDigitalPot::resistanceToPosition(float resistance)
{
  if(resistance <= 0.0)
    return 0;
  else if(scale != rAW_ohms_max)
    resistance = resistance * rAW_ohms_max / scale;

  return (unsigned int)((resistance - rW_ohms) / wiperPositionIncrement() ) + 0.5;
}

float McpDigitalPot::positionToResistance(unsigned int position)
{
  float resistance =  rW_ohms + ( (float)position * wiperPositionIncrement() );

  if(scale != rAW_ohms_max)
    resistance = resistance * scale / rAW_ohms_max;
  
  return resistance;
}

void McpDigitalPot::spiWrite(uint8_t cmd_byte, uint8_t data_byte)
{
  cmd_byte |= kCMD_WRITE;
  spiTransfer(cmd_byte);
  spiTransfer(data_byte);
}

uint16_t McpDigitalPot::spiRead(uint8_t cmd_byte)
{
  cmd_byte |= kCMD_READ;
  uint8_t high_byte = spiTransfer(cmd_byte);
  uint8_t low_byte  = spiTransfer(0xFF);
  return byte2uint16(high_byte, low_byte);
}

void McpDigitalPot::internalSetWiperPosition(uint8_t wiperAddress, unsigned int position, bool isNonVolatile)
{
  uint8_t cmd_byte    = 0x00;
  uint8_t data_byte   = 0x00;
  cmd_byte        |= wiperAddress;

  // Calculate the 9-bit data value to send
  if(position > 255)
    cmd_byte      |= 0b00000001; // Table 5-1 (page 36)
  else
    data_byte      = (uint8_t)(position & 0x00FF);

  spiWrite(cmd_byte|kADR_VOLATILE, data_byte);

  if(isNonVolatile)
  {
    // EEPROM write cycles take 4ms each. So we block with delay(5); after any NV Writes
    spiWrite(cmd_byte|kADR_NON_VOLATILE, data_byte);
    ets_delay_us(50);
  }
}

uint8_t McpDigitalPot::spiTransfer(const uint8_t cmd)
{
  esp_err_t ret;
  spi_transaction_t t;
  memset(&t, 0, sizeof(t));                     // Zero out the transaction
  t.length = 8;                                 // Command is 8 bits
  t.tx_buffer = &cmd;                           // The data is the cmd itself
  t.user = (void*)0;                            // D/C needs to be set to 0
  ret = spi_device_transmit(_spi_handle, &t);   // Transmit!
  assert(ret == ESP_OK);                        // Should have had no issues.
  return ret;
}

//---------- public ----------------------------------------------------

float McpDigitalPot::getResistance(unsigned int wiperIndex)
{
  return positionToResistance( getPosition(wiperIndex) );
}

unsigned int McpDigitalPot::getPosition(unsigned int wiperIndex)
{
  if (wiperIndex == 1) {
     return 0x01FF & this->spiRead(kADR_WIPER1|kADR_VOLATILE);
  } else {
     return (unsigned int)( 0x01FF & this->spiRead(kADR_WIPER0|kADR_VOLATILE) );
  }
}

void McpDigitalPot::setResistance(unsigned int wiperIndex, float resistance)
{
  setPosition( wiperIndex, resistanceToPosition(resistance) );
}

void McpDigitalPot::writeResistance(unsigned int wiperIndex, float resistance)
{
  writePosition( wiperIndex, resistanceToPosition(resistance) );
}

void McpDigitalPot::setPosition(unsigned int wiperIndex, unsigned int position)
{
  if (wiperIndex == 1) {
    this->internalSetWiperPosition(kADR_WIPER1, position, false);
  } else {
    this->internalSetWiperPosition(kADR_WIPER0, position, false);
  }
}

void McpDigitalPot::writePosition(unsigned int wiperIndex, unsigned int position)
{
  if (wiperIndex == 1) {
    this->internalSetWiperPosition(kADR_WIPER1, position, true);
  } else {
    this->internalSetWiperPosition(kADR_WIPER0, position, true);
  }
}



// // Not implemented
// bool McpDigitalPot::pot0_connected(bool terminal_a, bool wiper, bool terminal_b)
// {
//   
// }
// 
// bool McpDigitalPot::pot1_connected(bool terminal_a, bool wiper, bool terminal_b)
// {
//   
// }
// 
// void McpDigitalPot::pot0_connect(bool terminal_a, bool wiper, bool terminal_b)
// {
//   
// }
// 
// void McpDigitalPot::pot1_connect(bool terminal_a, bool wiper, bool terminal_b)
// {
//   
// }
// 
// bool McpDigitalPot::pot0_shutdown()
// {
//   
// }
// 
// bool McpDigitalPot::pot1_shutdown()
// {
//   
// }
// 
// void McpDigitalPot::pot0_shutdown(bool shutdown)
// {
//   
// }
// 
// void McpDigitalPot::pot1_shutdown(bool shutdown)
// {
//   
// }
// 
// bool McpDigitalPot::hw_shutdown()
// {
//   
// }



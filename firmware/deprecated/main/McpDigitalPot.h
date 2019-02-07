
// McpDigitalPot 2-channel Digital Potentiometer
// ww1.microchip.com/downloads/en/DeviceDoc/22059b.pdf

#ifndef McpDigitalPot_h
#define McpDigitalPot_h

class McpDigitalPot
{
  public:
    // You must at least specify the slave select pin and the rated resistance
    McpDigitalPot(uint8_t slave_select, float rAB_ohms);

    // If you have measured wiper resistance, rW
    McpDigitalPot(uint8_t slave_select, float rAB_ohms, float rW_ohms);

    // The resistance scaling, defaults to rAB_ohms
    float scale;

    // Read potentiometer values
    float getResistance(unsigned int wiperIndex);
    unsigned int getPosition(unsigned int wiperIndex);

    // Write potentiometer values
    void setResistance(unsigned int wiperIndex, float resistance);
    void writeResistance(unsigned int wiperIndex, float resistance);
    
    void setPosition(unsigned int wiperIndex, unsigned int position);
    void writePosition(unsigned int wiperIndex, unsigned int position);
    
    // // Not implemented
    // // Connect / disconnect potentiometers
    // bool pot0_connected(bool terminal_a, bool wiper, bool terminal_b);
    // bool pot1_connected(bool terminal_a, bool wiper, bool terminal_b);
    // void pot0_connect(bool terminal_a, bool wiper, bool terminal_b);
    // void pot1_connect(bool terminal_a, bool wiper, bool terminal_b);
    // 
    // bool pot0_shutdown();
    // bool pot1_shutdown();
    // void pot0_shutdown(bool shutdown);
    // void pot1_shutdown(bool shutdown);
    // 
    // bool hw_shutdown();

  protected:
   uint8_t spiTransfer(const uint8_t byte);

    constexpr static float        rW_ohms_typical = 117.50;
    constexpr static unsigned int resolution_7bit = 128;
    constexpr static unsigned int resolution_8bit = 256;

    // Other devices can be configured below vv as per the device numbering scheme:
    // MCP4N-- N=1 single pot, N=2 dual pot
    // MCP4--N N=1 potentiometer, N=2 rheostat
    // MCP4-N- N=3 7-bit volatile, N=4 7-bit non-volatile, N=5 8-bit volatile, N=6 8-bit non-volatile
    const static unsigned int resolution      = resolution_7bit;

    float rW_ohms;
    float rAB_ohms;
    float rAW_ohms_max;

    const static uint8_t kADR_WIPER0       = 0b00000000;
    const static uint8_t kADR_WIPER1       = 0b00010000;

    const static uint8_t kCMD_READ         = 0b00001100;
    const static uint8_t kCMD_WRITE        = 0b00000000;

    const static uint8_t kADR_VOLATILE     = 0b00000000;
    const static uint8_t kADR_NON_VOLATILE = 0b00100000;

    const static uint8_t kTCON_REGISTER    = 0b01000000;
    const static uint8_t kSTATUS_REGISTER  = 0b01010000;

    uint16_t byte2uint16(uint8_t high_byte, uint8_t low_byte);
    uint8_t uint16_high_byte(uint16_t uint16);
    uint8_t uint16_low_byte(uint16_t uint16);

    void initSpi(uint8_t slave_select_pin);
    void initResistance(float rAB_ohms, float rW_ohms);

    float wiperPositionIncrement();
    unsigned int resistanceToPosition(float ohms);
    float positionToResistance(unsigned int wiper_pos);

    uint16_t spiRead(uint8_t cmd_byte);
    void spiWrite(uint8_t cmd_byte, uint8_t data_byte);
    void internalSetWiperPosition(uint8_t wiperAddress, unsigned int position, bool isNonVolatile);

    spi_device_handle_t _spi_handle;
};

#endif // McpDigitalPot_h




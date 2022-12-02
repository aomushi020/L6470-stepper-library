/*
    L6470 Stepper driver library for Arduino
    by aomushi020

    Board(Archtecture)s
        Uno
        Mega/Mega2560
        ESP8266
        ESP32(M5Stack)
        RP2040
*/

#ifndef L6470_h
#define L6470_h

// SPI PINS
#ifndef L6470_SET_SPI_PINS
#define L6470_SET_SPI_PINS

#ifdef defined(ARDUINO_AVR_UNO)
  #define L6470_SPI_MOSI  11
  #define L6470_SPI_MISO  12
  #define L6470_SPI_SCK   13
#elif defined(ESP8266)
  #define L6470_SPI_MOSI  13
  #define L6470_SPI_MISO  12
  #define L6470_SPI_SCK   14
#elif defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560)
  #define L6470_SPI_MOSI  51
  #define L6470_SPI_MISO  50
  #define L6470_SPI_SCK   52
#elif defined(_M5STACK_H_)
  #define L6470_SPI_MOSI  23
  #define L6470_SPI_MISO  19
  #define L6470_SPI_SCK   18
#else
  #define L6470_SPI_MOSI  11
  #define L6470_SPI_MISO  12
  #define L6470_SPI_SCK   13
#endif
#endif

// L6470 Register Addresses
#define L6470_ADD_ABS_POS     0x01
#define L6470_ADD_EL_POS      0x02
#define L6470_ADD_MARK        0x03
#define L6470_ADD_SPEED       0x04
#define L6470_ADD_ACC         0x05
#define L6470_ADD_DEC         0x06
#define L6470_ADD_MAX_SPEED   0x07
#define L6470_ADD_MIN_SPEED   0x08
#define L6470_ADD_FS_SPD      0x15
#define L6470_ADD_KVAL_HOLD   0x09
#define L6470_ADD_KVAL_RUN    0x0A
#define L6470_ADD_KVAL_ACC    0x0B
#define L6470_ADD_KVAL_DEC    0x0C
#define L6470_ADD_INT_SPEED   0x0D
#define L6470_ADD_ST_SLP      0x0E
#define L6470_ADD_FN_SLP_ACC  0x0F
#define L6470_ADD_FN_SLP_DEC  0x10
#define L6470_ADD_K_THERM     0x11
#define L6470_ADD_ADC_OUT     0x12
#define L6470_ADD_OCD_TH      0x13
#define L6470_ADD_STALL_TH    0x14
#define L6470_ADD_STEP_MODE   0x16
#define L6470_ADD_ALARM_EN    0x17
#define L6470_ADD_CONFIG      0x18
#define L6470_ADD_STATUS      0x19

// L6470 Application Commands
#define L6470_CMD_SETPARAM    0x00  // B000XXXXX
#define L6470_CMD_GETPARAM    0x20  // B001XXXXX
#define L6470_CMD_RUN         0x50  // B0101000X
#define L6470_CMD_STEPCLOCK   0x57  // B0101100X
#define L6470_CMD_MOVE        0x40  // B0100000X
#define L6470_CMD_GOTO        0x60  // B01100000
#define L6470_CMD_GOHOME      0x70  // B01110000
#define L6470_CMD_GOMARK      0x78  // B01111000
#define L6470_CMD_RESETPOS    0xD8  // B11011000
#define L6470_CMD_RESETDEVICE 0xC0  // B11000000
#define L6470_CMD_SOFTSTOP    0xB0  // B10110000
#define L6470_CMD_HARDSTOP    0xB8  // B10111000
#define L6470_CMD_SOFTHIZ     0xA0  // B10100000
#define L6470_CMD_HARDHIZ     0xA8  // B10101000
#define L6470_CMD_GETSTATUS   0xD0  // B11010000

class L6470{
  public:
    L6470(unsigned short _SPI_SS);
    L6470(unsigned short _SPI_SS,short _L6470_BS,short _L6470_SR);
    void begin(void);
    void setMaxSpeed(unsigned int _L6470_payload);
    void setHoldVoltage(unsigned char _L6470_payload);
    void setRunVoltage(unsigned char _L6470_payload);
    void setAccelVoltage(unsigned char _L6470_payload);
    void setDecelVoltage(unsigned char _L6470_payload);
    void setSteps(unsigned char _L6470_payload);
    void run(unsigned char _dir,unsigned long _spd);
    void move(unsigned char _dir,unsigned long _steps);
//    void move2step(unsigned char _dir,unsigned long _steps);
//    void move2cm(unsigned char _dir,unsigned int _cm);
    void hardStop(void);
    void softStop(void);
    void goHome(void);
    unsigned int calcSpeedValue(unsigned long _target_spd, unsigned int _wheel_diameter);
    unsigned int calcTurnValue(unsigned long _target_turn_deg, unsigned int _wheel_diameter, unsigned int _wheel_pitch);
  private:
    unsigned short _L6470_SPI_SS;
    unsigned short _L6470_SIG_BS;
    unsigned short _L6470_SIG_SR;
    static boolean _L6470_SPI_SETUP;
    static boolean _L6470_SPI_BEGIN;
    void _spiwrite(unsigned char _L6470_payload);
    unsigned long calcCm2Steps(unsigned int _cm);
};

#endif

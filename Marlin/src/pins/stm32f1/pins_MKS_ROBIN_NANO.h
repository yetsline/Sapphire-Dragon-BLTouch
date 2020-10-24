/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * MKS Robin nano (STM32F130VET6) board pin assignments
 */

#ifndef __STM32F1__
  #error "Oops! Select an STM32F1 board in 'Tools > Board.'"
#endif

#define BOARD_INFO_NAME "MKS Robin nano"

//
// Release PB4 (Y_ENABLE_PIN) from JTAG NRST role
//
#define DISABLE_DEBUG

//
// EEPROM
//
//#define SDCARD_EEPROM_EMULATION
#if EITHER(NO_EEPROM_SELECTED, FLASH_EEPROM_EMULATION) && NONE (SDCARD_EEPROM_EMULATION)
  #define FLASH_EEPROM_EMULATION
  #define EEPROM_PAGE_SIZE     (0x800U) // 2KB
  #define EEPROM_START_ADDRESS (0x8000000UL + (STM32_FLASH_SIZE) * 1024UL - (EEPROM_PAGE_SIZE) * 2UL)
  #define MARLIN_EEPROM_SIZE   EEPROM_PAGE_SIZE  // 2KB
#endif

//
// Limit Switches
//
#define X_STOP_PIN                          PA15
#define Y_STOP_PIN                          PA12
#define Z_MIN_PIN                           PA11
#define Z_MAX_PIN                           PC4

#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN                    PA4   // MT_DET
#endif

//
//TMC UART RX / TX Pins Hardware/Software Serial
//
#if HAS_TMC220x
  /**
  * TMC2209 stepper drivers
  * 
  * Hardware serial communication ports.
  * If undefined software serial is used according to the pins below
  * 
  * Four TMC2209 drivers can use the same HW/SW serial port with hardware configured addresses.
  * Set the address using jumpers on pins MS1 and MS2.
  * Address | MS1  | MS2
  *       0 | LOW  | LOW
  *       1 | HIGH | LOW
  *       2 | LOW  | HIGH
  *       3 | HIGH | HIGH
  */

  // Set Hardware Serial UART only für TCM 2209
  //#define HARDWARE_SERIAL
  // Set Software Serial UART for TMC 2208 / TMC 2209
  //#define SOFTWARE_SERIAL

  #if ENABLED(HARDWARE_SERIAL)
    //#define X_HARDWARE_SERIAL  Serial1
    //#define Y_HARDWARE_SERIAL  Serial1
    //#define Z_HARDWARE_SERIAL  Serial1
    //#define Z2_HARDWARE_SERIAL Serial1
    //#define E0_HARDWARE_SERIAL Serial1
    //#define E1_HARDWARE_SERIAL Serial1

    //Set *_SERIAL_TX_PIN and *_SERIAL_RX_PIN to match for all drivers on the same PIN to the same Slave Address.
    // | = add jumper
    // : = remove jumper
    // M1 is always closest to 12/24v
    // <- board power M1 M2 M3 -> endstops
    // See: https://github.com/le3tspeak/Marlin-2.0.X-MKS-Robin-Nano/blob/MKS-Robin-Nano/docs/TMC2209HWSERIAL.jpg
    #define  X_SLAVE_ADDRESS 3    // |  |  :
    #define  Y_SLAVE_ADDRESS 2    // :  |  :
    #define  Z_SLAVE_ADDRESS 1    // |  :  :
    #define E0_SLAVE_ADDRESS 0    // :  :  :

    #ifdef E1_DRIVER_TYPE
      #define E1_SLAVE_ADDRESS 0  // :  :  : 
    #endif
    #ifdef Z2_DRIVER_TYPE
      #define Z2_SLAVE_ADDRESS 0  // :  :  : 
    #endif

    #define X_SERIAL_TX_PIN                   PA9
    #define X_SERIAL_RX_PIN                   PA9
    
    #define Y_SERIAL_TX_PIN                   PA9
    #define Y_SERIAL_RX_PIN                   PA9
    
    #define Z_SERIAL_TX_PIN                   PA9
    #define Z_SERIAL_RX_PIN                   PA9

    #define E0_SERIAL_TX_PIN                  PA5
    #define E0_SERIAL_RX_PIN                  PA5

    #ifdef E1_DRIVER_TYPE
      #define E1_SERIAL_TX_PIN                PA9
      #define E1_SERIAL_RX_PIN                PA9
    #endif

    #ifdef Z2_DRIVER_TYPE
      #define E1_SERIAL_TX_PIN                PA9
      #define E1_SERIAL_RX_PIN                PA9
    #endif

  #elif ENABLED (SOFTWARE_SERIAL)
    //#define X_HARDWARE_SERIAL  Serial1
    //#define Y_HARDWARE_SERIAL  Serial1
    //#define Z_HARDWARE_SERIAL  Serial1
    //#define Z2_HARDWARE_SERIAL Serial1
    //#define E0_HARDWARE_SERIAL Serial1
    //#define E1_HARDWARE_SERIAL Serial1

    //Set *_SERIAL_TX_PIN and *_SERIAL_RX_PIN to match for all drivers on the same PIN to the same Slave Address.
    #define  X_SLAVE_ADDRESS 0
    #define  Y_SLAVE_ADDRESS 0
    #define  Z_SLAVE_ADDRESS 0
    #define E0_SLAVE_ADDRESS 0
    #ifdef E1_DRIVER_TYPE
      #define E1_SLAVE_ADDRESS 0  
    #endif
    #ifdef Z2_DRIVER_TYPE
      #define Z2_SLAVE_ADDRESS 0
    #endif

    #define X_SERIAL_TX_PIN                   PA3
    #define X_SERIAL_RX_PIN                   PA3
    
    #define Y_SERIAL_TX_PIN                   PA6
    #define Y_SERIAL_RX_PIN                   PA6
    
    #define Z_SERIAL_TX_PIN                   PA1
    #define Z_SERIAL_RX_PIN                   PA1

    #define E0_SERIAL_TX_PIN                  PE5
    #define E0_SERIAL_RX_PIN                  PE5

    #ifdef E1_DRIVER_TYPE
      #define E1_SERIAL_TX_PIN                PA9
      #define E1_SERIAL_RX_PIN                PA9
    #endif

    #ifdef Z2_DRIVER_TYPE
      #define E1_SERIAL_TX_PIN                PA9
      #define E1_SERIAL_RX_PIN                PA9
    #endif

    // Reduce baud rate to improve software serial reliability
    #define TMC_BAUD_RATE 19200
  #endif
#endif

  //
  // Steppers
  //
  #define X_ENABLE_PIN                        PE4
  #define X_STEP_PIN                          PE3
  #define X_DIR_PIN                           PE2

  #define Y_ENABLE_PIN                        PE1
  #define Y_STEP_PIN                          PE0
  #define Y_DIR_PIN                           PB9

  #define Z_ENABLE_PIN                        PB8
  #define Z_STEP_PIN                          PB5
  #define Z_DIR_PIN                           PB4

  #define E0_ENABLE_PIN                       PB3
  #define E0_STEP_PIN                         PD6
  #define E0_DIR_PIN                          PD3

 #if ENABLED(SOFTWARE_SERIAL)
  	//#define E1_ENABLE_PIN                   PA3  // USED BY UART X Don't change
    //#define E1_STEP_PIN                     PA6  // USED BY UART Y Don't change
    //#define E1_DIR_PIN                      PA1  // USED BY UART Z Don't change
   #else
    #define E1_ENABLE_PIN                     PA3
    #define E1_STEP_PIN                       PA6 
    #define E1_DIR_PIN                        PA1  
  #endif

//
// Servos
//
#if ENABLED(BLTOUCH)
  #define SERVO0_PIN                          PA8   // Enable BLTOUCH support ROBIN NANO v1.2 ONLY
#endif

//
// Temperature Sensors
//
#define TEMP_0_PIN                           PC1   // TH1
#define TEMP_1_PIN                           PC2   // TH2
#define TEMP_BED_PIN                         PC0   // TB1

//
// Heaters / Fans
//
#define HEATER_0_PIN                      PC3
#define HEATER_BED_PIN                    PA0

#if HOTENDS == 1                                  
  #ifndef FAN1_PIN
    #define FAN1_PIN                        PB0
    #define HEATER_1_PIN                    PC3
  #endif
#else
  #ifndef HEATER_1_PIN
    #define HEATER_1_PIN                    PB0
  #endif
#endif

#define FAN_PIN                           PB1   // FAN

// Thermocouples
//
//#define MAX6675_SS_PIN                    PE5   // TC1 - CS1
//#define MAX6675_SS_PIN                    PE6   // TC2 - CS2

//
// Misc. Functions
//
#define POWER_LOSS_PIN                      PA2   // PW_DET
#define PS_ON_PIN                           PA3   // PW_OFF

//#define SUICIDE_PIN                       PB2   // Enable MKSPWC support ROBIN NANO v1.2 ONLY
//#define SUICIDE_PIN_INVERTING false

//#define KILL_PIN                          PA2   // Enable MKSPWC support ROBIN NANO v1.2 ONLY
//#define KILL_PIN_INVERTING true                 // Enable MKSPWC support ROBIN NANO v1.2 ONLY

//
// SD Card
//
#ifndef SDCARD_CONNECTION
  #define SDCARD_CONNECTION                 ONBOARD
  #define ONBOARD_SD_CS_PIN                 PC11
#endif

#define SDIO_SUPPORT
#define SD_DETECT_PIN                       PD12
#define SDIO_CLOCK                          18000000       /* 18 MHz (18000000) or 4.5MHz (450000) */ 
#define SDIO_READ_RETRIES                   16

//
// LCD / Controller
//
#define BEEPER_PIN                          PC5

//
// LED / NEOPixel
//
#define LED_PIN                             PB2
#if ENABLED(NEOPIXEL_LED)
  #define NEO_PIXEL_1                       LED_PIN  // USED WIFI RX PIN
    #ifdef NEOPIXEL2_PIN
      #define NEO_PIXEL_2                   PA9   // USED WIFI TX PIN
    #endif
#endif
      
//
// WIFI ESP8266 
//
#if ANY(WIFISUPPORT, ESP3D_WIFISUPPORT)
  #define WIFI_TX_PIN    PA10
  #define WIFI_RX_PIN    PA9
  #define WIFI_IO0_PIN   PC13
  #define WIFI_IO1_PIN   PC7
#endif

//
// SPI
//
#define ENABLE_SPI2
#define SPI_FLASH
#if ENABLED(SPI_FLASH)
  #define W25QXX_CS_PIN                     PB12
  #define W25QXX_MOSI_PIN                   PB15
  #define W25QXX_MISO_PIN                   PB14
  #define W25QXX_SCK_PIN                    PB13
#endif

/**
 * Note: MKS Robin TFT screens use various TFT controllers.
 * If the screen stays white, disable 'LCD_RESET_PIN'
 * to let the bootloader init the screen.
 */
#if ENABLED(FSMC_GRAPHICAL_TFT)
  #define DOGLCD_MOSI -1 // prevent redefine Conditionals_post.h
  #define DOGLCD_SCK -1
  #define FSMC_CS_PIN        PD7    // NE4
  #define FSMC_RS_PIN        PD11   // A0

  //#define LCD_RESET_PIN      PC6    // FSMC_RST
  #define LCD_USE_DMA_FSMC
  #define FSMC_DMA_DEV DMA2
  #define FSMC_DMA_CHANNEL DMA_CH5
  //#define NO_LCD_REINIT             // Suppress LCD re-initialization

  #define LCD_BACKLIGHT_PIN  PD13

  #if ENABLED(TOUCH_BUTTONS)
    #define TOUCH_CS_PIN     PA7  // SPI2_NSS
    #define TOUCH_SCK_PIN    PB13 // SPI2_SCK
    #define TOUCH_MISO_PIN   PB14 // SPI2_MISO
    #define TOUCH_MOSI_PIN   PB15 // SPI2_MOSI
  #endif

  #define FSMC_UPSCALE 3
  #define LCD_FULL_PIXEL_WIDTH  480
  #define LCD_PIXEL_OFFSET_X    48
  #define LCD_FULL_PIXEL_HEIGHT 320
  #define LCD_PIXEL_OFFSET_Y    48
#endif
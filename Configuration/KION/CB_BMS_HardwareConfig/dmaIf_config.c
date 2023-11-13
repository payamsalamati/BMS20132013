/**
 * @file dmaIf_config.c
 * @copyright (c) Futavis GmbH, Aachen 2020 - alle Rechte vorbehalten
 * @brief Short description
 * @details
 *  <b>Beschreibung</b>
 *
 *  Detaillierte Beschreibung des Moduls
 *
 */


//***************************************************************************//
//************************** INCLUDES ***************************************//
//***************************************************************************//

#include "dmaIf.h"
#include "reg_crc.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//

extern const uint32_t _paramram_start;
extern const uint32_t _paramram_sizeIn64Bit;

//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

const DmaConfig dmaConfigPackets[] = {
    { .dmaChNr     = DMA_CH0,
      .requestLine = DMA_RQL1,
      {
          .SADD      = (uint32_t)&_paramram_start,           // MIB-SPI-RAM receive data address
          .DADD      = (uint32_t)(&(crcREG->PSA_SIGREGL1)),  // global Array
          .CHCTRL    = 0,                                    // no channel triggerd after this channel
          .FRCNT     = 1,                                    // Bocklength
          .ELCNT     = (uint32_t)&_paramram_sizeIn64Bit,     // Framelength
          .ELDOFFSET = 0,                                    // not used
          .ELSOFFSET = 0,                                    // Offset to read data in Mib_SPi_RAM
          .FRDOFFSET = 0,                                    // not used
          .FRSOFFSET = 0,                                    // not used cause only 1 frame
          .PORTASGN  = 4,                                    //
          .RDSIZE    = ACCESS_64_BIT,                        // Mib_SPi_RAM data size
          .WRSIZE    = ACCESS_64_BIT,                        // afeDmaData element size
          .TTYPE     = FRAME_TRANSFER,                       // on request transfer 1 Frame
          .ADDMODERD = ADDR_INC1,                            // increase adresse by offset
          .ADDMODEWR = ADDR_FIXED,                           // increase adresse by elementsize
          .AUTOINIT  = AUTOINIT_ON,
      } }
};

const uint8_t DMA_CONFIG_PACKETS_LENGTH = sizeof(dmaConfigPackets) / sizeof(DmaConfig);


//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

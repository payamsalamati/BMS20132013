/**
 * @file ea_config.c
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

#include "ea.h"
#include "nvm_config.h"
#include "nvm.h"

//***************************************************************************//
//************************** PRIVATE TYPEDEFS *******************************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE FUNCTION DECLARATIONS ******************//
//***************************************************************************//


//***************************************************************************//
//************************** PRIVATE VARIABLE DECLARATIONS ******************//
//***************************************************************************//

const EA_BlockConfig blockConfig[] = {
    { .blockNumber       = 1U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 4,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 128,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 18U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 100,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 31U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 35U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 700,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 123U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 8,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 124U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 328,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 165U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 700,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 253U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 258U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 263U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 268U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 273U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 278U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 283U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 288U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 293U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 298U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 303U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 308U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 313U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 318U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 323U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 328U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 333U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 338U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 343U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 348U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 353U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 358U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 363U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 368U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 373U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 378U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 383U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 388U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 393U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 398U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 403U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 431U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 459U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 487U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 515U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 543U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 571U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 599U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 627U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 655U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 683U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 711U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 739U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 767U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 795U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 823U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 851U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 879U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 907U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 935U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 963U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 991U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1019U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1047U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1075U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1103U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1131U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1159U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1187U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1215U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 220,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1243U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1280U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1317U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1354U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1391U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1428U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1465U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1502U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1539U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1576U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1613U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1650U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1687U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1724U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1761U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1798U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1835U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1872U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1909U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1946U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 1983U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2020U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2057U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2094U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2131U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2168U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2205U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2242U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2279U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2316U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 292,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2353U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2357U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2361U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2365U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2369U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2373U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2377U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2381U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2385U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2389U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2393U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2397U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2401U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2405U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2409U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2413U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2417U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2421U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2425U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2429U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2433U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2437U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2441U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2445U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2449U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2453U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2457U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2461U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2465U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2469U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2473U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 20,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2476U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 1200,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2626U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 68,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2635U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 64,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2643U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 12,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2645U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 1580,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2843U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 320,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2883U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 148,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2902U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 20,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 2905U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 1944,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3148U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 48,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3154U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 2964,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3525U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 412,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3577U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 50 },
    { .blockNumber       = 3777U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 12,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 50 },
    { .blockNumber       = 3877U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 12,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3879U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 20,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3882U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3886U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 8,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3887U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 32,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3891U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 16,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3893U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3897U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3901U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3905U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3909U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3913U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3917U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3921U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3925U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3929U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3933U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3937U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3941U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3945U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3949U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3953U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3957U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3961U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3965U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3969U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3973U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3977U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3981U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3985U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3989U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3993U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 3997U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 4001U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 4005U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 4009U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 4013U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 40004,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 9014U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 28,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 9018U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 56,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 9025U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 196,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 9050U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 44,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 9056U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 228,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 9085U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 84,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 9096U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 48,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 9102U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 76,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 },
    { .blockNumber       = 9112U << NVM_DATASET_SELECTION_BITS,
      .blockSize         = 12,
      .deviceIndex       = 0,
      .usedDatasetBlocks = 1 }

};

const EA_Config eaCfg = {
    .blockConfig     = &blockConfig[0],
    .blockConfigSize = sizeof(blockConfig) / sizeof(EA_BlockConfig)
};

//***************************************************************************//
//************************** PRIVATE FUNCTION DEFINITIONS *******************//
//***************************************************************************//


//***************************************************************************//
//************************** PUBLIC FUNCTION DEFINITIONS * ******************//
//***************************************************************************//

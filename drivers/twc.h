/**
 * @file twc.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#ifndef __TWC_H
#define __TWC_H
#include "phnx02.h"
// twc_cr
#define TWC_CR_RXRECEN BIT(8)
#define TWC_CR_SEBUSMODE BIT(7)
#define TWC_CR_SEBUSEN BIT(6)
#define TWC_CR_TXLELCFG BIT(5)
#define TWC_CR_RXDECCFG BIT(4)
#define TWC_CR_RXGLITCHFILTCFG BITS(0, 3) //[0-0x0f] = 0-30cycle

// twc_swcr
#define TWC_SWCR_RXPARITYCFG BIT(4)
#define TWC_SWCR_TXCODECFG BIT(3)
#define TWC_SWCR_TXPARITYCFG BIT(2)
#define TWC_SWCR_TXBITCFG BITS(0, 1)

#define TWC_SWCR_TXBITCFG_8BIT (0 << 0) // send from lsb to msb
#define TWC_SWCR_TXBITCFG_16BIT (1 << 0)
#define TWC_SWCR_TXBITCFG_24BIT (2 << 0)
#define TWC_SWCR_TXBITCFG_32BIT (3 << 0)

// twc_swbr
#define TWC_SWBR_TXBR BITS(4, 7)
#define TWC_SWBR_TXBR_1K (0 << 4)
#define TWC_SWBR_TXBR_2K (1 << 4)
#define TWC_SWBR_TXBR_3K (2 << 4)
#define TWC_SWBR_TXBR_4K (3 << 4)
#define TWC_SWBR_TXBR_5K (4 << 4)
#define TWC_SWBR_TXBR_6K (5 << 4)
#define TWC_SWBR_TXBR_8K (6 << 4)
#define TWC_SWBR_TXBR_10K (7 << 4)
#define TWC_SWBR_TXBR_12K (8 << 4)
#define TWC_SWBR_TXBR_15K (9 << 4)
#define TWC_SWBR_TXBR_20K (10 << 4)
#define TWC_SWBR_TXBR_25K (11 << 4)
#define TWC_SWBR_TXBR_30K (12 << 4)
#define TWC_SWBR_TXBR_40K (13 << 4)
#define TWC_SWBR_TXBR_50K (14 << 4)
#define TWC_SWBR_TXBR_60K (15 << 4)

#define TWC_SWBR_RXBR BITS(0, 3)
#define TWC_SWBR_RXBR_1K (0 << 0)
#define TWC_SWBR_RXBR_2K (1 << 0)
#define TWC_SWBR_RXBR_3K (2 << 0)
#define TWC_SWBR_RXBR_4K (3 << 0)
#define TWC_SWBR_RXBR_5K (4 << 0)
#define TWC_SWBR_RXBR_6K (5 << 0)
#define TWC_SWBR_RXBR_8K (6 << 0)
#define TWC_SWBR_RXBR_10K (7 << 0)
#define TWC_SWBR_RXBR_12K (8 << 0)
#define TWC_SWBR_RXBR_15K (9 << 0)
#define TWC_SWBR_RXBR_20K (10 << 0)
#define TWC_SWBR_RXBR_25K (11 << 0)
#define TWC_SWBR_RXBR_30K (12 << 0)
#define TWC_SWBR_RXBR_40K (13 << 0)
#define TWC_SWBR_RXBR_50K (14 << 0)
#define TWC_SWBR_RXBR_60K (15 << 0)

// twc_gapw
#define TWC_GAPW_GAPCOMP BITS(8, 14)
#define TWC_GAPW_GAPCYC BITS(0, 7)

#define TWC_GAPW_GAPCOMP_pos (8)
#define TWC_GAPW_GAPCYC_pos (0)

// twc_cmd
#define TWC_CMD_CMD BITS(16, 31)
#define TWC_CMD_MSK BITS(0, 16)

// twc_txs
#define TWC_TXS_TXSTART BIT(1)
#define TWC_TXS_DATATXEN BIT(0)

// twc_inten
#define TWC_INTEN_RXFRAMENDINTEN BIT(1)
#define TWC_INTEN_TXDATAENDINTEN BIT(0)

// twc_sts
// #define TWC_STS_RXSTATE         BITS(22,23)
// #define TWC_STS_TXSTATE         BITS(20,21)
#define TWC_STS_HANMCHKPAR BITS(14, 19)
#define TWC_STS_RXPARITY BITS(8, 13)
#define TWC_STS_RXPARERR BIT(7)
#define TWC_STS_RXBITERR BIT(6)
#define TWC_STS_RXFRMEERR BIT(5)
#define TWC_STS_RXMUTEFRME BIT(4)
#define TWC_STS_RXDATLEV BIT(2)
#define TWC_STS_RXFRMEEND BIT(1)
#define TWC_STS_TXDATAEND BIT(0)

// extend define
#define TWC_PIN_18_19 0
#define TWC_PIN_10_11 1

typedef enum _FARM_END {
    TWC_RX_FRAME_END = (1 << 1),
    TWC_TX_FRAME_END = (1 << 0),
} eTansferEnd_Type;

#define TWC_MODE_9000 0
#define TWC_MODE_EPC 1

#define TWC_TX_LEVEL_HIGH_EN 1
#define TWC_TX_LEVEL_LOW_EN 0

#define TWC_RX_DEC_MATCH_CMD_INT 0
#define TWC_RX_DEC_NO_MT_CMD_INT 1

#define TWC_RX_FILT_NO 0
#define TWC_RX_FILT_2N_CYCLE(n) (n) // 1<x<15, 1-30cycle

typedef struct _SWAN {
    int txLelCfg;        // TWC_TX_LEVEL_HIGH_EN or TWC_TX_LEVEL_LOW_EN
    int rxDecCfg;        // TWC_RX_DEC_MATCH_CMD_INT or TWC_RX_DEC_NO_MT_CMD_INT
    int rxGlitchFiltCfg; // TWC_RX_FILT_NO or TWC_RX_FILT_2N_CYCLE(n)

    int rxParityCfg; // TWC_RX_PARITY_HMM or TWC_RX_PARITY_EVEN
    int txCodeCfg;   // TWC_TX_CODE_MCT or TWC_TX_CODE_NRZ
    int txParityCfg; // TWC_TX_PARITY_ODD or TWC_TX_PARITY_EVEN
    int txBitCfg; // TWC_TX_BIT_8BIT or TWC_TX_BIT_16BIT or TWC_TX_BIT_24BIT or
                  // TWC_TX_BIT_32BIT
} sSwanBusCfgParam;

#define TWC_RX_PARITY_HMM 1
#define TWC_RX_PARITY_EVEN 0

#define TWC_TX_CODE_MCT 1
#define TWC_TX_CODE_NRZ 0

#define TWC_TX_PARITY_ODD 1
#define TWC_TX_PARITY_EVEN 0

#define TWC_TX_BIT_8BIT 0
#define TWC_TX_BIT_16BIT 1
#define TWC_TX_BIT_24BIT 2
#define TWC_TX_BIT_32BIT 3

#define TWC_CMD_1 1
#define TWC_CMD_2 2
#define TWC_CMD_3 3
#define TWC_CMD_4 4

// extern function declare
void TWC_Init(int pin);
void TWC_DeInit(void);
void TWC_RecieveControl(ControlStatus clt);
void TWC_SEBUSConfig(int mode, int txLelCfg, int rxDecCfg, int rxGlitchFiltCfg);
void TWC_SetGapAndGapComp(int gap, int gapComp);
void TWC_SWANBusConfig(int txBaud, int rxBaud, sSwanBusCfgParam *pParam);
void TWC_SetCMDAndMask(int cmdRegNo, u16 cmd, u16 msk);
u32 TWC_ReadData(void);
void TWC_WriteData(u32 dat);
// void TWC_SendControl(ControlStatus ctl);
void TWC_SendEnable(void);  // gcc inline
void TWC_SendDisable(void); // gcc inline
void TWC_SwanBusSendStart(void);
void TWC_EnableIRQ(eTansferEnd_Type val);
void TWC_ClrIRQFlag(eTansferEnd_Type val);

#endif

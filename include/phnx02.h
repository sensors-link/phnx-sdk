/**
 * @file phnx02.h
 * @author bifei.tang
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */
#ifndef _PHNX02_H
#define _PHNX02_H

#ifdef cplusplus
extern "C" {
#endif
/* IO definitions (access restrictions to peripheral registers) */
/**

  <strong>IO Type Qualifiers</strong> are used
  \li to specify the access to peripheral variables.
  \li for automatic generation of peripheral register debug information.
  */
#ifdef __cplusplus
#define __I volatile /*!< Defines 'read only' permissions                 */
#else
#define __I                                                                    \
    volatile const /*!< Defines 'read only' permissions                 */
#endif
#define __O volatile  /*!< Defines 'write only' permissions                */
#define __IO volatile /*!< Defines 'read / write' permissions              */

/* define interrupt number */
typedef enum IRQn {
    /* ---------------------  Phonix02 Specific Interrupt Numbers ------------*/
    RSV_IRQn = 0,    /*!< Reserved Interrupt						*/
    PMU_IRQn = 1,    /*!< PMU Interrupt							*/
    LPT_IRQn = 2,    /*!< LPT Interrupt						*/
    TIMER1_IRQn = 3, /*!< TIMER1 Interrupt					*/
    TIMER2_IRQn = 4, /*!< TIMER2 Interrupt									*/
    TIMER3_IRQn = 5, /*!< TIMER3 Interrupt									*/
    TIMER4_IRQn = 6, /*!< TIMER4 Interrupt									*/
    UART1_IRQn = 7,  /*!< UART1 Interrupt							*/
    UART2_IRQn = 8,  /*!< UART2 Interrupt									*/
    SPI_IRQn = 9,    /*!< SPI Interrupt									*/
    ANAC_IRQn = 10,  /*!< ANAC Interrupt										*/
    EFC_IRQn = 11,   /*!< EFC Interrupt										*/
    IOM_IRQn = 12,   /*!< IOM Interrupt						*/
    I2C_IRQn = 13,   /*!< I2C Interrupt					*/
    RTC_IRQn = 14,   /*!< RTC Interrupt						*/
    TWC_IRQn = 15,   /*!< TWC Interrupt						*/
    LPU_IRQn = 16,   /*!< LPU Interrupt*/
} IRQn_Type;

//
#include "risc_v_csr.h"
#include "system_phnx02.h"
/* ================================================================================*/
/* ================                       EFC ================ */
/* ================================================================================*/

/**
 * @brief Embeded Flash Control (EFC)
 */
#pragma pack(1)
typedef struct { /*!< EFC Structure          */
    union {
        __IO unsigned int CR; /*!< Control Register */
        __IO struct {
            unsigned int CDINTEN : 1;
            unsigned int FCINTEN : 1;
            unsigned int PVEINTEN : 1;
            unsigned int EVEINTEN : 1;
            unsigned int ADDREINTEN : 1;
            unsigned int FTTEINTEN : 1;
            unsigned int ATTEINTEN : 1;
            unsigned int ATDEINTEN : 1;
            unsigned int LVDWARNEN : 1;
            unsigned int PMRDEN : 1;
            unsigned int EMRDEN : 1;
            unsigned int NRDDLY : 1;
            unsigned int MRDCYC : 4;
            unsigned int PRG2MDIV : 6;
            unsigned int ERS2KDIV : 10;
        } sCR;
    };
    union {
        __IO unsigned int
            TNVS; /*!< ROG/ERASE/CEb/NVR/ADDRESS to Web Setup time */
        __IO struct {
            unsigned int TNVS : 4;
            unsigned int rsv : 28;
        } sTNVS;
    };
    union {
        __IO unsigned int
            TPROG; /*!< PROG/ERASE/CEb/NVR/ADDRESS to Web Setup time          */
        __IO struct {
            unsigned int TPROG : 4;
            unsigned int rsv : 28;
        } sTROG;
    };
    union {
        __IO unsigned int TPGS; /*!< WEb low to PROG2 high Setup time */
        __IO struct {
            unsigned int TPGS : 4;
            unsigned int rsv : 28;
        } sTPGS;
    };
    union {
        __IO unsigned int TRCV; /*!< Program Recovery Time */
        __IO struct {
            unsigned int TCERCV : 9;
            unsigned int TSERCV : 7;
            unsigned int TPRCV : 4;
        } sTRCV;
    };
    union {
        __IO unsigned int TERASE; /*!< Erase time */
        __IO struct {
            unsigned int TCERS : 7;
            unsigned int TSERS : 4;
        } sTERASE;
    };
    union {
        __O unsigned int WPT; /*!< Write Protect Register     */
        __IO struct {
            unsigned int WPT : 8;
            unsigned int rsv : 24;
        } sWPT;
    };
    union {
        __IO unsigned int OPR; /*!< OPR Flow Register    */
        __IO struct {
            unsigned int OPRMODE : 4;
            unsigned int OPRF : 4;
            unsigned int WE : 1;
            unsigned int rsv : 26;
        } sOPR;
    };
    union {
        __I unsigned int PVEV; /*!< Verify Register    */
        __IO struct {
            unsigned int PVCNT : 6;
            unsigned int Rev : 1;
            unsigned int EVCNT : 7;

        } sPVEV;
    };
    union {
        __IO unsigned int STS; /*!< Verify Register    */
        __IO struct {
            unsigned int CD : 1;
            unsigned int FCE : 1;
            unsigned int PVE : 1;
            unsigned int EVE : 1;
            unsigned int ADDRE : 1;
            unsigned int FTTE : 1;
            unsigned int ATTE : 1;
            unsigned int ATDE : 1;

        } sSTS;
    };
} EFC_Type;

typedef struct {
    __I unsigned int Rsv[0x04 / 4];
    union {
        __IO unsigned int CRC_RSL;
        __IO struct {
            unsigned int CRC16 : 16;
            unsigned int CHKPSS : 1;

        } sCRC_RSL;
    };
    __I unsigned int RSV[0x80 / 4 - 2];
    union {
        __IO unsigned int CRC_DAT;
        __IO struct { unsigned int CRC_DAT : 32; } sCRC_DAT;
    };
} CRC_Type;

/* ================================================================================
 */
/* ================                      SYSC ================ */
/* ================================================================================
 */

/**
 * @brief System Control (SYSC)
 */

typedef struct { /*!< SYSC Structure             */
    union {
        __IO unsigned int CLKCTRCFG; /*!< CLKCTRCFG */
        __IO struct {
            unsigned int REV1 : 4;
            unsigned int SYS_CLK_SEL : 2;
            unsigned int REV2 : 2;
            unsigned int SRC_CLK_DIV1 : 7;
            unsigned int REV3 : 1;
            unsigned int SRC_CLK_DIV2 : 7;
            unsigned int DSP_WKUP_DLY : 9;

        } sCLKCTRCFG;
    };
    __O unsigned int WRPROCFG; /*!< WRPROCFG   */
    union {
        __IO unsigned int CLKENCFG;
        __IO struct {
            unsigned int APB_CKEN : 1;
            unsigned int I2C_PCKEN : 1;
            unsigned int SPI_PCKEN : 1;
            unsigned int UART1_PCKEN : 1;
            unsigned int UART2_PCKEN : 1;
            unsigned int TIMER_PCKEN : 1;
            unsigned int TIMER1_PCKEN : 1;
            unsigned int TIMER2_PCKEN : 1;
            unsigned int TIMER3_PCKEN : 1;
            unsigned int TIMER4_PCKEN : 1;
            unsigned int IOM_PCKEN : 1;
            unsigned int DCLK_HCKEN : 1;
            unsigned int ANAC_PCKEN : 1;
            unsigned int PMU_PCKEN : 1;
            unsigned int LPWDT_PCKEN : 1;
            unsigned int LPTIM_PCKEN : 1;
            unsigned int CRC_HCKEN : 1;
            unsigned int LPRTC_PCKEN : 1;
            unsigned int LPUART_PCKEN : 1;
            unsigned int TWC_PCKEN : 1;
            unsigned int LPUART_MRCKEN : 1;
            unsigned int TWC_MRCKEN : 1;

        } sCLKENCFG;
    };
    union {
        __O unsigned int MSFTRSTCFG;
        __IO struct {
            unsigned int I2C_PSFT_RST : 1;
            unsigned int SPI_PSFT_RST : 1;
            unsigned int UART1_PSFT_RST : 1;
            unsigned int UART2_PSFT_RST : 1;
            unsigned int TIMER_PSFT_RST : 1;
            unsigned int CRC_HSFT_RST : 1;
            unsigned int HCLK_SFT_RST : 1;
            unsigned int ANAC_SFT_RST : 1;
            unsigned int LPUART_SFT_RST : 1;
            unsigned int TWC_SFT_RST : 1;

        } sMSFTRSTCFG;
    };
    __IO unsigned int RSV[1];
    union {
        __IO unsigned int TESTCKSEL;
        __IO struct {
            unsigned int TEST_CLK_DIV : 7;
            unsigned int TEST_CLK_CKEN : 1;

        } sTESTCKSEL;
    };
    union {
        __IO unsigned int ANCLKDIV;
        __IO struct {
            unsigned int ANAC_SCLK_DIV : 4;
            unsigned int ANAC_500K_CLK_DIV : 5;

        } sANCLKDIV;
    };
    __IO unsigned int TIMCLKDIV;
    __IO unsigned int BZTIMCLKDIV;
} SYSC_Type;

/* ================================================================================
 */
/* ================                     TIMERS ================ */
/* ================================================================================
 */

/**
 * @brief Timer Control (TIMERS)
 */

typedef struct { /*!< TIMERS Structure             */
    union {
        __IO unsigned int CON; /*!< TIMCON    */
        __IO struct {
            unsigned int TE : 4;
            unsigned int TM : 4;
            unsigned int IE : 4;
            unsigned int PWM : 4;
            unsigned int EXTEN : 4;
            unsigned int EXTPOL : 4;
            unsigned int PAUSE : 4;

        } sCON;
    };
    __I unsigned int INTFLAG; /*!< TIMINTFLAG */
    __O unsigned int INTCLR;  /*!< TIMINTCLR  */
} TIMERS_Type;

/* ================================================================================
 */
/* ================                      TIM0 ================ */
/* ================================================================================
 */

/**
 * @brief Timer Control (TIM0)
 */

typedef struct {             /*!< TIM0 Structure            */
    __IO unsigned int CTCG1; /*!< TIMCTCG1 */
    __IO unsigned int CTCG2; /*!< TIMCTCG2 */
    __I unsigned int CTVAL;  /*!< TIMCTVAL  */
    union {
        __IO unsigned int PWCON; /*!< TIMPWCON */
        __IO struct {
            unsigned int DTUGAP : 16;
            unsigned int DTEN : 1;
            unsigned int PWMCPOL : 2;

        } sPWCON;
    };
} TIM_Type;

/* ================================================================================
 */
/* ================                       I2C ================ */
/* ================================================================================
 */

/**
 * @brief I2C Control (I2C)
 */

typedef struct { /*!< I2C Structure               */
    union {
        __IO unsigned int CON; /*!< I2C_CON     */
        __IO struct {
            unsigned int ENABLE : 1;
            unsigned int MASTER : 1;
            unsigned int SLAVE : 1;
            unsigned int RESTART_EN : 1;
            unsigned int GCEN : 1;
            unsigned int Rev1 : 13;
            unsigned int RXFIE : 1;
            unsigned int Rev2 : 1;
            unsigned int TXEIE : 1;
            unsigned int RDRIE : 1;
            unsigned int TXABIE : 1;
            unsigned int RXDIE : 1;
            unsigned int ACTIE : 1;
            unsigned int STPIE : 1;
            unsigned int STIE : 1;
            unsigned int GEIE : 1;

        } sCON;
    };
    union {
        __IO unsigned int ADDR; /*!< I2C_ADDR    */
        __IO struct {
            unsigned int IC_TAR : 7;
            unsigned int rsv : 9;
            unsigned int IC_SAR : 7;

        } sADDR;
    };
    union {
        __IO unsigned int DATACMD; /*!< I2C_DATACMD */
        __IO struct {
            unsigned int DATA : 8;
            unsigned int WREN : 1;
            unsigned int STOP : 1;
            unsigned int RESTART : 1;

        } sDATACMD;
    };
    union {
        __IO unsigned int SCLCR; /*!< I2C_SCLCR     */
        __IO struct {
            unsigned int LCNT : 9;
            unsigned int rsv : 7;
            unsigned int HCNT : 9;
        } sSCLCR;
    };
    union {
        __IO unsigned int ISR; /*!< I2C_ISR     */
        __IO struct {
            unsigned int Rev1 : 1;
            unsigned int Rev2 : 1;
            unsigned int R_RX_FULL : 1;
            unsigned int Rev3 : 1;
            unsigned int R_TX_EMPTY : 1;
            unsigned int R_RD_REQ : 1;
            unsigned int R_TX_ABRT : 1;
            unsigned int R_RX_DONE : 1;
            unsigned int R_ACTIVITY : 1;
            unsigned int R_STOP_DET : 1;
            unsigned int R_START_DET : 1;
            unsigned int R_GEN_CALL : 1;
            unsigned int Rev4 : 4;
            unsigned int ACTIVITY : 1;
            unsigned int ABRT_7B_ADDR_NOACK : 1;
            unsigned int ABRT_GCALL_NOACK : 1;
            unsigned int ARB_LOST : 1;
            unsigned int ABRT_SLV_ARBLOST : 1;
        } sISR;
    };
    union {
        __IO unsigned int TIMING; /*!< I2C_TIMING  */
        __IO struct {
            unsigned int IC_SDA_SETUP : 4;
            unsigned int IC_SDA_TX_HOLD : 4;
            unsigned int IC_SDA_RX_HOLD : 4;

        } sTIMING;
    };
} I2C_Type;

typedef struct {
    union {
        __IO unsigned int CR0;
        __IO struct {
            unsigned int SCLKDIV : 3;
            unsigned int MSMODE : 1;
            unsigned int DONEIE : 1;
            unsigned int MSTCFIE : 1;
            unsigned int CPHA : 1;
            unsigned int CPOL : 1;

        } sCR0;
    };
    __IO unsigned int CSN;
    union {
        __I unsigned int SR;
        __IO struct {
            unsigned int DONESR : 1;
            unsigned int MSTCFSR : 1;
            unsigned int SPI_CS : 1;

        } sSR;
    };
    __IO unsigned int DR;
} SPI_Type;

typedef struct {
    union {
        __IO unsigned int SCON;
        __IO struct {
            unsigned int SFDEN : 1;
            unsigned int TIEN : 1;
            unsigned int RIEN : 1;
            unsigned int RXSIEN : 1;
            unsigned int TB8 : 1;
            unsigned int RB8 : 1;
            unsigned int REN : 1;
            unsigned int SM2 : 1;
            unsigned int SM01 : 2;
            unsigned int LPMODE : 1;
            unsigned int PACFG : 1;

        } sSCON;
    };
    __IO unsigned int SBUF;
    __IO unsigned int SADDR;
    __IO unsigned int SADEN;
    union {
        __IO unsigned int ISR;
        __IO struct {
            unsigned int TI : 1;
            unsigned int RI : 1;
            unsigned int FE : 1;
            unsigned int PE : 1;
            unsigned int RXSF : 1;

        } sISR;
    };
    __IO unsigned int BDIV;
} UART_Type;

typedef struct {
    union {
        __IO unsigned int CR;
        __IO struct {
            unsigned int RXGLITCHFILTCFG : 4;
            unsigned int RXDECCFG : 1;
            unsigned int TXLELCFG : 1;
            unsigned int SEBUSEN : 1;
            unsigned int SEBUSMODE : 1;
            unsigned int RXRECEN : 1;

        } sCR;
    };
    union {
        __IO unsigned int SWCR;
        __IO struct {
            unsigned int TXBITCFG : 2;
            unsigned int TXPARITYCFG : 1;
            unsigned int TXCODECFG : 1;
            unsigned int RXPARITYCFG : 1;

        } sSWCR;
    };
    __IO unsigned int SWBR;
    union {
        __IO unsigned int GAPW;
        __IO struct {
            unsigned int GAPCYC : 8;
            unsigned int GAPCOMP : 7;
        } sGAPW;
    };
    union {
        __IO unsigned int CMD1;
        __IO struct {
            unsigned int MSK : 16;
            unsigned int CMD : 16;
        } sCMD1;
    };
    union {
        __IO unsigned int CMD2;
        __IO struct {
            unsigned int MSK : 16;
            unsigned int CMD : 16;
        } sCMD2;
    };
    union {
        __IO unsigned int CMD3;
        __IO struct {
            unsigned int MSK : 16;
            unsigned int CMD : 16;
        } sCMD3;
    };
    union {
        __IO unsigned int CMD4;
        __IO struct {
            unsigned int MSK : 16;
            unsigned int CMD : 16;
        } sCMD4;
    };
    __I unsigned int RXD;
    __IO unsigned int TXD;
    union {
        __IO unsigned int TXS;
        __IO struct {
            unsigned int DATATXEN : 1;
            unsigned int SOFTTXSTART : 1;
        } sTXS;
    };
    union {
        __IO unsigned int INTEN;
        __IO struct {
            unsigned int RXFRMEENDINTEN : 1;
            unsigned int TXDATAENDINTEN : 1;
        } sINTEN;
    };
    union {
        __IO unsigned int STS;
        __IO struct {
            unsigned int TXDATAEND : 1;
            unsigned int RXFRMEEND : 1;
            unsigned int RXDATLEV : 1;
            unsigned int Rev : 1;
            unsigned int RXMUTEFRME : 1;
            unsigned int RXFRMEERR : 1;
            unsigned int RXBITERR : 1;
            unsigned int RXPARERR : 1;
            unsigned int RXPARITY : 6;
            unsigned int HANMCHKPAR : 6;

        } sSTS;
    };
    __I unsigned int DBG;
} TWC_Type;

typedef struct {
    __IO unsigned int RSV[1]; // 00
    union {
        __IO unsigned int LED_CFG; // 04
        __IO struct {
            unsigned int IIRLED_EN : 1;
            unsigned int IIRLED_CC : 5;
            unsigned int IBLUE_EN : 1;
            unsigned int IBULE_CC : 5;
            unsigned int INDLED_EN : 1;
            unsigned int LED_SEL : 1;

        } sLED_CFG;
    };
    union {
        __IO unsigned int PDSENS_CFG; // 08
        __IO struct {
            unsigned int EN : 1;
            unsigned int RST : 1;
            unsigned int GC : 5;
            unsigned int CHRG : 1;

        } sPDSENS_CFG;
    };
    union {
        __IO unsigned int DC_CFG; // 0c
        __IO struct {
            unsigned int DCDC_EN : 1;
            unsigned int IPK : 2;
            unsigned int VSL : 2;
            unsigned int VOTRIM : 2;
            unsigned int TONTRIM : 2;
            unsigned int VOSW : 2;
            unsigned int DISCH : 1;
            unsigned int Rev : 4;
            unsigned int BZ_EN : 1;
            unsigned int MSEL : 1;
            unsigned int PWM_SEL : 2;

        } sDC_CFG;
    };
    union {
        __IO unsigned int CMP_CFG; // 10
        __IO struct {
            unsigned int CMP_EN : 1;
            unsigned int INV : 1;
            unsigned int VIPSEL : 3;
            unsigned int VINSEL : 3;
            unsigned int HYSSEL : 2;

        } sCMP_CFG;
    };
    union {
        __IO unsigned int ADC_CFG; // 14
        __IO struct {
            unsigned int VOLTREF_EN : 1;
            unsigned int VOLTREF_VRSEL : 3;
            unsigned int VRSEL : 2;
            unsigned int BUFEN : 1;
            unsigned int CHSEL : 4;

        } sADC_CFG;
    };
    union {
        __IO unsigned int ADC_CTL; // 18
        __IO struct {
            unsigned int ADC_EN : 1;
            unsigned int ADC_IE : 1;
            unsigned int SST : 1;
            unsigned int MULTI_MODE : 1;
            unsigned int SMP_CYCLE : 2;
            unsigned int SMP_TIME : 2;

        } sADC_CTL;
    };
    union {
        __IO unsigned int ANAC_CFG; // 1c
        __IO struct {
            unsigned int SLDO_VRSEL : 2;
            unsigned int ALDO4D_EN : 1;
            unsigned int ALDO4D_LPEN : 1;
            unsigned int Rev : 2;
            unsigned int BGR_EN : 1;
            unsigned int ALDO4A_EN : 1;
            unsigned int ALDO4A_VOSEL : 2;
            unsigned int BVS_EN : 1;
            unsigned int BVS_ISNKSEL : 4;
            unsigned int THERMD_EN : 1;
            unsigned int INTF_ISOEN : 1;

        } sANAC_CFG;
    };
    union {
        __IO unsigned int LVD_CFG; // 20
        __IO struct {
            unsigned int LVD_EN : 1;
            unsigned int SRCSEL : 2;
            unsigned int VTSEL : 4;
            unsigned int LVD_IE : 1;
            unsigned int FLT : 8;

        } sLVD_CFG;
    };
    union {
        __IO unsigned int CLK_CFG; // 24
        __IO struct {
            unsigned int LRC_EN : 1;
            unsigned int HRC_EN : 1;
            unsigned int HRC_FSEL : 3;
            unsigned int XTL_EN : 1;
            unsigned int XTL_CSET : 6;
            unsigned int XTL_RTRIM : 2;
            unsigned int XTH_EN : 1;
            unsigned int MRC_EN : 1;
            unsigned int HRC_DLYTRIM : 1;

        } sCLK_CFG;
    };
    __IO unsigned int HRC_TRIM;  // 28
    __IO unsigned int LRC_TRIM;  // 2c
    __IO unsigned int CMP_TRIM;  // 30
    __IO unsigned int BG4A_TRIM; // 34
    __IO unsigned int BG4S_TRIM; // 38
    __IO unsigned int TESTCTL;   // 3c
    __IO unsigned int AINSEL;    // 40
    __IO unsigned int MRC_TRIM;  // 44
    union {
        __IO unsigned int DLY_CFG; // 48
        __IO struct {
            unsigned int BGR_DLY : 2;
            unsigned int ALDO4A_DLY : 2;
            unsigned int ADC_DLY : 2;
            unsigned int TEMP_DLY : 2;
            unsigned int PDSENS_RST_DLY : 2;
            unsigned int SMOKE_DLY : 8;
            unsigned int LED_PW : 8;

        } sDLY_CFG;
    };
    union {
        __IO unsigned int ME_CTL; // 4c
        __IO struct {
            unsigned int ANAC_EN : 1;
            unsigned int ME_RST : 1;
            unsigned int THR_IE : 1;
            unsigned int ME_MODE : 1;
            unsigned int ME_AUTO : 1;
            unsigned int MODE_SEL : 2;
            unsigned int THRCMP_EN : 1;
            unsigned int ADC_TRIG_SEL : 3;

        } sME_CTL;
    };
    union {
        __IO unsigned int ANAC_FLAG; // 50
        __IO struct {
	    unsigned int ADC_INTF:1;
	    unsigned int THR_INTF:1;
	    unsigned int LVD_INTF:1;
	    unsigned int ANA_OK_INTF:1;
	    unsigned int Rev:1;
	    unsigned int DCDC_VOK:1;
	    unsigned int LVD_OUT:1;
	    unsigned int CMP_OUT:1;
	    unsigned int BZ_FO:1;
        } sANAC_FLAG;
    };
    __IO unsigned int TEST;      // 54
    __O unsigned int WPROT;      // 58
    __IO unsigned int THR1_DATA; // 5c
    __IO unsigned int THR2_DATA; // 60
    __I unsigned int rsv0[7];
    __IO unsigned int ADC_VAL[8]; // 80
    __IO unsigned int AVG_VAL;    // A0
} ANAC_Type;

typedef struct {
    __IO unsigned int DATA;
    __IO unsigned int OE;
    __IO unsigned int PU;
    __IO unsigned int PD;
    __IO unsigned int OTYPE;
    __IO unsigned int ADS;
    __IO unsigned int DRS;
    union {
        __IO unsigned int AF0;
        __IO struct {
            unsigned int P00_SEL : 2;
            unsigned int P01_SEL : 2;
            unsigned int P02_SEL : 2;
            unsigned int P03_SEL : 2;
            unsigned int P04_SEL : 2;
            unsigned int P05_SEL : 2;
            unsigned int P06_SEL : 2;
            unsigned int P07_SEL : 2;
            unsigned int P08_SEL : 2;
            unsigned int P09_SEL : 2;
            unsigned int P10_SEL : 2;
            unsigned int P11_SEL : 2;
            unsigned int P12_SEL : 2;
            unsigned int P13_SEL : 2;
            unsigned int P14_SEL : 2;
            unsigned int P15_SEL : 2;

        } sAF0;
    };
    union {
        __IO unsigned int AF1;
        __IO struct {
            unsigned int P16_SEL : 2;
            unsigned int P17_SEL : 2;
            unsigned int P18_SEL : 2;
            unsigned int P19_SEL : 2;
        } sAF1;
    };
    __IO unsigned int INT_TYPE;
    __IO unsigned int INT_POLARITY;
    __IO unsigned int EXT_INTE;
    __IO unsigned int INTF;
    union {
        __IO unsigned int CTL;
        __IO struct {
            unsigned int INTE : 1;
            unsigned int DEBOUNCE : 1;
            unsigned int LS_SYNC : 1;

        } sCTL;
    };

} IOM_Type;

typedef struct {
    union {
        __IO unsigned int CON;
        __IO struct {
            unsigned int PRDX : 6;
            unsigned int Rev1 : 1;
            unsigned int PRDSEL : 1;
            unsigned int PRDS : 3;
            unsigned int Rev2 : 5;
            unsigned int WAIT : 1;
            unsigned int Rev3 : 3;
            unsigned int PRDIE : 1;
            unsigned int PRDEN : 1;
            unsigned int ALMIE : 1;
            unsigned int ALMEN : 1;
            unsigned int FMT : 1;
            unsigned int Rev4 : 3;
            unsigned int CKSEL : 3;
            unsigned int RTCEN : 1;

        } sCON;
    };
    union {
        __IO unsigned int STS;
        __IO struct {
            unsigned int ALMF : 1;
            unsigned int Rev2 : 3;
            unsigned int PRDF : 1;
            unsigned int Rev1 : 3;
            unsigned int WAITF : 1;

        } sSTS;
    };
    union {
        __IO unsigned int TR;
        __IO struct {
            unsigned int SECL : 4;
            unsigned int SECH : 3;
            unsigned int Rev1 : 1;
            unsigned int MINL : 4;
            unsigned int MINH : 3;
            unsigned int Rev2 : 1;
            unsigned int HOURL : 4;
            unsigned int HOURH : 2;

        } sTR;
    };
    union {
        __IO unsigned int DR;
        __IO struct {
            unsigned int DAYL : 4;
            unsigned int DAYH : 2;
            unsigned int Rev1 : 2;
            unsigned int WEEK : 3;
            unsigned int Rev2 : 5;
            unsigned int MON : 5;
            unsigned int Rev3 : 3;
            unsigned int YEARL : 4;
            unsigned int YEARH : 4;

        } sDR;
    };
    union {
        __IO unsigned int ALM;
        __IO struct {
            unsigned int ALMMINL : 4;
            unsigned int ALMMINH : 3;
            unsigned int Rev1 : 1;
            unsigned int ALMHOURL : 4;
            unsigned int ALMHOURH : 2;
            unsigned int Rev2 : 2;
            unsigned int ALMWEEK : 7;

        } sALM;
    };
    union {
        __IO unsigned int CALR;
        __IO struct {
            unsigned int CR : 9;
            unsigned int Rev : 4;
            unsigned int ONE_HZ_OE : 1;
            unsigned int CAL_SEL : 1;
            unsigned int CAL_EN : 1;

        } sCALR;
    };
    __O unsigned int WPR;

} RTC_Type;

typedef struct {
    union {
        __IO unsigned int CR;
        __IO struct {
            unsigned int PDNEN : 4;
            unsigned int LVDCHIPRSTEN : 1;
            unsigned int LPCLKSEL : 1;
            unsigned int LPTCLKEN : 1;
            unsigned int WDTCLKEN : 1;
            unsigned int VDDLPCFG : 2;
            unsigned int HRCKEEPALIVE : 1;
            unsigned int Rsv : 1;
            unsigned int FLSDEEPSTB : 4;

        } sCR;
    };
    union {
        __IO unsigned int WKCFG;
        __IO struct {
            unsigned int GPIOWKEN : 4;
            unsigned int GPIOWKLEV : 4;
            unsigned int Rsv : 1;
            unsigned int PMUWKMODE : 1;

        } sWKCFG;
    };
    union {
        __O unsigned int SOFTRST;
        __IO struct {
            unsigned int SOFTCHIPRST : 1;
            unsigned int SOFTDIGRST : 1;
        } sSOFTRST;
    };
    union {
        __IO unsigned int WKSTS;
        __IO struct {
            unsigned int GPIOWKSTS : 4;
            unsigned int WDTWKSTS : 1;
            unsigned int LPTWKSTS : 1;
            unsigned int RTCWKSTS : 1;
            unsigned int LPUWKSTS : 1;
            unsigned int TWCWKSTS : 1;

        } sWKSTS;
    };
    union {
        __IO unsigned int RSTSTS;
        __IO struct {
            unsigned int LVDRSTSTS : 1;
            unsigned int WDTRSTSTS : 1;
            unsigned int EXTRSTSTS : 1;
            unsigned int SOFTCHIPRSTSTS : 1;
            unsigned int SOFTDIGRSTSTS : 1;
            unsigned int PORRSTSTS : 1;

        } sRSTSTS;
    };
    union {
        __IO unsigned int INTEN;
        __IO struct {
            unsigned int LVDRSTINTEN : 1;
            unsigned int WDTRSTINTEN : 1;
            unsigned int EXTRSTINTEN : 1;
            unsigned int SOFTCHIPRSTINTEN : 1;
            unsigned int SOFTDIGRSTINTEN : 1;
            unsigned int PORRSTINTEN : 1;
            unsigned int WDTWKINTEN : 1;
            unsigned int LPTWKINTEN : 1;
            unsigned int GPIOWKINTEN : 4;
            unsigned int RTCWKINTEN : 1;
            unsigned int LPUWKINTEN : 1;
            unsigned int TWCWKINTEN : 1;

        } sINTEN;
    };
    __O unsigned int WPT;
    __I unsigned int RSV[1];
    __IO unsigned int BAKR;

} PMU_Type;

typedef struct {
    union {
        __IO unsigned int CR;
        __IO struct {
            unsigned int EN : 1;
            unsigned int rsv : 1;
            unsigned int PITE : 1;
            unsigned int IE : 1;

        } sCR;
    };
    __IO unsigned int CFG;
    __IO unsigned int CNT;
    __IO unsigned int INTSTS;

} LPTIM_Type;

typedef struct {
    __IO unsigned int RST;
    union {
        __IO unsigned int CR;
        __IO struct {
            unsigned int WOV : 4;
            unsigned int RUN : 1;
            unsigned int INTEN : 1;
            unsigned int rsv : 1;
            unsigned int INTFLAG : 1;

        } sCR;
    };

} WDT_Type;
#pragma pack()
/* enum definitions */
typedef enum { DISABLE = 0, ENABLE = !DISABLE } EventStatus, ControlStatus;
typedef enum { FALSE = 0, TRUE = !FALSE } BOOL;
typedef enum { RESET = 0, SET = 1, MAX = 0X7FFFFFFF } FlagStatus;
typedef enum { ERROR = 0, SUCCESS = !ERROR } ErrStatus;

/* bit operations */
#define REG32(addr) (*((volatile unsigned int *)(addr)))
#define REG16(addr) (*((volatile unsigned short *)(addr)))
#define REG8(addr) (*((volatile unsigned char *)(addr)))
#define BIT(x) ((unsigned int)0x01U << (x))
#define BITS(start, end)                                                       \
    ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (end))))
#define GET_BITS(regval, start, end)                                           \
    (((regval)&BITS((start), (end))) >> (start))

/* main flash and SRAM memory map */

#define FLASH_BASE                                                             \
    ((unsigned int)0x10100000UL) /*!< main FLASH base address          */
#define SRAM_BASE                                                              \
    ((unsigned int)0x20000000UL) /*!< SRAM0 base address               */
#define PAGE_BUFF_BASE 0x101c0000UL
/* ================================================================================
 */
/* ================              Peripheral memory map ================ */
/* ================================================================================
 */

#define EFC_BASE 0x40000000UL
#define CRC_BASE 0x40000c00UL
#define SYSC_BASE 0x40001000UL
#define TIMERS_BASE 0x400100A0UL
#define TIM1_BASE 0x40010000UL
#define TIM2_BASE 0x40010014UL
#define TIM3_BASE 0x40010028UL
#define TIM4_BASE 0x4001003CUL
#define I2C_BASE 0x40010400UL
#define SPI_BASE 0x40010800UL
#define UART2_BASE 0x40010c00UL
#define UART1_BASE 0x40011000UL
#define LPUART_BASE 0x40011400UL
#define TWC_BASE 0x40011800UL
#define ANAC_BASE 0x40011c00UL
#define IOM_BASE 0x40012400UL
#define RTC_BASE 0x40012800UL
#define PMU_BASE 0x40012c00UL
#define LPTIM_BASE 0x40013000UL
#define WDT_BASE 0x40013400UL
/* ================================================================================
 */
/* ================             Peripheral declaration ================ */
/* ================================================================================
 */

#define EFC ((EFC_Type *)EFC_BASE)
#define CRC ((CRC_Type *)CRC_BASE)
#define SYSC ((SYSC_Type *)SYSC_BASE)
#define TIMERS ((TIMERS_Type *)TIMERS_BASE)
#define TIM1 ((TIM_Type *)TIM1_BASE)
#define TIM2 ((TIM_Type *)TIM2_BASE)
#define TIM3 ((TIM_Type *)TIM3_BASE)
#define TIM4 ((TIM_Type *)TIM4_BASE)
#define I2C ((I2C_Type *)I2C_BASE)
#define SPI ((SPI_Type *)SPI_BASE)
#define UART1 ((UART_Type *)UART1_BASE)
#define UART2 ((UART_Type *)UART2_BASE)
#define LPUART ((UART_Type *)LPUART_BASE)
#define TWC ((TWC_Type *)TWC_BASE)
#define ANAC ((ANAC_Type *)ANAC_BASE)
#define IOM ((IOM_Type *)IOM_BASE)
#define RTC ((RTC_Type *)RTC_BASE)
#define PMU ((PMU_Type *)PMU_BASE)
#define LPTIM ((LPTIM_Type *)LPTIM_BASE)
#define WDT ((WDT_Type *)WDT_BASE)

/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group Phonix02 */
/** @} */ /* End of group FHSJDZ */

// data type define
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef signed int s32;
typedef signed short s16;
typedef signed char s8;

#ifdef _FW_DEBUG
extern int __wrap_printf(const char *fmt, ...);
#define PARAM_CHECK(x)                                                         \
    {                                                                          \
        if (x) {                                                               \
            __wrap_printf("Wrong parameters value: file:%s,on line:%d\r\n",    \
                          __FILE__, __LINE__);                                 \
            while (1)                                                          \
                ;                                                              \
        }                                                                      \
    }
#else
#define PARAM_CHECK(x)
#endif

#ifdef cplusplus
}
#endif
#endif /* Phonix02_H */

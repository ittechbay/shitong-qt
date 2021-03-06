/*
 * Note: this file originally auto-generated by mib2c using
 *        $
 */
#ifndef FTS_SCALAR_H
#define FTS_SCALAR_H

#include "fts_cfg.h"
#define VAR_FTS_REF_CFG 0
#define VAR_FTS_REF_CURRENT 1
#define VAR_FTS_CLK_STATE 2
#define VAR_FTS_CLK_MODE 3
#define VAR_FTS_CLK_TIME_ACCURACY 4
#define VAR_FTS_CLK_FREQ_ACCURACY 5
#define VAR_FTS_CLK_TIME_THRESHOLD 6
#define VAR_FTS_CLK_GRADE 7
#define VAR_FTS_CLK_CURRENT_STATE_LAST 8
#define VAR_FTS_CLK_CLASS 9
#define VAR_FTS_NTP_NUMS 10
#define VAR_FTS_PTP_NUMS 11
#define VAR_FTS_TIMING_CFG 12
#define VAR_FTS_NULL 13

//new def for can
#define FTS_VAR_REF_CFG 0
#define FTS_VAR_REF_CURRENT 1
#define FTS_VAR_CLK_STATE 2
#define FTS_VAR_NULL 13



struct fts_scalar_data_s {
	char ftsRefCfg[FTS_STRING_LEN];
	//char *ftsRefCfg;
	//int ftsRefCfg_len;
	int ftsRefCurrent;
	int ftsClkState;
	int ftsClkMode;
	int ftsClkTimeAccuracy;
	int ftsClkFreqAccuracy;
	int ftsClkTimeThreshold;
	int ftsClkGrade;
	int ftsClkCurrentStateLast;
	int ftsClkClass;
	int ftsNtpNums;
	int ftsPtpNums;
	char ftsTimingCfg[FTS_STRING_LEN];
	//char *ftsTimingCfg;
	//int ftsTimingCfg_len;
};


/* function declarations */
void init_fts_scalar(void);
Netsnmp_Node_Handler handle_ftsRefCfg;
Netsnmp_Node_Handler handle_ftsRefCurrent;
Netsnmp_Node_Handler handle_ftsClkState;
Netsnmp_Node_Handler handle_ftsClkMode;
Netsnmp_Node_Handler handle_ftsClkTimeAccuracy;
Netsnmp_Node_Handler handle_ftsClkFreqAccuracy;
Netsnmp_Node_Handler handle_ftsClkTimeThreshold;
Netsnmp_Node_Handler handle_ftsClkGrade;
Netsnmp_Node_Handler handle_ftsClkCurrentStateLast;
Netsnmp_Node_Handler handle_ftsClkClass;
Netsnmp_Node_Handler handle_ftsNtpNums;
Netsnmp_Node_Handler handle_ftsPtpNums;
Netsnmp_Node_Handler handle_ftsTimingCfg;
void *fts_scalar_getvar(int var);
void fts_scalar_save();

void fts_scalar_set_var(int type, void *data);


#endif /* FTS_SCALAR_H */

/**
 * @file fifo_hw.h
 * @author Sami Dahoux (s.dahoux@emse.fr)
 * @brief Driver for the FIFO controller IP contained in the test system vivado_sca
 * 
 * The FIFO controller performs asymmetric operations on a FIFO :
 * - pushes values from a hardware device
 * - pops values into the CPU
 * 
 * Pushes can only be initiated and stopped by this software. 
 * The value are added to the FIFO at a sampling rate that depends on the hardware and the addition stops when the FIFO is full.
 * 
 * Pops can be initiated and stopped by this software.
 * The popped values can be read via the corresponding API.
 */

#ifndef XTDC_H
#define XTDC_H

#include "xil_io.h"
#include "xtdc_hw.h"
#include <limits.h>
#include <stdio.h>

#define DIST(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))


typedef struct
{
    u16 DeviceId;
    u32 BaseAddr;
    u8 SamplingLen;
    u8 CountTdc;
} XTDC_Config;

typedef struct
{
    XTDC_Config Config;
    u32 IsReady;
    u32 IsStarted;
} XTDC;

#define XTDC_SetId(BaseAddr, Id) \
    XTDC_WriteReg((BaseAddr), XTDC_SEL_OFFSET, (Id))

#define XTDC_ReadRaw(BaseAddr) \
    XTDC_ReadReg((BaseAddr), XTDC_RAW_OFFSET)

#define XTDC_ReadAll(BaseAddr, Offset) \
    XTDC_ReadReg((BaseAddr), (Offset) * 4)

#define XTDC_Read(BaseAddr, Id) \
    XTDC_Weight(XTDC_ReadReg(InstancePtr->Config.BaseAddr, ((Id) / 4) * 4), (Id % 4))

XTDC_Config XTDC_ConfigTable[];

u8 XTDC_RawWeight(u32 value);

int XTDC_BitPolarity(u32 value);

int XTDC_CfgInitialize(XTDC *InstancePtr, XTDC_Config *ConfigPtr);

/**
 * @brief Writes the given value of the delay into the corresponding register
 */
void XTDC_WriteDelay(XTDC *InstancePtr, int Id, u32 fine, u32 coarse);

u64 XTDC_ReadDelay(XTDC *InstancePtr, int Id);

/**
 * @brief Calibrates the TDC in order to provide the best range and sensitivity
 * 
 * The calibration tests all the delay tunning values and pick the best according to measurement.
 * For each delay tunning, an average on `iterations` acquired values is performed.
 * Depending on the value of the average the delay setting is saved or not.
 *   
 * @param iterations count of samples for average
 * @param true to display calibration log
 * @return chosen calibration delay value
 */
u64 XTDC_Calibrate(XTDC *InstancePtr, int iterations, int verbose);

#endif //XTDC_H
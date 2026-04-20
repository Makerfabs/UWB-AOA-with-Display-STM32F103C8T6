/*
 * @file error.h
 *
 * @brief
 *
 * @author Decawave Software
 *
 * @attention Copyright 2018 (c) DecaWave Ltd, Dublin, Ireland.
 *            All rights reserved.
 *
 */

#ifndef INC_ERROR_H_
#define INC_ERROR_H_


typedef enum{
    _NO_ERR       = 0,
    _Err          = 1,
    _Err_Busy     = 2,
    _Err_Timeout  = 3,
    _ERR_DEVID,
    _ERR_IWDG,
    _ERR_INSTANCE,
    _ERR_INIT,
    _ERR_IMU_INIT,
    _Err_TxBuf_Overflow,
    _Err_RxBuf_Overflow,
    _Err_Usb_Tx,
    _Err_Flash_Ob,
    _Err_Flash_Prog,
    _Err_Flash_Erase,
    _Err_Flash_Error,
    _Err_Flash_Verify,
    _Err_Flash_Protected,
    _ERR_LSM_R,
    _ERR_LSM_W,
    _ERR_SPI,
    _ERR_SPI_RRX,
    _ERR_SPI_WTX,
    _ERR_SPI_DMA,
    _ERR_UART_INIT,
    _ERR_UART_RX,
    _ERR_UART_TX,
    _ERR_UART_RxCplt,
    _ERR_UART_RxCplt_Overflow,
    _ERR_USB_UART_RX,
    _ERR_TCFM,
    _ERR_TWR_CANNOT_START,
    _ERR_MEM_CORRUPTED,
    _Err_Configure_WKUP_Timer,
/*TWR*/
    _Err_Twr_Bad_State,
    _Err_Not_Twr_Frame,
    _Err_Unknown_Tag,
    _Err_DelayedTX_Late,
    _No_Err_New_Tag,
    _No_Err_Tx_Sent,
    _No_Err_Start_Rx,
    _No_Err_Final,
    _Err_Range_Calculation,
/*USB2SPI*/
    _Err_Usb2Spi_ptr_busy,
    _Err_Usb2Spi_ptr_alloc,
/*RTOS*/
    _Err_General_Error,
    _Err_Create_Task_Bad,
    _Err_Timer_Create_Bad,
    _Err_Timer_Start_Bad,
    _Err_Signal_Bad,
    _ERR_Cannot_Delete_Timer,
    _ERR_Cannot_Delete_Task,
    _ERR_Cannot_Delete_usb2spiTask,
    _ERR_Cannot_Delete_tcfmTask,
    _ERR_Cannot_Delete_tcwmTask,
    _ERR_Cannot_Delete_imuTask,
    _ERR_Cannot_Delete_rxTask,
    _ERR_Cannot_Delete_calcTask,
    _ERR_Cannot_Delete_testTask,
    _ERR_Cannot_Send_Mail,
    _ERR_Cannot_Alloc_Mail,
    _ERR_Cannot_Alloc_Memory,
    _ERR_Stack_Overflow,
    _ERR_No_pTwrInfo
}error_e;


#endif /* INC_ERROR_H_ */

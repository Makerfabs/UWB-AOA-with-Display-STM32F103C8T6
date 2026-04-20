/*! ----------------------------------------------------------------------------
 *  @file    ds_twr_initiator.c
 *  @brief   Double-sided two-way ranging (DS TWR) initiator example code
 *
 *           This is a simple code example which acts as the initiator in a DS TWR distance measurement exchange. This application sends a "poll"
 *           frame (recording the TX time-stamp of the poll), and then waits for a "response" message expected from the "DS TWR responder" example
 *           code (companion to this application). When the response is received its RX time-stamp is recorded and we send a "final" message to
 *           complete the exchange. The final message contains all the time-stamps recorded by this application, including the calculated/predicted TX
 *           time-stamp for the final message itself. The companion "DS TWR responder" example application works out the time-of-flight over-the-air
 *           and, thus, the estimated distance between the two devices.
 *
 * @attention
 *
 * Copyright 2015-2020 (c) Decawave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author Decawave
 */

#include <deca_device_api.h>
#include <deca_regs.h>
#include "twr_task.h"
#include <shared_defines.h>
#include "uwb.h"
#include <shared_functions.h>



/*! ------------------------------------------------------------------------------------------------------------------
 * @fn ds_twr_initiator()
 *
 * @brief Application entry point.
 *
 * @param  none
 *
 * @return none
 */
void twr_task(void)
{
	//Run the selected example as selected in example_selection.h
	build_examples();
}

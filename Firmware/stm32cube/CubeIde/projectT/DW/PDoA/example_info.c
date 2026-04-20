///*! ----------------------------------------------------------------------------
// * @file    example_info.h
// * @brief
// *
// * @attention
// *
// * Copyright 2013-2018(c) Decawave Ltd, Dublin, Ireland.
// *
// * All rights reserved.
// *
// */
//
//#include <assert.h>
////#include <example_selection.h>
////#include "examples_defines.h"
//
//example_ptr example_pointer;
//
//void build_examples(void)
//{
//    unsigned char test_cnt=0;
//
//#ifdef TEST_DS_TWR_STS_SDC_INITIATOR
//    extern int ds_twr_sts_sdc_initiator(void);
//
//    example_pointer=ds_twr_sts_sdc_initiator;
//    test_cnt++;
//#endif
//
//#ifdef TEST_DS_TWR_STS_SDC_RESPONDER
//    extern int ds_twr_sts_sdc_responder(void);
//
//    example_pointer=ds_twr_sts_sdc_responder;
//    test_cnt++;
//#endif
//
//    //Check that only 1 test was enabled in test_selection.h file
//    assert(test_cnt==1);
//
//
//    // ���лص�����
//    example_pointer();
//}
//

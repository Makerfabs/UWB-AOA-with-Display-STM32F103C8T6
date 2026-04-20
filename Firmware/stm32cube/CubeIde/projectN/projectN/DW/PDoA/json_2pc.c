/*
 * @file     json_2pc.c
 * @brief    collection of JSON formatted functions which used
 *           to report from Node application to the PC
 *
 * @author Decawave Software
 *
 * @attention Copyright 2018 (c) Decawave Ltd, Dublin, Ireland.
 *            All rights reserved.
 *
 */
#include "util.h"
//#include "node.h"
#include "shared_functions.h"
#include "cmd_fn.h"
#include "Generic_cmd.h"

/*
 * @brief function to report to PC a new tag was discovered
 *
 * 'JSxxxx{"NewTag":
 *             <string>//address64, string
 *        }'
 *
 * */
void signal_to_pc_new_tag_discovered(uint64_t addr64)
{
    char str[MAX_STR_SIZE];
    memset(str, 0, sizeof(str));
    
    int  hlen;

    hlen = sprintf(str,"JS%04X", 0x5A5A);    // reserve space for length of JS object

    sprintf(&str[strlen(str)],"{\"NewTag\":\"%08lX%08lX\"}", (uint32_t)(addr64>>32), (uint32_t)addr64);

    sprintf(&str[2],"%04X",strlen(str)-hlen);//add formatted 4X of length, this will kill first '{'
    str[hlen]='{';                            //restore the start bracket

    sprintf(&str[strlen(str)],"\r\n");
    port_tx_msg((uint8_t*)str, strlen(str));
}

/*
 *  作用:小车(跟随)上报数据格式,包含自身基站和标签距离及角度
 *
 */
void send_to_pc_custom_twr_carfollow(result_t Res)
{
    uint8_t buf[128];
    int len = 0;
    Msg_Hex_Output_t msg;
    msg.header = 0x2A;

    msg.length = MSG_HEX_OUTPUT_LEN;		
    msg.length += 2;

    msg.gerneal_para.sn = Res.rangeNum;
    msg.gerneal_para.Addr = Res.addr16;
    
    msg.gerneal_para.angle = (int)Res.angle;
    msg.gerneal_para.distance = (int)Res.dist_cm;
    
    msg.gerneal_para.user_cmd = Res.flag;

    msg.gerneal_para.F_Path_Power_Level = 0;
    msg.gerneal_para.RX_Level = 0;

    msg.gerneal_para.Acc_X = Res.acc_x;
    msg.gerneal_para.Acc_Y = Res.acc_y;
    msg.gerneal_para.Acc_Z = Res.acc_z;
    msg.footer = 0x23;		
    
    len = App_Module_format_conver_uint8(msg, buf);

    port_tx_msg(buf , len);

}



/*
 * @brief This is a report of twr to pc
 *
 * There are two modes of operation: JSON(long output) or plain(short output)
 * JSON (default):
 *  'JSxxxx{"TWR":
 *    {     "a16":%04X, //addr16
 *          "R":%d,//range num
 *          "T":%d,//sys timestamp of Final WRTO Node's SuperFrame start, us
 *          "D":%f,//distance
 *          "P":%f,//raw pdoa
 *          "A":%f,//corrected angle
 *          "O":%f,//clock offset in hundreds part of ppm
 *          "V":%d //service message data from the tag: (stationary, etc)
 *          "X":%d //service message data from the tag: (stationary, etc)
 *          "Y":%d //service message data from the tag: (stationary, etc)
 *          "Z":%d //service message data from the tag: (stationary, etc)
 *    }
 *   }'
 *
 * Plain:
 * used if any from below is true:
 * diag, acc,
 * */
void send_to_pc_twr(result_t Res)
{
	uint8_t str[256];
    memset(str, 0, sizeof(str));
    
    int  hlen;
    if (app.pConfig->s.user_cmd == 0)
    {
        /* use JSON type of output during a normal operation
         *
         * This is not very efficient, as one TWR location is 107 chars, as per format below
         * JS  62{"TWR": {"a16":"2E5C","R":3,"T":8605,"D":343,"P":1695,"O":14,"V":1,"X":53015,"Y":60972,"Z":10797}}
         *
         * For pure UART, with limit of 115200b/s, the channel can handle ~100 locations per second,
         * i.e. 10 tags ranging on maximum rate of 10 times a second.
         * For higher throughput limit amount of JSON TWR object or use plain output instead.
         *
         * */

        /* Floating point values are standard for JSON objects, however the floating point printing
         * is not used in current application.
         * If the fixed point printing required, will need to add "-u _printf_float" to the
         * linker string, to include "floating printf" to the nano.spec of the stdlib.
         * This will increase the size of application by ~6kBytes and the floating printing also requires
         * much more stack space.
         * Use this with caution, as this might result unpredictable stack overflow / hard fault.
         * */
        hlen = sprintf(str,"JS%04X", 0x5A5A);    // reserve space for length of JS object

        sprintf(&str[strlen(str)],"{\"TWR\": ");

        sprintf(&str[strlen(str)],
                "{\"a16\":\"%04X\","
                "\"R\":%d," //range number
                "\"T\":%d,",//sys timestamp of Final WRTO Node's SuperFrame start, us
                (int)(Res.addr16),
                (int)(Res.rangeNum),
                (int)(Res.resTime_us));

        sprintf(&str[strlen(str)],
                "\"D\":%d," //distance as int
                "\"P\":%d," //pdoa  as int in milli-radians
                "\"Xcm\":%d,"   //X distance wrt Node in cm
                "\"Ycm\":%d,",  //Y distance wrt Node in cm
                (int)(Res.dist_cm),
                (int)(Res.pdoa_raw_deg),
                (int)(Res.x_cm),
                (int)(Res.y_cm));

        sprintf(&str[strlen(str)],
                "\"O\":%d,"//clock offset as int
                "\"V\":%d," //service message data from the tag: (bitmask: bit0 = stationary, bit15 = zeroed pdoaOffset used; bit14 = zeroed rngOffset used)
                "\"X\":%d," //Normalized accel data X from the Tag, mg
                "\"Y\":%d," //Normalized accel data Y from the Tag, mg
                "\"Z\":%d"  //Normalized accel data Z from the Tag, mg
                "}",
                (int)(Res.clockOffset_pphm),
                (int)(Res.flag),
                (int)(Res.acc_x),
                (int)(Res.acc_y),
                (int)(Res.acc_z));

        sprintf(&str[strlen(str)],"}");

        sprintf(&str[2],"%04X",strlen(str)-hlen);//add formatted 4X of length, this will kill first '{'
        str[hlen]='{';                            //restore the start bracket

        sprintf(&str[strlen(str)],"\r\n");
        port_tx_msg((uint8_t*)str, strlen(str));
    }
    else if(app.pConfig->s.user_cmd == 1)
    {
        send_to_pc_custom_twr_carfollow(Res);
        //no output
    }
}



/*
 * @file     cmd_fn.c
 * @brief    collection of executables functions from defined known_commands[]
 *
 * @author   Decawave Software
 *
 * @attention Copyright 2018 (c) DecaWave Ltd, Dublin, Ireland.
 *            All rights reserved.
 *
 */

#include "cmd_fn.h"
//#include "translate.h"
#include "version.h"
#include "deca_version.h"
#include "config.h"
//#include "uwb_frames.h"
//#include "node.h"
#include "Generic.h"
#include "shared_functions.h"
//-----------------------------------------------------------------------------
const char CMD_FN_RET_OK[] = "ok\r\n";
const char CMD_FN_RET_ERR[] = "error\r\n";


/*
 * 功能:帮助
 *
 * */
REG_FN(f_help_app)
{
    int        indx = 0;
    const char * ret = NULL;
    char str[MAX_STR_SIZE];
    memset(str, 0, sizeof(str));

    while (known_commands[indx].name != NULL)
    {
        sprintf(str,"%s \r\n", known_commands[indx].name);

        port_tx_msg((uint8_t*)str, strlen(str));

        indx++;
    }
    ret = CMD_FN_RET_OK;

    return (ret);
}

/*
 * 功能:获取版本
 *
 * */
REG_FN(f_getver)
{
    char str[64];
	memset(str, 0, sizeof(str));

	sprintf(str,"getver software:%s,hardware:%s\r\n",uwb_software_ver,uwb_hardware_ver);    // reserve space for length of JS object
    port_tx_msg(str, strlen(str));	
    return (CMD_FN_RET_OK);		
}


/*
 * 功能:保存
 *
 * */
REG_FN(f_save)
{
	App_Module_Sys_Write_NVM();	
	port_tx_msg("save\r\n", strlen("save\r\n"));

    return (CMD_FN_RET_OK);
}


/*
 * 功能:恢复出厂模式
 *
 * */
REG_FN(f_rtoken)
{
	App_Module_sys_para_Init();			
	App_Module_Sys_Write_NVM();	
	Sleep(100);
	NVIC_SystemReset(); 	
	return (CMD_FN_RET_OK);	
}


/*
 * 功能:复位模块
 *
 * */
REG_FN(f_reset)
{
	 NVIC_SystemReset();
	 return (CMD_FN_RET_OK);	
}

/*
 * 功能:上位机通信命令
 *
 * */
REG_FN(f_decaPDOA)
{
    const char *ret = NULL;
    const char ver[] = FULL_VERSION;

    char str[256];
	memset(str, 0, sizeof(str));

	int  hlen;

	hlen = sprintf(str,"JS%04X", 0x5A5A);    // reserve space for length of JS object

	sprintf(&str[strlen(str)],"{\"Info\":{\r\n");
	sprintf(&str[strlen(str)],"\"Device\":\"PDOA Node\",\r\n");
	sprintf(&str[strlen(str)],"\"Version\":\"%s\",\r\n", ver);
	sprintf(&str[strlen(str)],"\"Build\":\"%s %s\",\r\n", __DATE__, __TIME__ );
	sprintf(&str[strlen(str)],"\"Driver\":\"%s\"}}", DW3000_DEVICE_DRIVER_VER_STRING );

	sprintf(&str[2],"%04X",strlen(str)-hlen);   //add formatted 4X of length, this will erase first '{'
	str[hlen]='{';                            //restore the start bracket
	sprintf(&str[strlen(str)],"\r\n");
	port_tx_msg((uint8_t*)str, strlen(str));

	ret = CMD_FN_RET_OK;

    return (ret);
}

/*
 *	作用：角度修正值
 *
 * */
REG_FN(f_pdoa_offset)
{
    app.pConfig->s.pdoaOffset_deg = (int16_t)val;
    return (CMD_FN_RET_OK);
}


/*
 *	作用：距离修正值
 *
 * */
REG_FN(f_rng_offset)
{
    app.pConfig->s.rngOffset_mm = (int16_t)val;
    return (CMD_FN_RET_OK);
}


/*
 *	作用：获取[发现列表]
 *
 * */
REG_FN(f_motion_filter)
{
	app.pConfig->s.motionfilter	= (int16_t)val;
	return (CMD_FN_RET_OK);
}


/*
 *	作用：修改串口速率
 *
 * */
REG_FN(f_uart_rate)
{
	app.pConfig->s.UartReFreshRate	= (int16_t)val;
	return (CMD_FN_RET_OK);	
}

/*
 *	作用：命令格式选择 0:Json格式 1:Hex格式
 *	
 * */
REG_FN(f_user_cmd)
{
	app.pConfig->s.user_cmd = (int16_t)val;
	return (CMD_FN_RET_OK);	
}



/*
 *	作用：获取[发现列表]
 *
 * */
REG_FN(f_get_discovered_list)
{
    uint64_t    *pAddr64;
    uint16_t     size;
    int          jlen, tmp;

    pAddr64     = getDList();
    size        = getDList_size();

    char str[MAX_STR_SIZE];
    memset(str, 0, sizeof(str));
    
        jlen = (11+2);
    if(size>0)
    {
        tmp = 0;
        tmp = strlen("\"1122334455667788\"");    //16+2 for every addr64
        jlen += (tmp+3)*size -3;
    }

    sprintf(str,"JS%04X", jlen);                   // print pre-calculated length of JS object
    sprintf(&str[strlen(str)],"{\"DList\":[ ");    //+11 to json.
    port_tx_msg((uint8_t*)str, strlen(str));

    //DList cannot be with gaps
    // if changed, will need to change the calculation of jlen
    while(size>0 )
    {
        sprintf(str,"\"%08lX%08lX\"", (uint32_t)(*pAddr64>>32), (uint32_t)(*pAddr64));//+18 to json

        if(size > 1)
        {
            sprintf(&str[strlen(str)], ",\r\n");    //+3 to json
        }

        port_tx_msg((uint8_t*)str, strlen(str));

        pAddr64++;
        size--;
    }

    port_tx_msg((uint8_t*)"]}\r\n", 4);             //+2 to json

    _dbg_printf("deal cmd\n");
    initDList();                                    //clear the Discovered list

    return (CMD_FN_RET_OK);
}


static void fill_json_tag(char *str, tag_addr_slot_t *tag)
{
    sprintf(str,
            "{\"slot\":\"%04X\",\"a64\":\"%08lX%08lX\",\"a16\":\"%04X\","
            "\"F\":\"%04X\",\"S\":\"%04X\",\"M\":\"%04X\"}",
            tag->slot,(uint32_t)(tag->addr64>>32),(uint32_t)(tag->addr64),tag->addr16,
            tag->multFast, tag->multSlow, tag->mode );
}


/*
 *	作用：获取[配对列表]
 *
 * */
REG_FN(f_get_known_list)
{
    tag_addr_slot_t    *tag;
    int                jlen, size, tmp;

    char str[MAX_STR_SIZE];
    memset(str, 0, sizeof(str));
    
  /*  16 bytes overhead for JSON
     *  66 bytes per known tag
     *  3 bytes per separation
     *  we need to pre-calculate the length of json string for DList & KList : in order to keep malloc() small
     */
    tag = get_knownTagList();
    size = get_knownTagList_size();

    jlen = (10+2);

    if(size > 0)
    {
        tmp = 0;
        fill_json_tag(str, tag);
        tmp = strlen(str);                            //+NN to json for every known tag
        jlen += (tmp+3)*size -3;
    }

    sprintf(str,"JS%04X", jlen);                        // 6 print pre-calculated length of JS object
    sprintf(&str[strlen(str)],"{\"KList\":[");          // 10
    port_tx_msg((uint8_t*)str, strlen(str));

    //KList can be with gaps, so need to scan it whole
    for(int i = 0; i< MAX_KNOWN_TAG_LIST_SIZE; i++)
    {
        if(tag->slot != (uint16_t)(0))
        {
            fill_json_tag(str, tag);                    //NN

            if(size > 1)    //last element should not have ',\r\n'
            {
                sprintf(&str[strlen(str)], ",\r\n");    //3
            }

            size--;

            port_tx_msg((uint8_t*)str, strlen(str));
        }

        tag++;
    }

    port_tx_msg((uint8_t*)"]}\r\n", 4);

    return (CMD_FN_RET_OK);
}


/*
 *	作用：增加标签到[配对列表]
 *
 * */
REG_FN(f_add_tag_to_list)
{
    const char *ret = NULL;

    char str[MAX_STR_SIZE];
    memset(str, 0, sizeof(str));
    
    tag_addr_slot_t    *tag;
    uint64_t           addr64=0;
    unsigned int       addr1=0, addr2=0;
    unsigned int       addr16=0, multFast=0, multSlow=0, mode=0, n=1, hlen;
    char               tmp[10];
    /* "addtag 11AABB4455FF7788 10AA 1 2 1" */
    n = sscanf(text, "%8s %08x%08x %x %x %x %x",
                      tmp, &addr1, &addr2, &addr16, &multFast, &multSlow, &mode);

    if (!(multFast == 0) && !(multSlow == 0) && (n == 7))
    {
        addr64 = (uint64_t)((((uint64_t)addr1)<<32) | addr2);

        tag = add_tag_to_knownTagList(addr64, (uint16_t)addr16);

        if(tag)
        {
            tag->multFast = (uint16_t)multFast;
            tag->multSlow = (uint16_t)multSlow;
            tag->mode = (uint16_t)mode;

            hlen = sprintf(str,"JS%04X", 0x5A5A);    // reserve space for length of JS object
            sprintf(&str[strlen(str)],"{\"TagAdded\": ");

            fill_json_tag(&str[strlen(str)], tag);

            sprintf(&str[strlen(str)],"}"); //\r\n

            sprintf(&str[2],"%04X",strlen(str)-hlen);//add formatted 4X of length, this will kill first '{'
            str[hlen]='{';                            //restore the start bracket

            sprintf(&str[strlen(str)],"\r\n");
            port_tx_msg((uint8_t*)str, strlen(str));

            ret = CMD_FN_RET_OK;
        }
    }

    return (ret);
}


/*
 *	作用：删除标签到[配对列表]
 *
 * */
REG_FN(f_del_tag_from_list)
{
    const char *ret = NULL;

    char str[MAX_STR_SIZE];
    memset(str, 0, sizeof(str));
    

    uint64_t        addr64=0;
    unsigned int    addr1=0, addr2=0, hlen;
    char            tmp[10];

    /* "delTag 11AABB4455FF7788" */
    sscanf(text, "%8s %08x%08x", tmp, &addr1, &addr2);

    addr64 = (uint64_t)((((uint64_t)addr1)<<32) | (uint64_t)addr2);
    if(addr64 > 0xFFFF)
    {
        del_tag64_from_knownTagList(addr64);
    }
    else
    {
        del_tag16_from_knownTagList((uint16_t)addr64);
    }

    hlen = sprintf(str,"JS%04X", 0x5A5A);    // reserve space for length of JS object
    sprintf(&str[strlen(str)],"{\"TagDeleted\": \"%08x%08x\"}", addr1 , addr2);

    sprintf(&str[2],"%04X",strlen(str)-hlen);//add formatted 4X of length, this will erase first '{'
    str[hlen]='{';                            //restore the start bracket
    sprintf(&str[strlen(str)],"\r\n");
    port_tx_msg((uint8_t*)str, strlen(str));

    ret = CMD_FN_RET_OK;

    return (const char *)(ret);
}

/*
 *	作用：设置配置参数(发现列表标签数量,绑定列表标签数量,基站PANID,基站设备ID,串口刷新速率)
 *
 * */
REG_FN(f_setcfg)
{
    const char *ret = CMD_FN_RET_ERR;

    char str[256];	
	uint16_t DiscList_num, BindList_num, panID, AncID, serail_Rate, filter, user_cmd;
	int n = 0;
	char tmp[10];
    memset(str, 0, sizeof(str));

    
	n = sscanf(text, "%8s %d %d %x %d %d %d %d",tmp, &DiscList_num, &BindList_num, &panID, &AncID, &serail_Rate, &filter, &user_cmd);	
	

	if(n == 8 &&
        DiscList_num <= MAX_DISCOVERED_TAG_LIST_SIZE &&
        BindList_num <= MAX_KNOWN_TAG_LIST_SIZE &&
		AncID <= 1)
	{
//	    pbss->s.Dlist = DiscList_num;
//      pbss->s.Klist = BindList_num;
		app.pConfig->s.addr = (int16_t)AncID;	
		app.pConfig->s.panID = (uint16_t)(panID);
        app.pConfig->s.UartReFreshRate = serail_Rate;
		app.pConfig->s.motionfilter = filter;
		app.pConfig->s.user_cmd = user_cmd;
		
		sprintf(str, "getcfg Dlist:%d KList:%d Net:%04X AncID:%d Rate:%d Filter:%d UserCmd:%d pdoaOffset:%d rngOffset:%d\r\n", 
			app.pConfig->s.Dlist,
			app.pConfig->s.Klist,
			app.pConfig->s.panID,
			app.pConfig->s.addr,
			app.pConfig->s.UartReFreshRate,
			app.pConfig->s.motionfilter,
			app.pConfig->s.user_cmd,
			app.pConfig->s.pdoaOffset_deg,
			app.pConfig->s.rngOffset_mm);
        
        port_tx_msg(str, strlen(str));

		ret = CMD_FN_RET_OK;		
	}
        
	return (ret);
}


/*
 *	作用：获取配置参数(发现列表标签数量,绑定列表标签数量,基站PANID,基站设备ID,串口刷新速率)
 *
 * */
REG_FN(f_getcfg)
{
    char str[256];	
    memset(str, 0, sizeof(str));
    
	sprintf(str, "getcfg Dlist:%d KList:%d Net:%04X AncID:%d Rate:%d Filter:%d UserCmd:%d pdoaOffset:%d rngOffset:%d\r\n", 
		app.pConfig->s.Dlist,
		app.pConfig->s.Klist,
		app.pConfig->s.panID,
		app.pConfig->s.addr,
		app.pConfig->s.UartReFreshRate,
		app.pConfig->s.motionfilter,
		app.pConfig->s.user_cmd,
		app.pConfig->s.pdoaOffset_deg,
		app.pConfig->s.rngOffset_mm);

    port_tx_msg(str, strlen(str));

	return (CMD_FN_RET_OK);
}
//-----------------------------------------------------------------------------
/*
 * 命令集
 */
//-----------------------------------------------------------------------------
const command_t known_commands []= {
    /* CMDNAME   MODE   fn     */

    {"HELP",    f_help_app},				//帮助
    {"SAVE",    f_save},					//保存
	{"RESET", 	f_reset},					//复位
	{"RTOKEN",  f_rtoken},					//恢复出厂模式
	{"GETVER",	f_getver},					//获取版本号
    {"DECA$",   f_decaPDOA},				//上位机认证命令
	
    {"GETDLIST",f_get_discovered_list},		//获取[发现列表]
    {"GETKLIST",f_get_known_list},			//获取[配对列表]
    {"ADDTAG",  f_add_tag_to_list},			//增加标签到[配对列表]
    {"DELTAG",  f_del_tag_from_list},		//删除标签到[配对列表]
    {"PDOAOFF", f_pdoa_offset},				//角度修正值
    {"RNGOFF",  f_rng_offset},				//距离修正值
	{"FILTER",  f_motion_filter},			//开启滤波
	{"UARTRATE",f_uart_rate},				//串口速率
    {"USER_CMD",f_user_cmd},				//命令格式选择 0:Json格式 1:Hex格式
	{"SETCFG",	f_setcfg},					//设置配置参数(发现列表标签数量,绑定列表标签数量,基站PANID,基站设备ID,串口刷新速率)
	{"GETCFG",	f_getcfg},					//获取配置参数(发现列表标签数量,绑定列表标签数量,基站PANID,基站设备ID,串口刷新速率)

    {NULL,       NULL}
};

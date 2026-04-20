/*
 * @file    cmd.c
 * @brief     command string as specified in document SWxxxx version X.x.x
 * @param    *text - string
 *             source - is an input stream source: this will be used to reply to the specified direction
 *
 * CODEWORD:
 *      "XXXX YYY" : set appropriate parameter XXXX to value YYY, allowed as per permission.
 *      "ZZZZ"     : change a mode of operation to ZZZZ, allowed only from IDLE except of "STOP".
 *      "STOP"     : allowed at any time and put application to the IDLE
 *
 *
 * @author Decawave Software
 *
 * @attention Copyright 2018 (c) DecaWave Ltd, Dublin, Ireland.
 *            All rights reserved.
 *
 */
#include <stdint.h>

#ifndef _WINT_T
#define _WINT_T
typedef uint32_t wint_t;
#endif
#include <cmd.h>
#include <cmd_fn.h>

#include "Generic_cmd.h"
/*
 *    Command interface
 */

/* IMPLEMENTATION */

/*
 * @brief "error" will be sent if error during parser or command execution returned error
 * */
static void cmd_onERROR(const char *err, control_t *pcmd)
{
    char *str = (char *)CMD_MALLOC(MAX_STR_SIZE);

    if(str)
    {
        strcpy(str, "error \r\n");
        if ( strlen(err)< (sizeof(str)-6-3-1)) {
            strcpy(&str[6], err);
            strcpy(&str[6 + strlen(err)], "\r\n");
        }
        port_tx_msg((uint8_t*)str, strlen(str));

        CMD_FREE(str);
    }
}


/* @fn         command_parser
 * @brief    checks if input "text" string in known "COMMAND" or "PARAMETER VALUE" format,
 *             checks their execution permissions, a VALUE range if restrictions and
 *             executes COMMAND or sets the PARAMETER to the VALUE
 * */
void command_parser(char *text)
{
    control_t   mcmd_console;
    control_t   *pcmd = &mcmd_console;
    command_t   *pk = NULL;

    memset (&mcmd_console, 0 , sizeof(mcmd_console));

    pcmd->equal = _NO_COMMAND;
    pcmd->indx = 0;

    do{
        text[pcmd->indx]=(char)toupper((int)text[pcmd->indx]);
    }while(text[ ++pcmd->indx ]);

    sscanf(text ,"%9s %d", pcmd->cmd, &pcmd->val); //check MAX_COMMAND_SIZE if format will be changeds

    pcmd->indx = 0;
    while (known_commands[pcmd->indx].name != NULL)
    {
        pk = (command_t *) &known_commands[pcmd->indx];

        if (( strcmp(pcmd->cmd, pk->name) == 0 ) &&\
            ( strlen(pcmd->cmd) == strlen(pk->name)) )
        {
            pcmd->equal = _COMMAND_FOUND;
			pcmd->equal = _COMMAND_ALLOWED;
			break;
        }

        pcmd->indx++;
    }


    switch (pcmd->equal)
    {
        case (_COMMAND_FOUND) :
        {
            cmd_onERROR(" incompatible mode", pcmd);
            break;
        }
        case (_COMMAND_ALLOWED):
        {
            /* execute corresponded fn() */
            pcmd->ret = pk->fn(text, pcmd->val);

            if (pcmd->ret)
            {
                port_tx_msg((uint8_t*)pcmd->ret, strlen(pcmd->ret));
            }
            else
            {
                cmd_onERROR(" function", pcmd);
            }
            break;
        }
        default:
            break;
    }
}


/* end of cmd.c */

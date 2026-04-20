/*
 * @file cmd_fn.h
 *
 * @brief  header file for cmd_fn.c
 *
 * @author Decawave Software
 *
 * @attention Copyright 2018 (c) DecaWave Ltd, Dublin, Ireland.
 *            All rights reserved.
 *
 */
#ifndef INC_CMD_FN_H_
#define INC_CMD_FN_H_    1

#ifdef __cplusplus
 extern "C" {
#endif



//-----------------------------------------------------------------------------
/* module DEFINITIONS */
#define MAX_STR_SIZE       (160)

/* Prefer to use dynamic strings allocation.
 * however this leads every task, which uses string output,
 * to allocate MAX_STR_SIZE from its own stack.
 * FreeRTOS does not look by default to overflow of the stack.
 * Set the configCHECK_FOR_STACK_OVERFLOW to 2 if in doubt.
 * */
#define DYNAMIC_MSG_STR_ALLOW

#if defined(DYNAMIC_MSG_STR_ALLOW)
#define CMD_MALLOC              malloc
#define CMD_FREE                free
#else
 extern char staticstr[];

 #define CMD_MALLOC(MAX_STR_SIZE)   staticstr
 #define CMD_FREE(x)    UNUSED(x)
#endif


//-----------------------------------------------------------------------------
/* All cmd_fn functions have unified input: (char *text, param_block_t *pbss, int val)
 * Will use REG_FN macro to declare unified functions.
 * */
#define REG_FN(x) const char *x(char *text, int val)

 /* command table structure definition */
 typedef struct {
     const char  *name;            /**< Command name string */
     REG_FN       ((*fn));         /**< function() */
 }command_t;


 extern const command_t known_commands[];

 void command_stop_received(void);



#ifdef __cplusplus
}
#endif


#endif /* INC_CMD_FN_H_ */

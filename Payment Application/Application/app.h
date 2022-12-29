/*
 * app.h
 *
 *  Created on: Dec 6, 2022
 *      Author: ahmed bahaa alkomy
 */

#ifndef App_H
#define App_H

#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

typedef unsigned char uint8_t;

typedef struct ST_user_info_t {
	uint8_t user_name[25];
	uint8_t user_PAN[20];
	uint8_t user_cardExpDate[6];
	float user_TransAmount;
	float user_terminalMaxAmount;
	float user_balance;

}ST_user_info_t;

void appStart(void);

#endif

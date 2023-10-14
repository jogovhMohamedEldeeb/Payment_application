

#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../Card/card.h"

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#define MAX_SIZE 11

typedef struct ST_terminalData_t{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[MAX_SIZE];

}ST_terminalData_t;

typedef enum EN_terminalError_t{
    TERMINAL_OK = 0,
    WRONG_DATE,
    EXPIRED_CARD,
    INVALID_CARD,
    INVALID_AMOUNT,
    EXCEED_MAX_AMOUNT,
    INVALID_MAX_AMOUNT

}EN_terminalError_t;


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);

#endif _TERMINAL_H_

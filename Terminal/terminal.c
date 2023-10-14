
#include"terminal.h"

/* helper function */
static int Compare_Date(int card,int trans);


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData) {
    uint8_t Date[MAX_SIZE];
    EN_terminalError_t ret = TERMINAL_OK;
    uint32_t counter = 0;

    printf("Enter Transaction Date [DD/MM/YYYY]: ");
    scanf("%10s", Date);

    if (strlen(Date) != 10){
        ret = WRONG_DATE;
    }
    else{           /* validate the format :  DD / MM / YYYY  */
        for(counter = 0; counter < 10; counter++){
            if(counter == 2 || counter == 5){
                if(Date[counter] != '/'){
                    ret = WRONG_DATE;
                    break;
                }
            }
             else{
                if(Date[counter] < '0' || Date[counter] > '9'){
                    ret = WRONG_DATE;
                    break;
                }
            }
        }
    }

    if(ret == TERMINAL_OK){
        strcpy(termData->transactionDate, Date);
    }

    return ret;
}



static int Compare_Date(int card,int trans){
    int ret = 0;
    if(card < trans){
        ret = -1;
    }
    else{
        ret = 1;
    }
    return ret;
}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){ // okk
    EN_terminalError_t ret = TERMINAL_OK;
    uint32_t card_day = 0, card_month = 0, card_year = 0;
    uint32_t term_day = 0, term_month = 0, term_year = 0;
                        /* 2 2 / 0 3 / 2 0 2 2  */
                        /* DD / MM / YYYY */
    card_day = ((cardData->cardExpirationDate[0] - '0') * 10 ) + (cardData->cardExpirationDate[1] - '0');
    card_month = ((cardData->cardExpirationDate[3] - '0') * 10 ) + (cardData->cardExpirationDate[4] - '0');
    card_year = ((cardData->cardExpirationDate[6] - '0') * 1000 ) + ((cardData->cardExpirationDate[7] - '0') * 100 ) +
            ((cardData->cardExpirationDate[8] - '0') * 10) + (cardData->cardExpirationDate[9] - '0');

    term_day = ((termData->transactionDate[0] - '0') * 10) + (termData->transactionDate[1] - '0');
    term_month = ((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0');
    term_year = ((termData->transactionDate[6] - '0') * 1000) + ((termData->transactionDate[7] - '0') * 100) +
             ((termData->transactionDate[8] - '0') * 10) + (termData->transactionDate[9] - '0');

    if(Compare_Date(card_year,term_year) < 0){
        ret = EXPIRED_CARD;
    }
    else if ((Compare_Date(card_year,term_year) ==  0) && (Compare_Date(card_month,term_month) < 0)){
         ret = EXPIRED_CARD;
    }
    else if ((Compare_Date(card_year,term_year) ==  0) && (Compare_Date(card_month,term_month) == 0)
              && (Compare_Date(card_day,term_day) < 0)){
         ret = EXPIRED_CARD;
    }
    else{
        ret = TERMINAL_OK;
    }
    return ret;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    EN_terminalError_t ret = TERMINAL_OK;
    float amount;

    printf("Enter transaction amount : ");
    fflush(stdin);
    scanf("%f",&(termData->transAmount));

    if(termData->transAmount <= 0){
        ret = INVALID_AMOUNT;
    }
    else{
       ret =  TERMINAL_OK;
    }
    return ret;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    EN_terminalError_t ret = TERMINAL_OK;

    if(termData->transAmount > termData->maxTransAmount){
        ret = EXCEED_MAX_AMOUNT;
    }
    else{
        ret = TERMINAL_OK;
    }
    return ret;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){
    EN_terminalError_t ret = TERMINAL_OK;

    if(maxAmount <= 0){
        ret = INVALID_MAX_AMOUNT;
    }
    else{
        termData->maxTransAmount = maxAmount;
        ret = TERMINAL_OK;
    }
    return ret;
}







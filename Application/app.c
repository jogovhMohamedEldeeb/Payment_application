
#include "app.h"



void appStart(void){
    ST_cardData_t card;
    ST_transaction_t trnas;
    ST_terminalData_t tirmn;

    if(getCardHolderName(&card) == WRONG_NAME){
        printf("Sorry, Invalid Name \n");
        return;
    }
    if(getCardExpiryDate(&card) == WRONG_EXP_DATE){
        printf("Sorry,Invalid Expiry Date \n");
        return;
    }
    else{
        if(getTransactionDate(&tirmn) == WRONG_DATE){
            printf("Sorry,Invalid Transaction Date \n");
            return;
        }
        else if(isCardExpired(&card,&tirmn) == EXPIRED_CARD){
            printf("Sorry,Invalid Expired Card \n");
            return;
        }
        else{/* Nothing */}
    }

    if(getTransactionAmount(&tirmn) == INVALID_AMOUNT){
        printf("Sorry,Invalid Amount \n");
        return;
    }
    else if(isBelowMaxAmount(&tirmn) == EXCEED_MAX_AMOUNT){
        printf("Sorry,Exceed Amount \n");
        return;
    }
    else{/* Nothing */}

     recieveTransactionData(&trnas);

     if(isValidAccount(&trnas,&accountsDB) == ACCOUNT_NOT_FOUND){
        printf("Sorry, Invalid Account \n");
        return;
     }
     else{/* Nothing */}

     if(isAmountAvailable(&trnas,&accountsDB) == LOW_BALANCE){
        printf("Sorry, Amount Not Available \n");
        return;
     }

     if(saveTransaction(&trnas) == SAVING_FAILED){
         printf("Sorry, Saving Failed \n");
        return;
     }
}


#include "server.h"

extern ST_accountsDB_t accountsDB[255] = {
    {2000.0, RUNNING, "1234567890123456"},{100000.0, BLOCKED, "5807007076043875"},
    {300.0, BLOCKED, "13450137418736813"},{600.0, RUNNING, "576545986530928"},
    {50000.0, BLOCKED, "2468135791357924"},{10000.0, BLOCKED, "9876543210987654"},
    {7000.0, RUNNING, "134567890123456"}, {8000.0, RUNNING, "9452956523475894"}
};

extern ST_transaction_t transDB[255] = {0};



EN_transState_t recieveTransactionData(ST_transaction_t *transData){
    EN_transState_t ret =  APPROVED;
    EN_serverError_t ret_error = SERVER_OK;
    EN_serverError_t ret_amount = SERVER_OK;
    EN_serverError_t ret_save = SERVER_OK;
    if(NULL == transData){
        ret = INTERNAL_SERVER_ERROR;
    }
    else{
        ret_error = isValidAccount(&(transData->cardHolderData),accountsDB);
        if(ret_error != SERVER_OK){
            switch(ret_error){
            case ACCOUNT_NOT_FOUND:
                ret = FRAUD_CARD;
                break;
            case BLOCKED_ACCOUNT:
                ret= DECLINED_STOLEN_CARD;
                break;
            default :
                ret = INTERNAL_SERVER_ERROR;
            }
        }
        else{ /* Nothing */ }
        ret_amount = isAmountAvailable(&(transData->terminalData),accountsDB);
        if(ret_amount != SERVER_OK){
            switch(ret_amount){
            case  LOW_BALANCE:
                ret = DECLINED_INSUFFECIENT_FUND;
                break;

            default :
                ret = INTERNAL_SERVER_ERROR;
            }
        }
        else{ /* Nothing */ }
        ret_save = saveTransaction(transData);
        if(ret_save != SERVER_OK){
            ret = INTERNAL_SERVER_ERROR;
        }
    }
    return ret ;
}


EN_serverError_t isValidAccount(ST_cardData_t*cardData, ST_accountsDB_t *accountRefrence){
    EN_serverError_t ret = SERVER_OK;
    uint32_t counter = 0;
    if((NULL == cardData) || (NULL == accountRefrence)){
        ret = ACCOUNT_NOT_FOUND;
    }

    for(counter = 0; counter < 8;counter++){
        if(strcmp(cardData->primaryAccountNumber , accountsDB[counter].primaryAccountNumber) == 0){
            *accountRefrence = accountsDB[counter];
            ret = SERVER_OK;
            break;
        }
    }
    return ret;
}


EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
    EN_serverError_t ret = SERVER_OK;
     if(accountRefrence->state == BLOCKED){
        ret = BLOCKED_ACCOUNT;
     }
     else{
        ret = SERVER_OK;
     }
    return ret;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence){
    EN_serverError_t ret = SERVER_OK;

    if(termData->transAmount > accountRefrence->balance){
        ret = LOW_BALANCE;
    }
    else{
        ret = SERVER_OK;
    }
    return ret;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){
    EN_serverError_t ret = SERVER_OK;
    uint32_t counter = 0;
    if(NULL == transData){
        ret = SAVING_FAILED;
    }
    for(counter = 0; counter < 255; counter++){
        if(transData[counter].transactionSequenceNumber == 0){
           transData[counter] =  *transData;
           transData[counter].transactionSequenceNumber = counter + 1;
           ret = SERVER_OK;
        }
    }
    return ret;
}

void listSavedTransactions(void){
    uint32_t counter = 0;

    for(counter = 0; counter < 255; counter++){
        if(transDB[counter].transactionSequenceNumber != 0){
            printf("######################### \n");
            printf("Transaction Sequence Number : %d \n",transDB[counter].transactionSequenceNumber);
            printf("Transaction Date : %s \n",transDB[counter].cardHolderData);
            printf("Transaction Amount : %.2f \n",transDB[counter].terminalData.transAmount);
            printf("Transaction State : %d \n",transDB[counter].transState);
            printf("Terminal Max Amount : %.2f \n",transDB[counter].terminalData.maxTransAmount);
            printf("Card holder Name : %s \n",transDB[counter].cardHolderData.cardHolderName);
            printf("Card Expiration Date : %s \n",transDB[counter].cardHolderData.cardExpirationDate);
            printf("######################### \n");
        }
    }
}





#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
     EN_cardError_t ret_status = CARD_OK;
     uint8_t counter = 0;

     printf("\nEnter holder name, please : ");
     fflush(stdin);
     scanf("%[^\n]%*c",cardData->cardHolderName);

     if((cardData->cardHolderName[0] == '\0') || (strlen(cardData->cardHolderName) < 20 &&  strlen(cardData->cardHolderName) >24))
     {
        ret_status = WRONG_NAME;
     }

    else{

      for(counter = 0; counter < strlen(cardData->cardHolderName); counter++){
        if(!isalpha((unsigned char) cardData->cardHolderName[counter])){
            ret_status = WRONG_NAME;
            break;
        }
     }
    }

     return ret_status;
}


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    EN_cardError_t ret_status = CARD_OK;


    printf("Enter the expiry date : ");
    fflush(stdin);
    scanf("%[^\n]%*c",cardData->cardExpirationDate);
                                                    /* MM/YY */
    if ((strlen(cardData->cardExpirationDate) != 5) || (cardData->cardExpirationDate[2] != '/') ||
        (((cardData->cardExpirationDate[0] - '0') * 10) + (cardData->cardExpirationDate[1] - '0') > 12) ||
        (((cardData->cardExpirationDate[3] - '0') * 10) + (cardData->cardExpirationDate[4] - '0') > 99)) {

         ret_status = WRONG_EXP_DATE;
    }
    else{
         ret_status = CARD_OK;
        }

    return ret_status;
}


EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    EN_cardError_t ret_status = CARD_OK;
    uint8_t counter = 0;

    printf("Enter PAN Card : ");
    fflush(stdin);
    scanf("%[^\n]%*c",cardData->primaryAccountNumber);

    if((strlen(cardData->primaryAccountNumber) < 16) || (strlen(cardData->primaryAccountNumber) > 19) ||
                (cardData->primaryAccountNumber[0] == '\0'))
    {
        ret_status = WRONG_PAN;
    }
    else{
        for(counter = 0; counter < strlen(cardData->cardHolderName); counter++){
            if((cardData->primaryAccountNumber[counter] < '0') ||(cardData->primaryAccountNumber[counter] > '9') ){
                ret_status = WRONG_PAN;
            }
        }
    }

     return ret_status;
}


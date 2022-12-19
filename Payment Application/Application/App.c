#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include"../Card/Card.h"
#include"../Terminal/Terminal.h"
#include"../Server/Server.h"
#include"App.h"


extern int user_index;
extern ST_transaction_t transaction_data;
extern ST_transaction_t  transaction[255];
extern ST_dataBase_t accounts_DB[255];
extern int trans_user_ids[255];
extern bool Expire;

int main()
{  
    appStart();

    //testCardModule();
    //testTerminalModule();
    //testServerModule();

}

void appStart()
{
    clientsData();

    float maxamount;

    getCardHolderName(&(transaction_data.cardHolderData));
    getCardExpiryDate(&(transaction_data.cardHolderData));
    getCardPan(&(transaction_data.cardHolderData));
    isValidCardPAN(&(transaction_data.cardHolderData));
    getTransactionDate(&(transaction_data.terminalData));
    if(isCardExpired(&(transaction_data.cardHolderData), &(transaction_data.terminalData))== EXPIRED_CARD)
        {   
            printf("DECLINED EXPIRED CARD");
        }
    else 
    {
    setMaxAmount(&(transaction_data.terminalData), maxamount);

    getTransactionAmount(&(transaction_data.terminalData));
    
    if(isBelowMaxAmount(&transaction_data.terminalData)==EXCEED_MAX_AMOUNT)
        printf("DECLINED AMOUNT EXCEEDING LIMIT");
    else
    {transaction_data.transState = recieveTransactionData(&transaction_data);

    if(transaction_data.transState==APPROVED)
        printf("SUCCESSFUL TRANSACTION\n");
    else if((transaction_data.transState== DECLINED_INSUFFECIENT_FUND))
        printf("Declined transaction, insuffecient fund\n");
    else if((transaction_data.transState==INTERNAL_SERVER_ERROR)&& (Expire==true))
        printf("DeclinedTransaction, Expired Card\n");
    else if((transaction_data.transState==INTERNAL_SERVER_ERROR))
        printf("Declined Transaction, transaction amount exceeds the maxmim amount\n");
    else if(transaction_data.transState== DECLINED_STOLEN_CARD)   
        printf("Declined transaction, stolen card\n");
    else if(transaction_data.transState==FRAUD_CARD)
    printf("Declined transaction, card's primary number does not exist\n"); 

    saveClientsData(accounts_DB);
    saveTransaction(&transaction_data);
    
    

    listSavedTransactions();
    
     }
    }
}

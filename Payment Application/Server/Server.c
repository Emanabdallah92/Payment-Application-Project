#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include"../Card/Card.h"
#include"../Terminal/Terminal.h"
#include"Server.h"


int user_index;

ST_dataBase_t accounts_DB[255];
ST_transaction_t  transaction[255];
ST_transaction_t transaction_data;
int trans_user_ids[255];

bool Expire=0;

EN_serverError_t clientsData() {
    
    int i= 0;
    char array[150];
    char state[150];

    FILE *accountsDb_Ptr = fopen("../Server/accountsDB.csv", "r");
    
    while (fgetc(accountsDb_Ptr) != '\n');

    while (fgets(array, 100, accountsDb_Ptr) != NULL) 
    {   
        sscanf(array, "%hd, %[^,], %[^,], %[^,], %f, %[^\n]", &(accounts_DB[i].ID), accounts_DB[i].CadrdHolderName,
        accounts_DB[i].account_data.primaryAccountNumber, accounts_DB[i].getCardExpiryDate, &(accounts_DB[i].account_data.balance),
         &state);

        if (strcmp(state, "RUNNING") == 0) 
            accounts_DB[i].account_data.state = RUNNING;
         else 
            accounts_DB[i].account_data.state = BLOCKED;

        i++;
        memset(array, 0, 100);
    }
    fclose(accountsDb_Ptr);
}

FILE *openFileAccount()
{
    FILE *accessFile_Ptr =fopen("../Server/accountsDB.csv", "w");
    fprintf(accessFile_Ptr, "ID, Card Holder Name, PAN, Card Expiration Date, Balance, Transaction State\n");

    return accessFile_Ptr;
}

EN_serverError_t saveClientsData(ST_dataBase_t accounts_DB[]) 
{
    
    char state[100];

    FILE *account_ptr= openFileAccount();

    for (int i = 0; i <255; i++) {
        if (accounts_DB[i].CadrdHolderName[0] == 0)
            break;
        
        if (accounts_DB[i].account_data.state == RUNNING) 
            strcpy(state, "RUNNING");
        else 
            strcpy(state, "BLOCKED");
        
        
        fprintf(account_ptr, "%d, %s, %s, %s, %f, %s\n", accounts_DB[i].ID, accounts_DB[i].CadrdHolderName, 
        accounts_DB[i].account_data.primaryAccountNumber, accounts_DB[i].getCardExpiryDate, accounts_DB[i].account_data.balance, 
        state);
    }
    fclose(account_ptr);
}


void testServerModule(void)
{  
    clientsData();

    float maxamount;
    // ST_transaction_t transaction_data;

    //isValidAccountTest();
    //recieveTransactionDataTest();
    //isBlockedAccountTest();
    //isAmountAvailableTest();
    //saveTransactionTest();
    //listSavedTransactionsTest();

    // getCardPan(&(transaction_data.cardHolderData));
    // getCardHolderName(&(transaction_data.cardHolderData));
    // getCardExpiryDate(&(transaction_data.cardHolderData));
    // isValidCardPAN(&(transaction_data.cardHolderData));
    // setMaxAmount(&(transaction_data.terminalData), maxamount);
    // getTransactionAmount(&(transaction_data.terminalData));
    
    // transaction_data.transState = recieveTransactionData(&transaction_data);

    // if(transaction_data.transState==APPROVED)
    //     printf("SUCCESSFUL TRANSACTION\n");
    //  else if((transaction_data.transState== DECLINED_INSUFFECIENT_FUND))
    //     printf("Declined transaction, insuffecient fund\n");
    //  else if((transaction_data.transState==INTERNAL_SERVER_ERROR))
    //     printf("Declined Transaction, transaction amount exceeds the maxmim amount\n");
    // else if(transaction_data.transState== DECLINED_STOLEN_CARD)   
    //     printf("Declined transaction, stolen card\n");
    // else if(transaction_data.transState==FRAUD_CARD)
    //     printf("Declined transaction, card's primary number does not exist\n"); 

    // saveClientsData(accounts_DB);
    // saveTransaction(&transaction_data);
    // listSavedTransactions();
}
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{   ST_terminalData_t TermData;
    bool flag=0;

    float maxTrans= transData -> terminalData.maxTransAmount;
    float TRANS= transData ->terminalData.transAmount;
     
        
        if(isValidAccount(&(transData->cardHolderData),&(accounts_DB[user_index].account_data) )==SERVER_OK)
        {   
                flag=true;
                
        }
            else
                flag=false;
        

        if (flag==false)
        {   
            transData->transState=FRAUD_CARD;
            return FRAUD_CARD;
        }


        if(isBlockedAccount(&(accounts_DB[user_index].account_data))==BLOCKED_ACCOUNT)
        {
            transData->transState= DECLINED_STOLEN_CARD;
            return DECLINED_STOLEN_CARD;
        }

    

        if (isAmountAvailable(&(transData->terminalData), &(accounts_DB[user_index].account_data))==LOW_BALANCE)
        {   
            transData->transState= DECLINED_INSUFFECIENT_FUND;
            return DECLINED_INSUFFECIENT_FUND;
        }
        
        accounts_DB[user_index].account_data.balance =accounts_DB[user_index].account_data.balance - TRANS;
        transData->transState= APPROVED;
        return APPROVED;
}
    

void recieveTransactionDataTest(void)
{  
    char name[]="Eman Mohamed Ehab Abdalla";
    char *PAN[]={"670995485543707426","6304159809696340230","6771654209871225","677127444535685112"};
    char *date[]={"12/28","11/28", "01/25","11/24"};
    float a=5000.00, b=2000.00, c=7000.00, d=500.00;
    float maxamount;
    ST_transaction_t transaction_data;
    EN_transState_t error;

    getCardPan(&(transaction_data.cardHolderData));
    isValidCardPAN(&(transaction_data.cardHolderData));
    setMaxAmount(&(transaction_data.terminalData), maxamount);
    getTransactionAmount(&(transaction_data.terminalData));
    printf("Tester Name: %s\n", name);
    printf("Function Name: recieveTransactionData\n");

    strcpy(transaction_data.cardHolderData.primaryAccountNumber, PAN[0]);
    strcpy(transaction_data.cardHolderData.cardExpirationDate, date[0]);
    transaction_data.terminalData.transAmount=a;
    error= recieveTransactionData(&transaction_data);
    printf("Test Case 1:\n");
    printf("Input Data: Primary account number: %s , Transaction amount: %f\n", PAN[0], a);
    printf("Expected Result: SUCCESSFUL TRANSACTION\n");
        if(error==APPROVED)
            printf("Actual Result: SUCCESSFUL TRANSACTION\n");
        else if((error== DECLINED_INSUFFECIENT_FUND))
            printf("Actual Result: DECLINED TRANSACTION, INSUFFECIENT FUND\n");
        else if(error== DECLINED_STOLEN_CARD)   
            printf("Actual Result: DECLINED TRANSACTION, STOLEN CARD\n");
        else if(error==FRAUD_CARD)
            printf("Actual Result: DECLINED TRANSACTION, card's primary number does not exist\n");
    printf("New Balance:%f\n",accounts_DB[user_index].account_data.balance);
       

    strcpy(transaction_data.cardHolderData.primaryAccountNumber, PAN[1]);
    strcpy(transaction_data.cardHolderData.cardExpirationDate, date[1]);
    transaction_data.terminalData.transAmount=b;
    error= recieveTransactionData(&transaction_data);
    printf("Test Case 2:\n");
    printf("Input Data: Primary account number: %s , Transaction amount: %f\n", PAN[1], b);
    printf("Expected Result: Declined transaction due to fake PAN\n");
        if(error==APPROVED)
            printf("Actual Result: SUCCESSFUL TRANSACTION\n");
        else if((error== DECLINED_INSUFFECIENT_FUND))
            printf("Actual Result: Declined transaction, insuffecient fund\n");
        else if(error== DECLINED_STOLEN_CARD)   
            printf("Actual Result: Declined transaction, stolen card\n");
        else if(error==FRAUD_CARD)
            printf("Actual Result: Declined transaction, card's primary number does not exist\n");

    strcpy(transaction_data.cardHolderData.primaryAccountNumber, PAN[2]);
    strcpy(transaction_data.cardHolderData.cardExpirationDate, date[2]);
    transaction_data.terminalData.transAmount=c;
    error= recieveTransactionData(&transaction_data);
    printf("Test Case 3:\n");
    printf("Input Data: Primary account number: %s , Transaction amount: %f\n", PAN[2], c);
    printf("Expected Result: Declined transaction due to insuffecient fund\n");
        if(error==APPROVED)
            printf("Actual Result: SUCCESSFUL TRANSACTION\n");
        else if((error== DECLINED_INSUFFECIENT_FUND))
            printf("Actual Result: Declined transaction, insuffecient fund\n");
        else if(error== DECLINED_STOLEN_CARD)   
            printf("Actual Result: Declined transaction, stolen card\n");
        else if(error==FRAUD_CARD)
            printf("Actual Result: Declined transaction, card's primary number does not exist\n");
    printf("New Balance:%f\n",accounts_DB[user_index].account_data.balance);

    strcpy(transaction_data.cardHolderData.primaryAccountNumber, PAN[3]);
    strcpy(transaction_data.cardHolderData.cardExpirationDate, date[3]);
    transaction_data.terminalData.transAmount=d;
    error= recieveTransactionData(&transaction_data);
    printf("Test Case 4:\n");
    printf("Input Data: Primary account number: %s , Transaction amount: %f\n", PAN[3], d);
    printf("Expected Result: Declined transaction due to blocked card\n");
        if(error==APPROVED)
            printf("Actual Result: SUCCESSFUL TRANSACTION\n");
        else if((error== DECLINED_INSUFFECIENT_FUND))
            printf("Actual Result: Declined transaction, insuffecient fund\n");
        else if(error== DECLINED_STOLEN_CARD)   
            printf("Actual Result: Declined transaction, stolen card\n");
        else if(error==FRAUD_CARD)
            printf("Actual Result: Declined transaction, card's primary number does not exist\n");
    
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
   
    for (int i = 0; i <256; i++)
    {   user_index=i;
        if(strcmp(cardData->primaryAccountNumber, accounts_DB[user_index].account_data.primaryAccountNumber) == 0)
       {    return SERVER_OK;
            break;
       }
    }
        accountRefrence=NULL;
        return ACCOUNT_NOT_FOUND;
    
}
void isValidAccountTest(void)
{
    char name[]="Eman Mohamed Ehab Abdalla";
    char *PAN[]={"6709157263619735","6304159809696340230"};
    ST_cardData_t transaction_data;
    EN_transState_t error;

    printf("Tester Name: %s\n", name);
    printf("Function Name: isValidAccount\n");


    strcpy(transaction_data.primaryAccountNumber,PAN[0] );
    error=isValidAccount(&transaction_data, &(accounts_DB[user_index].account_data));
    printf("Test Case 1:\n");
    printf("Input Data: Primary account number: %s\n" , PAN[0]);
    printf("Expected Result: Server Okay, Card Exists\n");
        if(error==APPROVED)
            printf("Actual Result: CARD EXISTS\n");
        else if(error== ACCOUNT_NOT_FOUND) 
            printf("Actual Result: ACCOUNT NOT FOUND\n");

    
    strcpy(transaction_data.primaryAccountNumber,PAN[1] );
    error=isValidAccount(&transaction_data, &(accounts_DB[user_index].account_data));
    printf("Test Case 2:\n");
    printf("Input Data: Primary account number: %s\n" , PAN[1]);
    printf("Expected Result: ACCOUNT NOT FOUND\n");
        if(error==APPROVED)
            printf("Actual Result: CARD EXISTS\n");
        else if(error== ACCOUNT_NOT_FOUND) 
            printf("Actual Result: ACCOUNT NOT FOUND\n");
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{       
    
    
  
       if(accounts_DB[user_index].account_data.state== BLOCKED)
            return BLOCKED_ACCOUNT;

        return SERVER_OK;
          

}
void 
isBlockedAccountTest(void)
{
    char name[]="Eman Mohamed Ehab Abdalla";
    char *PAN[]={"670995485543707426","67060721645739332"};
    EN_transState_t error;
    ST_cardData_t card_data;
    

    printf("Tester Name: %s\n", name);
    printf("Function Name: isBlockedAccount\n");
    
    strcpy(card_data.primaryAccountNumber, PAN[0]);
    isValidAccount(&card_data ,&(accounts_DB[user_index].account_data));
    error=isBlockedAccount(&(accounts_DB[user_index].account_data));
    printf("Test Case 1:\n");
    printf("Input Data: Primary account number: %s\n" , PAN[0]);
    printf("Expected Result: Server Okay, Card is running\n");
        if(error==SERVER_OK)
            printf("Actual Result: CARD IS RUNNING\n");
        else if(error== BLOCKED_ACCOUNT) 
            printf("Actual Result: CARD IS BLOCKED\n");


    strcpy(card_data.primaryAccountNumber, PAN[1]);
    isValidAccount(&card_data ,&(accounts_DB[user_index].account_data));
    error=isBlockedAccount(&(accounts_DB[user_index].account_data));
    printf("Test Case 2:\n");
    printf("Input Data: Primary account number: %s\n" , PAN[1]);
    printf("Expected Result: Card is blocked, stolen card\n");
        if(error==SERVER_OK)
            printf("Actual Result: CARD IS RUNNING\n");
        else if(error== BLOCKED_ACCOUNT) 
            printf("Actual Result: CARD IS BLOCKED\n");
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
     float TRANS= termData->transAmount;
    
    if(TRANS > accounts_DB[user_index].account_data.balance)
        return LOW_BALANCE;    
    
    return SERVER_OK;
}
void isAmountAvailableTest(void)
{
    char name[]="Eman Mohamed Ehab Abdalla";
    char *PAN[]={"6709157263619735","67716239517846141"};
    float a=8000.00, b=5000.00;
    ST_terminalData_t transaction_data;
    ST_cardData_t card_data;
    EN_transState_t error; 

    printf("Tester Name: %s\n", name);
    printf("Function Name: isAmountAvailable\n");

    transaction_data.transAmount=a;
    strcpy(card_data.primaryAccountNumber, PAN[0]);
    isValidAccount(&card_data ,&(accounts_DB[user_index].account_data));
    error=isAmountAvailable(&transaction_data, &(accounts_DB[user_index].account_data));
    printf("Test Case 1:\n");
    printf("Input Data: Primary account number: %s, Transaction Amount: %f\n" , PAN[0], a);
    printf("Expected Result: SUCCESSFUL TRANSACTION\n");
        if(error==SERVER_OK)
            printf("Actual Result: SUCCESSFUL TRANSACTION\n");
        else if(error== LOW_BALANCE) 
            printf("Actual Result: DECLINED TRANSACTION DUE TO INSUFFECIENT FUND\n");
    

    transaction_data.transAmount=b;
    strcpy(card_data.primaryAccountNumber, PAN[1]);
    isValidAccount(&card_data ,&(accounts_DB[user_index].account_data));
    error=isAmountAvailable(&transaction_data, &(accounts_DB[user_index].account_data));
    printf("Test Case 2:\n");
    printf("Input Data: Primary account number: %s, Transaction Amount: %f\n" , PAN[1], b);
    printf("Expected Result: DECLINED TRANSACTION\n");
        if(error==SERVER_OK)
            printf("Actual Result: SUCCESSFUL TRANSACTION\n");
        else if(error== LOW_BALANCE) 
            printf("Actual Result: DECLINED TRANSACTION DUE TO INSUFFECIENT FUND\n");
}

 FILE *openFileTrans()
{
 
    FILE *transactionFile_Ptr = fopen("../Server/transactionsDB.csv", "r");
    fseek(transactionFile_Ptr, 94, SEEK_SET);
    
    return transactionFile_Ptr;
}

EN_serverError_t getTransaction(char transactionSequenceNumber, ST_transaction_t *transData) 
{  
    char array[150];
    char rest[150];
    char state[25];
    int currentSequenceNumber;

    FILE *tran_ptr = openFileTrans();

    while (fgets(array, 100, tran_ptr) != NULL) 
    {   
        sscanf(array, "%d, %s", &currentSequenceNumber, rest);
        if (currentSequenceNumber == transactionSequenceNumber) 
        {   
            
            sscanf(array, "%d, %d, %f, %[^,], %[^\n]", &transData->transactionSequenceNumber, &user_index, 
            &transData->terminalData.transAmount, transData->terminalData.transactionDate, state);
            
            if (strcmp(state, "APPROVED") == 0)
                transData->transState = APPROVED;
            if (strcmp(state, "DECLINED_INSUFFECIENT_FUND") == 0)
                transData->transState = DECLINED_INSUFFECIENT_FUND;
            if (strcmp(state, "DECLINED_STOLEN_CARD") == 0)
                transData->transState = DECLINED_STOLEN_CARD;
            if (strcmp(state, "DECLINED_FRAUD_CARD") == 0)
                transData->transState = FRAUD_CARD;
            if (strcmp(state, "DECLINED_INTERNAL_SERVER_ERROR") == 0)
                 transData->transState = INTERNAL_SERVER_ERROR;

            fclose(tran_ptr);
            return SERVER_OK;
        }
    }
    
    fclose(tran_ptr);
    return TRANSACTION_NOT_FOUND;
}
FILE *loadTransactions()
{
    FILE *transactionFile_Ptr = fopen("../Server/transactionsDB.csv", "r");
    while (fgetc(transactionFile_Ptr) != '\n');
     
    return transactionFile_Ptr;
}
EN_serverError_t loadAllTransactions() {
    
    char array[150];
    char state[150];

    FILE *transaction_ptr= loadTransactions();

    int i= 0;
    while (fgets(array, 100, transaction_ptr) != NULL) 
    {   
        
        sscanf(array, "%d, %d, %f, %[^,], %[^\n]", &(transaction[i].transactionSequenceNumber), &trans_user_ids[i],
        &(transaction[i].terminalData.transAmount), &(transaction[i].terminalData.transactionDate), state);

        if (strcmp(state, "APPROVED") == 0) 
            transaction[i].transState = APPROVED;
        else if (strcmp(state, "DECLINED_INSUFFECIENT_FUND") == 0)
            transaction[i].transState = DECLINED_INSUFFECIENT_FUND;
        else if (strcmp(state, "DECLINED_STOLEN_CARD") == 0)
            transaction[i].transState = DECLINED_STOLEN_CARD;
        else if (strcmp(state, "DECLINED_FRAUD_CARD") == 0)
            transaction[i].transState = FRAUD_CARD;
        else if (strcmp(state, "DECLINED_INTERNAL_SERVER_ERROR") == 0)
            transaction[i].transState = INTERNAL_SERVER_ERROR;

        i++;
        memset(array, 0, 100);
    }
    fclose(transaction_ptr);
}

FILE *sTransaction()
{
    FILE *transactionFile_Ptr = fopen("../Server/transactionsDB.csv", "a");
    fseek(transactionFile_Ptr, 2, SEEK_CUR);

    return transactionFile_Ptr;
}
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    char transaction_state[25];

    FILE *transaction_ptr= sTransaction();

    if (transData->transState== APPROVED)    
        strcpy(transaction_state, "APPROVED");
    
    if (transData->transState== DECLINED_INSUFFECIENT_FUND)
        strcpy(transaction_state, "DECLINED_INSUFFECIENT_FUND");
        
    if (transData->transState== DECLINED_STOLEN_CARD)
        strcpy(transaction_state, "DECLINED_STOLEN_CARD");
        
    if (transData->transState== FRAUD_CARD)
        strcpy(transaction_state, "DECLINED_FRAUD_CARD");
        
    if (transData->transState== INTERNAL_SERVER_ERROR)
        strcpy(transaction_state, "DECLINED_INTERNAL_SERVER_ERROR"); 
 
        
    getTransactionDate(&(transData->terminalData));
    

    int trans_SequenceNumber = getTransactionSequenceNumber(); 
    transaction_data.transactionSequenceNumber= trans_SequenceNumber;
    fprintf(transaction_ptr, "\n%d, %d, %f, %s, %s", trans_SequenceNumber, user_index,
            transData->terminalData.transAmount, transData->terminalData.transactionDate, transaction_state);
    


    fclose(transaction_ptr);
    EN_serverError_t error;
    error = getTransaction(trans_SequenceNumber, transData);
    
    if(error == TRANSACTION_NOT_FOUND)
        return SAVING_FAILED;
    
    
    return SERVER_OK;

}
FILE *transeqnum()
{
 FILE *transactionFile_Ptr = fopen("../Server/transactionsDB.csv", "r");
        fseek(transactionFile_Ptr, 94 , SEEK_SET);
    
    // if (fgetc(transactionFile_Ptr) == EOF) 
    // {
    //     fclose(transactionFile_Ptr);
    //     return 0;
    // }
        
    //fseek(transactionFile_Ptr, -1, SEEK_CUR);
    return transactionFile_Ptr;
}
int getTransactionSequenceNumber() 
{   
    int last_ID=0;
    char rest[100];
    int i = 0;
    char array[100];
    
    FILE *transaction_ptr= transeqnum();
    while (fgets(array, 100, transaction_ptr) != NULL) 
    {
        sscanf(array, "%d,%s", &last_ID, rest);
        i++;
        memset(array, 0, 100);
    }
    fclose(transaction_ptr);
    return last_ID + 1;
}
void saveTransactionTest(void)
{
     char name[]="Eman Mohamed Ehab Abdalla";
    char *PAN[]={"670995485543707426","6304159809696340230","6771654209871225","677127444535685112"};
    char *NAME[]={"Milly Cyrus Gibbsons", "Dalia Borham Ibrahim", "Rene Weiler Lambings", "Kieran Gate Mann Drink"};
    char *date[]={"12/28","11/28", "01/25","11/24"};
    float a=1000.00, b=2000.00, c=7000.00, d=500.00;
    float maxamount=15000;
    ST_transaction_t TransactionTest;

    printf("Tester Name: %s\n", name);
    printf("Function Name: saveTransationTest\n");


    strcpy(TransactionTest.cardHolderData.primaryAccountNumber, PAN[0]);
    strcpy(TransactionTest.cardHolderData.cardHolderName, NAME[0]);
    strcpy(TransactionTest.cardHolderData.cardExpirationDate, date[0]);
    TransactionTest.terminalData.transAmount=a;
    TransactionTest.terminalData.maxTransAmount=maxamount;
    recieveTransactionData(&TransactionTest);
    saveClientsData(accounts_DB);
    printf("Test Case 1:\n");
    printf("Input Data: Card Holder Name: %s, Primary account number: %s, Expiry Date: %s, Transaction Amount: %f\n" ,NAME[0], PAN[0], date[0],a);
    printf("Expected Result: SAVED TRANSACTION\n");
    printf("Actual Result:\n ");
    saveTransaction(&TransactionTest);
    listSavedTransactions();

    strcpy(TransactionTest.cardHolderData.primaryAccountNumber, PAN[1]);
    strcpy(TransactionTest.cardHolderData.cardHolderName, NAME[1]);
    strcpy(TransactionTest.cardHolderData.cardExpirationDate, date[1]);
    TransactionTest.terminalData.transAmount=b;
    TransactionTest.terminalData.maxTransAmount=maxamount;
    recieveTransactionData(&TransactionTest);
    saveClientsData(accounts_DB);
    printf("Test Case 2:\n");
    printf("Input Data: Card Holder Name: %s, Primary account number: %s, Expiry Date: %s, Transaction Amount: %f\n" ,NAME[1], PAN[1], date[1],b);
    printf("Expected Result: SAVED TRANSACTION\n");
    printf("Actual Result:\n ");
    saveTransaction(&TransactionTest);
    listSavedTransactions();

    strcpy(TransactionTest.cardHolderData.primaryAccountNumber, PAN[2]);
    strcpy(TransactionTest.cardHolderData.cardHolderName, NAME[2]);
    strcpy(TransactionTest.cardHolderData.cardExpirationDate, date[2]);
    TransactionTest.terminalData.transAmount=c;
    TransactionTest.terminalData.maxTransAmount=maxamount;
    recieveTransactionData(&TransactionTest);
    saveClientsData(accounts_DB);
    printf("Test Case 3:\n");
    printf("Input Data: Card Holder Name: %s, Primary account number: %s, Expiry Date: %s, Transaction Amount: %f\n" ,NAME[2], PAN[2], date[2],c);
    printf("Expected Result: SAVED TRANSACTION\n");
    printf("Actual Result:\n ");
    saveTransaction(&TransactionTest);
    listSavedTransactions();

    strcpy(TransactionTest.cardHolderData.primaryAccountNumber, PAN[3]);
    strcpy(TransactionTest.cardHolderData.cardHolderName, NAME[3]);
    strcpy(TransactionTest.cardHolderData.cardExpirationDate, date[3]);
    TransactionTest.terminalData.transAmount=d;
    TransactionTest.terminalData.maxTransAmount=maxamount;
    recieveTransactionData(&TransactionTest);
    saveClientsData(accounts_DB);
    printf("Test Case 4:\n");
    printf("Input Data: Card Holder Name: %s, Primary account number: %s, Expiry Date: %s, Transaction Amount: %f\n" ,NAME[3], PAN[3], date[3],c);
    printf("Expected Result: SAVED TRANSACTION\n");
    printf("Actual Result:\n ");
    saveTransaction(&TransactionTest);
    listSavedTransactions();
    
}
void listSavedTransactions(void)
{  
   loadAllTransactions();

    // Displaying the data in a detailed format
    for(int i=0; i<=(transaction_data.transactionSequenceNumber); i++)
    {   
        //getTransaction(i, &transaction[i]);

        printf("#########################\n");

        //Transaction Sequence Number
        printf("Transaction Sequence Number: %d\n",transaction[i].transactionSequenceNumber);

        //Transaction Date
        printf("Transaction Date: %s\n",transaction[i].terminalData.transactionDate);

        //Transaction Amount
        printf("Transaction Amount: %f\n",transaction[i].terminalData.transAmount);

        //Transaction State
        if(transaction[i].transState == APPROVED)
        printf("Transaction State: APPROVED\n");

        if(transaction[i].transState == DECLINED_INSUFFECIENT_FUND)
        printf("Transaction State: DECLINED INSUFFECIENT FUNd\n");

        if(transaction[i].transState == DECLINED_STOLEN_CARD)
        printf("Transaction State: DECLINED STOLEN CARD\n");

        if(transaction[i].transState == FRAUD_CARD)
        printf("Transaction State: FRAUD CARD\n");

        if(transaction[i].transState == INTERNAL_SERVER_ERROR)
        printf("Transaction State: INTERNAL SERVER ERROR\n");

        //Maximum Transaction Amount
        printf("Terminal Max Amount: 15000\n");

        user_index = trans_user_ids[i];

        //Card Holder Name
        printf("Cardholder Name: %s\n", accounts_DB[user_index].CadrdHolderName);
    
        //Primary Account Number
        printf("PAN: %s\n",accounts_DB[user_index].account_data.primaryAccountNumber);

        //Card Expiration Date
        printf("Card Expiration Date: %s\n", accounts_DB[user_index].getCardExpiryDate);

        printf("#########################\n");
    }
}
 void listSavedTransactionsTest(void)
 {   char name[]="Eman Mohamed Ehab Abdalla";
    char *PAN[]={"670995485543707426","6771654209871225"};
    char *NAME[]={"Milly Cyrus Gibbsons","Rene Weiler Lambings"};
    char *date[]={"12/28","01/25"};
    float a=1000.00, b=7000.00;
    float maxamount=15000;
    ST_transaction_t TransactionTest;
    printf("Tester Name: %s\n", name);
    printf("Function Name: listsavedtransactionTest\n");
    strcpy(TransactionTest.cardHolderData.primaryAccountNumber, PAN[0]);
    strcpy(TransactionTest.cardHolderData.cardHolderName, NAME[0]);
    strcpy(TransactionTest.cardHolderData.cardExpirationDate, date[0]);
    TransactionTest.terminalData.transAmount=a;
    TransactionTest.terminalData.maxTransAmount=maxamount;
    recieveTransactionData(&TransactionTest);
    saveClientsData(accounts_DB);
    printf("Test Case 1:\n");
    printf("Input Data: Card Holder Name: %s, Primary account number: %s, Expiry Date: %s, Transaction Amount: %f\n" ,NAME[0], PAN[0], date[0],a);
    printf("Expected Result: SAVED TRANSACTION\n");
    printf("Actual Result:\n ");
    saveTransaction(&TransactionTest);
    listSavedTransactions();
    strcpy(TransactionTest.cardHolderData.primaryAccountNumber, PAN[1]);
    strcpy(TransactionTest.cardHolderData.cardHolderName, NAME[1]);
    strcpy(TransactionTest.cardHolderData.cardExpirationDate, date[1]);
    TransactionTest.terminalData.transAmount=b;
    TransactionTest.terminalData.maxTransAmount=maxamount;
    recieveTransactionData(&TransactionTest);
    saveClientsData(accounts_DB);
    printf("Test Case 2:\n");
    printf("Input Data: Card Holder Name: %s, Primary account number: %s, Expiry Date: %s, Transaction Amount: %f\n" ,NAME[1], PAN[1], date[1],b);
    printf("Expected Result: SAVED TRANSACTION\n");
    printf("Actual Result:\n ");
    saveTransaction(&TransactionTest);
    listSavedTransactions();
 }

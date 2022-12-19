#ifndef SERVER
#define SERVER
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

typedef enum EN_transState_t
{
     APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
     ST_cardData_t cardHolderData;
     ST_terminalData_t terminalData;
     EN_transState_t transState;
     uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_serverError_t 
{
     SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t; 

typedef enum EN_accountState_t
{
     RUNNING,
     BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
     float balance;
     EN_accountState_t state;
     uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

typedef struct ST_dataBase_t 
{
     ST_accountsDB_t account_data;
     uint8_t CadrdHolderName[25];
     uint8_t getCardExpiryDate[6];
     uint32_t ID;
} ST_dataBase_t;

int getTransactionSequenceNumber();
FILE *openFileTrans();
FILE *openFileAccount();
FILE *loadTransactions();
FILE *sTransaction();
EN_serverError_t clientsData();
EN_serverError_t getTransaction(char transactionSequenceNumber, ST_transaction_t *transData);
EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t saveClientsData(ST_dataBase_t accounts_DB[]);
EN_serverError_t loadAllTransactions();

void testServerModule(void);
void listSavedTransactionsTest(void);
void listSavedTransactions(void);
void saveTransactionTest(void);
void isAmountAvailableTest(void);
void isValidAccountTest(void);
void recieveTransactionDataTest(void);
void isBlockedAccountTest(void);

#endif
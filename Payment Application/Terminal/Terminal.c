#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#include"../Card/Card.h"
#include"Terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    time_t t= time(NULL);
    struct tm date = *localtime(&t);
    int dd= date.tm_mday;
    int mm= date.tm_mon+1;
    int yy= date.tm_year+1900;
    char arr_date_check[10];
    sprintf(arr_date_check, "%d/%d/%d", dd, mm, yy);
    strcpy(termData ->transactionDate, arr_date_check);
    return TERMINAL_OK;
}

void testTerminalModule(void)
{   
    ST_terminalData_t terminal_data;
    ST_cardData_t card_data;
    EN_terminalError_t error;

    //getTransactionDateTest();
    // error= getTransactionDate(&terminal_data);
    // if(error==TERMINAL_OK)
    // printf("The transaction date: %s\n", terminal_data.transactionDate);

     //isCardExpriedTest();
    // getCardExpiryDate(&card_data);
    // getTransactionDate(&terminal_data);
    // error= isCardExpired(&card_data, &terminal_data);
    // if(error== TERMINAL_OK)
    //     printf("The card is not expired");
    // else if(error== EXPIRED_CARD)
    //     printf("The card is expired");

   //getTransactionAmountTest();
    // error= getTransactionAmount(&terminal_data);
    // if(error== TERMINAL_OK)
    //     printf("The transaction amount is valid");
    // else if(error== INVALID_AMOUNT)
    //     printf("The transaction amount is invalid");

  //isBelowMaxAmountTest();
//     getTransactionAmount(&terminal_data);
//     error= isBelowMaxAmount(&terminal_data);
//         if(error== TERMINAL_OK)
//             printf("The transaction amount is below the maximum amount");
//         if(error== EXCEED_MAX_AMOUNT)
//             printf("The transaction amount exceeds the maximum amount");
    // setMaxAmountTest();
//     float maxAmount=15000;
//     error=setMaxAmount(&terminal_data, maxAmount);
//         if(error== TERMINAL_OK)
//             printf("Valid maximum amount");
//         if(error== INVALID_MAX_AMOUNT)
//             printf("Invalid Maximum amount");

 //   isValidCardPANTest();
//     getCardPan(&card_data);
//     error= isValidCardPAN(&card_data);
//        if(error==TERMINAL_OK)
//            printf("PAN is a luhn number");
//         else if(error== INVALID_CARD)
//            printf("Pan is not a luhn number");        
}
void getTransactionDateTest(void)
{
    char name[]="Eman Mohamed Ehab Abdalla";
    ST_terminalData_t terminal_data;
    EN_terminalError_t error;

    error= getTransactionDate(&terminal_data);
    printf("Tester Name: %s\n", name);
    printf("Function Name: getTransactionDate\n");
    printf("Test Case:\n");
    printf("Input Data: None\n");
    printf("Expected data: Today's Date\n");
    if(error==TERMINAL_OK)
        printf("Actual Data: %s\n", terminal_data.transactionDate);

}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{   char arr_exp_date[6];
    char arr_date_check[11];
    int dd, mm, yy;
    int mm2, yy2;
   
    sscanf( termData ->transactionDate, "%d/%d/%d", &dd, &mm, &yy ); //dd/mm/yyyy
    sscanf(cardData ->cardExpirationDate, "%d/%d", &mm2, &yy2); //mm/yy
    
    if (yy<(yy2+2000))
        return TERMINAL_OK;
    else if (yy>(yy2+2000))
        return EXPIRED_CARD;
    else if(yy==(yy2+2000))
    {
        if (mm<mm2)
            return TERMINAL_OK;
        else if (mm>=mm2)
            return EXPIRED_CARD;    
    }
}
void isCardExpriedTest(void)
{   
    char name[]="Eman Mohamed Ehab Abdalla";
    char date1[]="08/28"; //valid
    char date2[]="08/20"; //invalid
    char date3[]="12/22"; //valid
    char date4[]="09/22"; //invalid
    ST_terminalData_t terminal_data;
    ST_cardData_t card_data;
    EN_terminalError_t error;
    getTransactionDate(&terminal_data);
    printf("Tester Name: %s\n", name);
    printf("Function Name: isCardExpired\n");

    strcpy(card_data.cardExpirationDate, date1);
    error= isCardExpired(&card_data, &terminal_data);
    printf("Test Case 1:\n");
    printf("Input Data: Expiry date= %s, Transaction date= %s\n", date1, terminal_data.transactionDate);
    printf("Expected Result: Card is not expired\n");
         if (error== TERMINAL_OK)
        printf("Actual Result: The card is not expired\n");
        if (error== EXPIRED_CARD)
        printf("Actual Result: The card is expired\n");

    strcpy(card_data.cardExpirationDate, date2);
    error= isCardExpired(&card_data, &terminal_data);
    printf("Test Case 2:\n");
    printf("Input Data: Expiry date= %s, Transaction date= %s\n", date2, terminal_data.transactionDate);
    printf("Expected Result: Card is expired\n");
         if (error== TERMINAL_OK)
        printf("Actual Result: The card is not expired\n");
        if (error== EXPIRED_CARD)
        printf("Actual Result: The card is expired\n");    
    
    strcpy(card_data.cardExpirationDate, date3);
    error= isCardExpired(&card_data, &terminal_data);
    printf("Test Case 3:\n");
    printf("Input Data: Expiry date= %s, Transaction date= %s\n", date3, terminal_data.transactionDate);
    printf("Expected Result: Card is not expired\n");
         if (error== TERMINAL_OK)
        printf("Actual Result: The card is not expired\n");
        if (error== EXPIRED_CARD)
        printf("Actual Result: The card is expired\n"); 

    strcpy(card_data.cardExpirationDate, date4);
    error= isCardExpired(&card_data, &terminal_data);
    printf("Test Case 4:\n");
    printf("Input Data: Expiry date= %s, Transaction date= %s\n", date4, terminal_data.transactionDate);
    printf("Expected Result: Card is expired\n");
         if (error== TERMINAL_OK)
        printf("Actual Result: The card is not expired\n");
        if (error== EXPIRED_CARD)
        printf("Actual Result: The card is expired\n");     
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    float trans_amount;
    printf("Enter transaction amount: ");
    scanf("%f", &trans_amount);

    //trans_amount=termData->transAmount;

    if(trans_amount<=0)
        return INVALID_AMOUNT;
    else
    {
        termData->transAmount= trans_amount;
        return TERMINAL_OK;
    }
}
void getTransactionAmountTest(void)
{
    char name[]="Eman Mohamed Ehab Abdalla";
    float a= 5000;
    float b= 600.55;
    float c= 0.0;
    float d= -79.5;
    ST_terminalData_t terminal_data;
    EN_terminalError_t error;
    printf("Tester Name: %s\n",name);
    printf("Function Name: getTransactionAmount\n");

    terminal_data.transAmount=a;
    error= getTransactionAmount(&terminal_data);
    printf("Test Case 1:\n");
    printf("Input Data: %.f\n", a);
    printf("Expected Result: Transaction amount is valid\n");
    if(error==TERMINAL_OK)
        printf("Actual Result: Transaction amount is valid\n");
    else if(error== INVALID_AMOUNT)
        printf("Actual Result: Transaction amount is invalid\n");

    terminal_data.transAmount=b;
    error= getTransactionAmount(&terminal_data);
    printf("Test Case 2:\n");
    printf("Input Data: %f\n", b);
    printf("Expected Result: Transaction amount is valid\n");
    if(error==TERMINAL_OK)
        printf("Actual Result: Transaction amount is valid\n");
    else if(error== INVALID_AMOUNT)
        printf("Actual Result: Transaction amount is invalid\n");    

    terminal_data.transAmount=c;
    error= getTransactionAmount(&terminal_data);
    printf("Test Case 3:\n");
    printf("Input Data: %f\n", c);
    printf("Expected Result: Transaction amount is invalid\n");
    if(error==TERMINAL_OK)
        printf("Actual Result: Transaction amount is valid\n");
    else if(error== INVALID_AMOUNT)
        printf("Actual Result: Transaction amount is invalid\n"); 

    terminal_data.transAmount=d;
    error= getTransactionAmount(&terminal_data);
    printf("Test Case 4:\n");
    printf("Input Data: %f\n", d);
    printf("Expected Result: Transaction amount is invalid\n");
    if(error==TERMINAL_OK)
        printf("Actual Result: Transaction amount is valid\n");
    else if(error== INVALID_AMOUNT)
        printf("Actual Result: Transaction amount is invalid\n"); 
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    float transactionAmount, maxAmount;
    transactionAmount=termData->transAmount;
    maxAmount= 15000.00;
    if(transactionAmount>maxAmount)
        return EXCEED_MAX_AMOUNT;
    if(transactionAmount<=maxAmount)
       return TERMINAL_OK;
        
    
}
void isBelowMaxAmountTest(void)
{
    char name[]="Eman Mohamed Ehab Abdalla";
    float a= 6000.00;
    float b= 499.99;
    float c= 20000.00;
    ST_terminalData_t terminal_data;
    EN_terminalError_t error;
    printf("Tester Name: %s\n",name);
    printf("Function Name: isBelowMaxAmountTest\n");

    terminal_data.transAmount=a;
    error= isBelowMaxAmount(&terminal_data);
    printf("Test Case 1:\n");
    printf("Input Data: %f\n", a);
    printf("Expected Result: Below maximum amount\n");
    if(error==TERMINAL_OK)
        printf("Actual Result: Below maximum amount\n");
    else if(error== EXCEED_MAX_AMOUNT)
        printf("Actual Result: Exceeds maximum amount\n");

    terminal_data.transAmount=b;
    error= isBelowMaxAmount(&terminal_data);
    printf("Test Case 2:\n");
    printf("Input Data: %f\n", b);
    printf("Expected Result: Below maximum amount\n");
    if(error==TERMINAL_OK)
        printf("Actual Result: Below maximum amount\n");
    else if(error== EXCEED_MAX_AMOUNT)
        printf("Actual Result: Exceeds maximum amount\n");     
    
    terminal_data.transAmount=c;
    error= isBelowMaxAmount(&terminal_data);
    printf("Test Case 3:\n");
    printf("Input Data: %f\n", c);
    printf("Expected Result: Exceeds maximum amount\n");
    if(error==TERMINAL_OK)
        printf("Actual Result: Below maximum amount\n");
    else if(error== EXCEED_MAX_AMOUNT)
        printf("Actual Result: Exceeds maximum amount\n");
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    maxAmount=15000;
    if(maxAmount<=0)
        return INVALID_MAX_AMOUNT;
    else
    {
        termData ->maxTransAmount = maxAmount;
        return TERMINAL_OK;
    }

}
void setMaxAmountTest(void)
{
    char name[]="Eman Mohamed Ehab Abdalla";
    float a= 15000.00;
    float b= 0.0;
    float c= -5000.55;
    ST_terminalData_t terminal_data;
    EN_terminalError_t error;
    printf("Tester Name: %s\n",name);
    printf("Function Name: SetMaxAmount\n");

    setMaxAmount(&terminal_data, a);
    printf("Test Case 1:\n");
    printf("Input Data: %f\n",a);
    printf("Expected Result: Valid maximum amount\n");
    if(error==TERMINAL_OK)
        printf("Valid maximum amount\n");
    else if(error==INVALID_MAX_AMOUNT)
        printf("Invalid maximum amount\n"); 

    setMaxAmount(&terminal_data, b);
    printf("Test Case 2:\n");
    printf("Input Data: %f\n",b);
    printf("Expected Result: Invalid maximum amount\n");
    if(error==TERMINAL_OK)
        printf("Valid maximum amount\n");
    else if(error==INVALID_MAX_AMOUNT)
        printf("Invalid maximum amount\n");

   setMaxAmount(&terminal_data, c);
    printf("Test Case 3:\n");
    printf("Input Data: %f\n",c);
    printf("Expected Result: Invalid maximum amount\n");
    if(error==TERMINAL_OK)
        printf("Valid maximum amount\n");
    else if(error==INVALID_MAX_AMOUNT)
        printf("Invalid maximum amount\n");     
}
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
    char pan_num[20];
    strcpy(pan_num, cardData ->primaryAccountNumber);
    int pan_num_len= strlen(pan_num);

    long long pan;
    sscanf(pan_num, " %llu", &pan);

    
    unsigned long long q=pan;
    int i, rem, sum=0;
    for(i=0; i<pan_num_len; i++)
    {
        rem = q%10;
        if((i % 2) != 0)
            rem = rem*2;
        if(rem>9)
            rem = rem - 9;
        sum = sum + rem;
        q=q/10;
    }

    bool Luhn_check=0;
    if ((sum%10)!=0)
        Luhn_check=true;

    if (pan_num_len<16 || pan_num_len>19|| Luhn_check )
        return INVALID_CARD;
    else
    {
        strcpy(cardData->primaryAccountNumber, pan_num);
        return TERMINAL_OK;
    }
}
void isValidCardPANTest(void)
{
    char name[]="Eman Mohamed Ehab Abdalla";
    char number1[]="468749305327270045"; //max valid
    char number2[]="98532885423149745"; //invalid

    ST_cardData_t card_data;
    EN_cardError_t error;
    printf("Tester Name: %s\n",name);
    printf("Function Name: isValidCardPANTest\n");

        strcpy(card_data.primaryAccountNumber, number1);
        error=isValidCardPAN(&card_data);
        printf("Test Case 1:\n");
        printf("Input Data: %s\n", number1);
        printf("Expected Result: Luhn number\n");
         if (error== TERMINAL_OK)
        printf("Actual Result: The PAN is a luhn number\n");
        if (error== INVALID_CARD)
        printf("Actual Result: The PAN is not a luhn number\n");

        strcpy(card_data.primaryAccountNumber, number2);
        error= isValidCardPAN(&card_data);
        printf("Test Case 2:\n");
        printf("Input Data: %s\n", number2);
        printf("Expected Result: Not a luhn number\n");
         if (error== TERMINAL_OK)
        printf("Actual Result: The PAN is a luhn number\n");
        if (error== INVALID_CARD)
        printf("Actual Result: The PAN is not a luhn number\n"); 

  
}

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include"Card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    char arr_check[25];
    printf("Enter the cardholder's name: ");
    scanf(" %[^\n]",arr_check);
    //strcpy(arr_check,cardData ->cardHolderName);
    int len=strlen(arr_check);
    int i;
    bool Name=false, NotaName=false;
    for(i=0; arr_check[i]!='\0'; i++)
    {   Name = (arr_check[i] >= 'A'&& arr_check[i]<='Z') || (arr_check[i]>= 'a' && arr_check[i]<= 'z') || arr_check[i]==' ';
        if(!(Name)) {
            NotaName=true;
            break;
        }
    }

    if (len<20 || len>24 ||NotaName )
        return WRONG_NAME;
    else
    {
        strcpy(cardData->cardHolderName, arr_check);
        return CARD_OK;
    }
}

void testCardModule(void)
{   
  ST_cardData_t card_data;
    EN_cardError_t error ;


//getCardHolderTest();
    // error= getCardHolderName(&card_data);
    // if (error== CARD_OK)
    //     {printf("The card holder name's is valid\n");
    //     }
    // if (error== WRONG_NAME)
    //     printf("The card holder name's is invalid\n");

  //getCardExpiryDateTest();
    // error= getCardExpiryDate(&card_data);
    // if (error== CARD_OK)
    //     printf("The card expiry date's is valid\n");
    // if (error== WRONG_EXP_DATE)
    //     printf("The card expiry date's is Invalid\n");

    //getCardPANTest();
    // error= getCardPan(&card_data);
    // if (error== CARD_OK)
    //     printf("The card primary number's is valid\n");
    // if (error== WRONG_PAN)
    //     printf("The card primary number's is Invalid\n");    
    
}
void getCardHolderTest(void)
{
    char name[]="Eman Mohamed Ehab Abdalla";
    char name1[]="Dalia Borham Ibrahim";
    char name2[]="Eva2 Christ**8er B08kle/";
    char name3[]="Evan Christopher Buckley";
    char name4[]="Cooshi Bobby Freeman";
    char name5[]="Eddie Diaz";
    ST_cardData_t card_data;
    EN_cardError_t error;
    printf("Tester Name: %s\n",name);
    printf("Function Name: getCardHolderName\n");

    strcpy(card_data.cardHolderName, name1);
     error=getCardHolderName(&card_data);
    printf("Test Case 1:\n");
    printf("Input Data: %s\n", name1);
    printf("Expected result: Valid name\n ");
    if (error== CARD_OK)
        printf("Actual result: The card holder name's is valid\n");
    if (error== WRONG_NAME)
        printf("Actual result: The card holder name's is invalid\n");

    strcpy(card_data.cardHolderName, name2);
     error=getCardHolderName(&card_data);
    printf("Test Case 2:\n");
    printf("Input Data: %s\n", name2);
    printf("Expected result: Invalid name\n ");
    if (error== CARD_OK)
        printf("Actual result: The card holder name's is valid\n");
    if (error== WRONG_NAME)
        printf("Actual result: The card holder name's is invalid\n");

    strcpy(card_data.cardHolderName, name3);
     error=getCardHolderName(&card_data);
    printf("Test Case 3:\n");
    printf("Input Data: %s\n", name3);
    printf("Expected result: Valid name\n ");
    if (error== CARD_OK)
        printf("Actual result: The card holder name's is valid\n");
    if (error== WRONG_NAME)
        printf("Actual result: The card holder name's is invalid\n");

    strcpy(card_data.cardHolderName, name4);
     error=getCardHolderName(&card_data);
    printf("Test Case 4:\n");
    printf("Input Data: %s\n", name4);
    printf("Expected result: Valid name\n ");
    if (error== CARD_OK)
        printf("Actual result: The card holder name's is valid\n");
    if (error== WRONG_NAME)
        printf("Actual result: The card holder name's is invalid\n");    

    strcpy(card_data.cardHolderName, name5);
     error=getCardHolderName(&card_data);
    printf("Test Case 5:\n");
    printf("Input Data: %s\n", name5);
    printf("Expected result: Invalid name\n ");
    if (error== CARD_OK)
        printf("Actual result: The card holder name's is valid\n");
    if (error== WRONG_NAME)
        printf("Actual result: The card holder name's is invalid\n");
}    
    EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
    {
        char arr_date_check[6];
        printf("Enter the card's expiry date: ");
        scanf(" %[^\n]", arr_date_check);

        //strcpy(arr_date_check, cardData ->cardExpirationDate);

        int dlen=strlen(arr_date_check);
        int i;
        bool validformat=0, invalidformat=0, check=0;

        for(i=0; i<1; i++)
        {
            validformat=((arr_date_check[i]>='0') && (arr_date_check[i]<='1'));
            if(!(validformat))
            {
                invalidformat=true;
                break;
            }
            if(arr_date_check[i]== '0')
                check=true;
        }
        for(i=1; i<2; i++)
        {   
            if (check == true)
                validformat=((arr_date_check[i]>='1') && (arr_date_check[i]<='9'));
            else    
                validformat=((arr_date_check[i]>='0') && (arr_date_check[i]<='2'));
            if(!(validformat))
            {
                invalidformat=true;
                break;
            }
        }
        if(!(invalidformat==true))
        {
            validformat=(arr_date_check[2]=='/');
             if(!(validformat))
                invalidformat=true;
        }
        if(!(invalidformat==true))
        {
            for(i=3; i<5; i++)
        {
            validformat=(arr_date_check[i]>='0') && (arr_date_check[i]<='9');
            if(!(validformat))
            {
                invalidformat=true;
                break;
            }
        }
        int check_null= ((arr_date_check[0]=='0') && (arr_date_check[1]=='0')) || ((arr_date_check[3]=='0') && (arr_date_check[4]=='0'));
        if(check_null!=0)
            invalidformat=true;
        }
        if(dlen<5 || dlen>5 || invalidformat)
            return WRONG_EXP_DATE;
        else  
        {
            strcpy(cardData->cardExpirationDate, arr_date_check);
            return CARD_OK;
        }  


    }
    void getCardExpiryDateTest (void)
    {
        char name[]="Eman Mohamed Ehab Abdalla";
        char date1[]="08/28";
        char date2[]="3^/&9";
        char date3[]="12*25";
        char date4[]="00/00";
        char date5[]="13/22";
        ST_cardData_t card_data;
        EN_cardError_t error;
        printf("Tester Name: %s\n",name);
        printf("Function Name: getCardExpiryDate\n");
        
        strcpy(card_data.cardExpirationDate, date1);
        error= getCardExpiryDate(&card_data);
        printf("Test Case 1:\n");
        printf("Input Data: %s\n", date1);
        printf("Expected Result: Valid date\n");
         if (error== CARD_OK)
        printf("Actual Result: The card expiry date's is valid\n");
        if (error== WRONG_EXP_DATE)
        printf("Actual Result: The card expiry date's is Invalid\n");
        
        strcpy(card_data.cardExpirationDate, date2);
        error= getCardExpiryDate(&card_data);
        printf("Test Case 2:\n");
        printf("Input Data: %s\n", date2);
        printf("Expected Result: Invalid date\n");
         if (error== CARD_OK)
        printf("Actual Result: The card expiry date's is valid\n");
        if (error== WRONG_EXP_DATE)
        printf("Actual Result: The card expiry date's is Invalid\n");

        strcpy(card_data.cardExpirationDate, date3);
        error= getCardExpiryDate(&card_data);
        printf("Test Case 3:\n");
        printf("Input Data: %s\n", date3);
        printf("Expected Result: Invalid date\n");
         if (error== CARD_OK)
        printf("Actual Result: The card expiry date's is valid\n");
        if (error== WRONG_EXP_DATE)
        printf("Actual Result: The card expiry date's is Invalid\n");

        strcpy(card_data.cardExpirationDate, date4);
        error= getCardExpiryDate(&card_data);
        printf("Test Case 4:\n");
        printf("Input Data: %s\n", date4);
        printf("Expected Result: Invalid date\n");
         if (error== CARD_OK)
        printf("Actual Result: The card expiry date's is valid\n");
        if (error== WRONG_EXP_DATE)
        printf("Actual Result: The card expiry date's is Invalid\n");

        strcpy(card_data.cardExpirationDate, date5);
        error= getCardExpiryDate(&card_data);
        printf("Test Case 5:\n");
        printf("Input Data: %s\n", date5);
        printf("Expected Result: Invalid date\n");
         if (error== CARD_OK)
        printf("Actual Result: The card expiry date's is valid\n");
        if (error== WRONG_EXP_DATE)
        printf("Actual Result: The card expiry date's is Invalid\n");
    }
EN_cardError_t getCardPan(ST_cardData_t *cardData)
{
    char pan_num[20];
    printf("Enter the primary account number: ");
    scanf(" %[^\n]",pan_num);

    //strcpy(pan_num ,cardData ->primaryAccountNumber);

    int pan_num_len= strlen(pan_num);
    int i;
    bool Numeric=0 , NOTnumeric=0;
    for(i=0; i<pan_num_len; i++)
    {
        Numeric= (pan_num[i]<='9') && (pan_num[i]>='0');
        if(!(Numeric))
            {NOTnumeric=true;
            break;}
    }
    long long pan;
    sscanf(pan_num, " %llu", &pan);
    if(pan==0)
        return WRONG_PAN;

    if (pan_num_len<16 || pan_num_len>19 ||NOTnumeric )
        return WRONG_PAN;
    else
    {
        strcpy(cardData->primaryAccountNumber, pan_num);
        return CARD_OK;
    }
}
void getCardPANTest (void)
{ 
    char name[]="Eman Mohamed Ehab Abdalla";
    char number1[]="63048179815363852"; //valid
    char number2[]="6706513894593652"; // min valid
    char number3[]="6771723153640090471"; //max valid
    char number4[]="67717231536400904712"; //invalid
    char number5[]="172315364009042"; //invalid
    char number6[]="63893hd3678gd9*27g";//invalid
    char number7[]="0000000000000000000"; //invalid


    ST_cardData_t card_data;
    EN_cardError_t error;
    printf("Tester Name: %s\n",name);
    printf("Function Name: getCardPan\n");

        strcpy(card_data.primaryAccountNumber, number1);
        error= getCardPan(&card_data);
        printf("Test Case 1:\n");
        printf("Input Data: %s\n", number1);
        printf("Expected Result: Valid PAN\n");
         if (error== CARD_OK)
        printf("Actual Result: The card primary number's is valid\n");
        if (error== WRONG_PAN)
        printf("Actual Result: The card primary number's is Invalid\n");

        strcpy(card_data.primaryAccountNumber, number2);
        error= getCardPan(&card_data);
        printf("Test Case 2:\n");
        printf("Input Data: %s\n", number2);
        printf("Expected Result: Valid PAN\n");
         if (error== CARD_OK)
        printf("Actual Result: The card primary number's is valid\n");
        if (error== WRONG_PAN)
        printf("Actual Result: The card primary number's is Invalid\n"); 

        strcpy(card_data.primaryAccountNumber, number3);
        error= getCardPan(&card_data);
        printf("Test Case 3:\n");
        printf("Input Data: %s\n", number3);
        printf("Expected Result: Valid PAN\n");
         if (error== CARD_OK)
        printf("Actual Result: The card primary number's is valid\n");
        if (error== WRONG_PAN)
        printf("Actual Result: The card primary number's is Invalid\n");   

        strcpy(card_data.primaryAccountNumber, number4);
        error= getCardPan(&card_data);
        printf("Test Case 4:\n");
        printf("Input Data: %s\n", number4);
        printf("Expected Result: Invalid PAN\n");
         if (error== CARD_OK)
        printf("Actual Result: The card primary number's is valid\n");
        if (error== WRONG_PAN)
        printf("Actual Result: The card primary number's is Invalid\n"); 

        strcpy(card_data.primaryAccountNumber, number5);
        error= getCardPan(&card_data);
        printf("Test Case 5:\n");
        printf("Input Data: %s\n", number5);
        printf("Expected Result: Invalid PAN\n");
         if (error== CARD_OK)
        printf("Actual Result: The card primary number's is valid\n");
        if (error== WRONG_PAN)
        printf("Actual Result: The card primary number's is Invalid\n");

        strcpy(card_data.primaryAccountNumber, number6);
        error= getCardPan(&card_data);
        printf("Test Case 6:\n");
        printf("Input Data: %s\n", number6);
        printf("Expected Result: Invalid PAN\n");
         if (error== CARD_OK)
        printf("Actual Result: The card primary number's is valid\n");
        if (error== WRONG_PAN)
        printf("Actual Result: The card primary number's is Invalid\n");

        strcpy(card_data.primaryAccountNumber, number7);
        error= getCardPan(&card_data);
        printf("Test Case 7:\n");
        printf("Input Data: %s\n", number7);
        printf("Expected Result: Invalid PAN\n");
         if (error== CARD_OK)
        printf("Actual Result: The card primary number's is valid\n");
        if (error== WRONG_PAN)
        printf("Actual Result: The card primary number's is Invalid\n");

}




    

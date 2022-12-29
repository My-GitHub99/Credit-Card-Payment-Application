/*
 * terminal.c
 *
 *  Created on: Dec 6, 2022
 *      Author: ahmed bahaa alkomy
 */
#include "terminal.h"
char getTransDate[][30]={"25/06/2023","33/06/2020","20/13/2022","222/07/2019","18606/2018","17/1122015","a+/07/2R8_",""};
char transDate[][30]={"25/06/2023","15/06/2020","20/11/2022","22/07/2018","18/08/2018"};
char expDate[] ="08/21";
float getAmountData[3]={0,21213,-300};
float maxAmountData[5]={3000,4000,5000,6000,1500};
float setmaxAmountData[3]={3000,0,-500};
char transaction_year[3];
char transaction_month[3];
char transaction_day[3];
ST_terminalData_t *termData=NULL;





EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){
	if(maxAmount<0 || maxAmount==0){
	return INVALID_MAX_AMOUNT;
	}
	else{
    termData->maxTransAmount= maxAmount;
    return TERMINAL_OK;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
	if(termData->transAmount > termData->maxTransAmount){
		return EXCEED_MAX_AMOUNT;
	}
	else{
		return TERMINAL_OK;
	}

}


EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
	if(termData->transAmount ==0 ||termData->transAmount<0){
		return INVALID_AMOUNT;
	}
	else{
   return TERMINAL_OK;
	}
}

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){

 for(int j= 0;j<2;j++){
	 	 	transaction_day[j]=termData->transactionDate[j];
	 	 		}

 for(int j= 0;j<2;j++){
 	 	transaction_month[j]=termData->transactionDate[j+3];
 	 		}

 if(strlen((char*) termData->transactionDate) !=10 || termData->transactionDate[2]!='/'||termData->transactionDate[5]!='/'||atoi(transaction_day)>31||atoi(transaction_month)>12){
 	return WRONG_DATE;
 }

 for(int i=0;i<2;i++){
   if(isdigit(termData->transactionDate[i])==0){
 	return WRONG_NAME;
   }
   for(int i=0;i<2;i++){
     if(isdigit(termData->transactionDate[i+3])==0){
   	return WRONG_NAME;
     }
    for(int i=0;i<4;i++){
      if(isdigit(termData->transactionDate[i+6])==0){
       return WRONG_NAME;
       }
  }
   }
 }

 	return TERMINAL_OK;

 }

 EN_terminalError_t isCardExpired( ST_cardData_t *cardData,ST_terminalData_t *termData){
	 char expire_year[3];
	 char expire_month[3];

	 for(int i= 0;i<2;i++){
	 	expire_year[i]=cardData->cardExpirationDate[i+3];
	 	}
	 	for(int j= 0;j<2;j++){
	 	expire_month[j]=cardData->cardExpirationDate[j];
	 		}
	 for(int c=0;c<2;c++){
	transaction_year[c]= termData->transactionDate[c+8];
	 }

	 for(int k=0;k<2;k++){
	transaction_month[k]= termData->transactionDate[k+3];

	 }

	 if(atoi(transaction_year)>atoi(expire_year)){
		 return EXPIRED_CARD;
	 }
	 else if(atoi(transaction_year)==atoi(expire_year) && atoi(transaction_month)> atoi(expire_month)){
		 return EXPIRED_CARD;

	 }
	 else{
		 return TERMINAL_OK;
	 }
	 }


 void setMaxAmountTest(void){

    	 printf("tester Name: ahmed bahaa  \n");

    		 	printf("function name: setMaxAmountTest\n\n");
    		 	for(int i=0;i<sizeof(setmaxAmountData)/sizeof(setmaxAmountData[0]);i++){
    		 	printf("Test Case %d\n",i+1);
    		 	printf("input set max transaction amount: %f \n",setmaxAmountData[i]);
    		 	char expected_result[25];
    		 	printf("Expected Result:   ");
    		 	fflush(stdout);
    		 	fgets(expected_result,24,stdin);
    		 	if(setMaxAmount(termData,setmaxAmountData[i])==0){
    		 	printf("actual results: Terminal OK \n\n");
    		 	}
    		 	else {
    		 	printf("actual results: invalid max amount\n\n ");
    		 	}
    		 	}

     }


 void isBelowMaxAmountTest(void){

   	 printf("tester Name: ahmed bahaa  \n");

   		 	printf("function name: isBelowMaxAmountTest\n\n");
   		 	for(int i=0;i<sizeof(maxAmountData)/sizeof(maxAmountData[0]);i++){
   		 	printf("Test Case %d\n",i+1);
   		    termData->transAmount=maxAmountData[i];
   		 	printf("input transaction amount: %f \n",  termData->transAmount);
   		    termData ->maxTransAmount=4000;
   		 	printf("max Transaction Amount : %f\n",termData ->maxTransAmount);
   		 	char expected_result[25];
   		 	printf("Expected Result:   ");
   		 	fflush(stdout);
   		 	fgets(expected_result,24,stdin);
   		 	if(isBelowMaxAmount(termData)==0){
   		 	printf("actual results: Terminal OK \n\n");
   		 	}
   		 	else {
   		 	printf("actual results: exceed amount\n\n ");
   		 	}
   		 	}

    }


 void getTransactionAmountTest(void){

  	 printf("tester Name: ahmed bahaa  \n");
  		 	printf("function name: getTransactionAmountTest\n\n");
  		 	for(int i=0;i<sizeof(getAmountData)/sizeof(getAmountData[0]);i++){
  		 	printf("Test Case %d\n",i+1);
  		 	termData->transAmount=getAmountData[i];
  		 	printf("input transaction amount: %f \n",termData->transAmount);
  		 	char expected_result[25];
  		 	printf("Expected Result:   ");
  		 	fflush(stdout);
  		 	fgets(expected_result,24,stdin);
  		 	if(getTransactionAmount(termData)==0){
  		 	printf("actual results: Terminal OK \n\n");
  		 	}
  		 	else {
  		 	printf("actual results: invalid amount\n\n ");
  		 	}
  		 	}

   }




 void isCardExpriedTest(void){

	 printf("tester Name: ahmed bahaa  \n");

		 	printf("function name: isCardExpriedTest\n\n");
		 	for(int i=0;i<strlen(transDate[i]);i++){
		 	printf("Test Case %d\n",i+1);
		 	int j=0;
		 	int k=0;
		 	 while(expDate[j]!='\0'){
		 		cardData->cardExpirationDate[j]= expDate[j];
		 		j++;
		 		 		}
		 	cardData->cardExpirationDate[j]='\0';

		 	while(transDate[i][k]!='\0'){
		 			 		termData->transactionDate[k]= transDate[i][k];
		 			 		k++;
		 			 		 		}
		 	termData->transactionDate[k]='\0';

		 	printf("input transaction date : %s \n",termData->transactionDate);
		 	printf("input expiration date: %s\n",cardData->cardExpirationDate);
		 	for(int j=0;j<=strlen(transDate[i]);j++){
		 	termData->transactionDate[j]=transDate[i][j];
		 		 	}

		 	char expected_result[25];
		 	printf("Expected Result:   ");
		 	fflush(stdout);
		 	fgets(expected_result,24,stdin);
		 	if(isCardExpired(cardData,termData)==0){
		 	printf("actual results: Terminal OK \n\n");
		 	}
		 	else {
		 	printf("actual results: Card Expired\n\n ");
		 	}
		 	}

 }


 void GetTransactionDateTest(void){

	 printf("tester Name: ahmed bahaa  \n");

	 	printf("function name: GetTransactionDataTest\n\n");
	 	for(int i=0;i<sizeof(getTransDate)/sizeof(getTransDate[0]);i++){
	 	printf("Test Case %d\n",i+1);
	 	int j=0;
	 		while(getTransDate[i][j]!='\0'){
	 		termData->transactionDate[j]= getTransDate[i][j];
	 		j++;
	 		}
	 	termData->transactionDate[j]='\0';
	 	printf("input data : %s \n",termData->transactionDate);
	 	printf("input name length=  %d\n",strlen((char*)termData->transactionDate));
	 	char expected_result[25];
	 	printf("Expected Result:   ");
	 	fflush(stdout);
	 	fgets(expected_result,24,stdin);

	 	if(getTransactionDate(termData)==0){
	 	printf("actual results: Terminal OK \n\n");
	 	}
	 	else {
	 	printf("actual results: Wrong Date\n\n ");
	 	}
	 	}
	 	}

/*int main()
{
termData= (ST_terminalData_t*)malloc(sizeof(ST_terminalData_t));
cardData= (ST_cardData_t*)malloc(sizeof(ST_cardData_t));
//GetTransactionDateTest();
//isCardExpriedTest();
//getTransactionAmountTest();
//isBelowMaxAmountTest();
setMaxAmountTest();
free(termData);
free(cardData);
}*/

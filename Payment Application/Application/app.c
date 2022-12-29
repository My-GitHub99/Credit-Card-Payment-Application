/*
 * app.c
 *
 *  Created on: Dec 6, 2022
 *      Author: ahmed bahaa alkomy
 */

#include "app.h"

ST_transaction_t *transdata=NULL;
ST_cardData_t *carddata=NULL;
ST_terminalData_t *termdata=NULL;


ST_user_info_t user_story[]={{"Mohamed Ahmed Soliman","4517 0519 4588 3511","02/26",1000,4000,8000},{"aly zain abdelhamid aly","0081 6483 3028 3333","07/24",5000,4000,6000},{"samir ahmed maged moa","8912 0519 0734 4444","03/27",3000,4000,2000},{"maria samir elsayed aly","6632 0044 1235 7777","11/22",1000,4000,4000},{"laila ahmed mohamed wa","5577 9944 3322 8769","05/24",1000,4000,4000}};
int story_no;
char trans_Date[]="15/12/2022";

void cpystring (char* str1,char* str2){
int i=0;
while(str2[i]!='\0'){
	str1[i]=str2[i];
	i++;
}
str1[i]='\0';
}


void appStart(){
	transdata->transactionSequenceNumber=0;
	for(story_no=0;story_no<sizeof(user_story)/sizeof(user_story[0]);story_no++){

	cpystring((char*)carddata->cardHolderName,(char*)user_story[story_no].user_name);
	cpystring((char*)carddata->primaryAccountNumber,(char*)user_story[story_no].user_PAN);
	cpystring((char*)carddata->cardExpirationDate,(char*)user_story[story_no].user_cardExpDate);
	printf("\n\n");
	printf("#############CARD DETECTED###############\n\n");
	printf("*CARD INFO*\n");
    printf("cardholdername: %s\n",carddata->cardHolderName);
    printf("PAN Number: %s\n",carddata->primaryAccountNumber);
    printf("cardExpiration date: %s\n\n",carddata->cardExpirationDate);
    printf("VALIDATING CARD DATA.......\n");


	if(getCardHolderName(carddata)==WRONG_NAME){
		printf("CARD ERROR: Invalid CardHolder Name\n\n");
		printf("Name lenght is %d  \n",strlen((char*)carddata->cardHolderName));
		continue;
	}
	else{
		printf(">>>>>Valid CARDHOLDER FORMAT\n");
	}
	if( getCardExpiryDate(carddata)==WRONG_EXP_DATE){
		printf("CARD ERROR: INVALID EXPIRATION DATE,Exp date should be 5 elements in the format MM/YY \n\n");
		continue;
	}
	else{
		printf(">>>>>VALID EXPIRATION DATE FORMAT\n");
	}
	if(getCardPAN(carddata)==WRONG_PAN){
		printf("CARD ERROR: INVALID PAN FORMAT\n\n");
		continue;
	}
	else{
		printf(">>>>>VALID PAN NUMBER\n\n");
	}
	printf("************CARD DATA FORMAT IS VALID**************\n\n");

	printf("VALIDATING TERMINAL SETTINGS.......\n\n");

cpystring((char*)termdata->transactionDate,trans_Date);
if(getTransactionDate(termdata)==WRONG_DATE){
	printf("TERMINAL ERROR: WRONG TRANSACTION DATE\n\n");
	continue;
}
else{
	printf(">>>>>VALID TRANSACTION DATE FORMAT\n");
}
 if(isCardExpired(carddata,termdata)==EXPIRED_CARD){
	 printf("\n");
	 printf("!!!!!!!!CARD ERROR: CARD IS EXPIRED\n");
	 printf("TRANSACTION DATE:%s\n",termdata->transactionDate);
	 printf("CARD EXPIRED AT:%s\n\n",carddata->cardExpirationDate);
	 continue;
 }
 else{
	 printf(">>>>>CARD IS NOT EXPIRED\n");
 }
 termdata->transAmount=user_story[story_no].user_TransAmount;
 if( getTransactionAmount(termdata)==INVALID_AMOUNT){
	 printf("TERMINAL ERROR: INVALID AMOUNT\n\n");
	 continue;
 }
 else{
 printf(">>>>>VALID TRANSACTION AMOUNT\n");
 }
termdata->maxTransAmount=user_story[story_no].user_terminalMaxAmount;
if(setMaxAmount(termdata,user_story[story_no].user_terminalMaxAmount)==INVALID_MAX_AMOUNT){
	printf("TERMINAL ERROR: MAX Transaction amount is INVALID\n\n");
	continue;
}
else{
	printf(">>>>>VALID TERMINAL MAX TRANSATION AMOUNT\n");
}
if(isBelowMaxAmount(termdata)==EXCEED_MAX_AMOUNT){
	printf("\n");
	printf("!!!!!!!!!TERMINAL ERROR: TRANSACTION AMOUNT EXCEEDS THE MAX TERMINAL LIMIT\n");
	printf("TRANSACTION AMOUNT: %f\n",termdata->transAmount);
	printf("TERMINAL MAX TRANSACTION AMOUNT:%f\n\n",termdata->maxTransAmount);
	continue;
}

else{
	printf(">>>>>TRANSCTION IS WITHIN TERMINAL LIMITS\n\n");
}
printf("***************TERMINAL SETTINGS IS VALID**************\n\n");

printf("SERVER VALIDATION........\n");

cpystring((char*)transdata->cardHolderData.cardExpirationDate,(char*)carddata->cardExpirationDate);
cpystring((char*)transdata->cardHolderData.cardHolderName,(char*)carddata->cardHolderName);
cpystring((char*)transdata->cardHolderData.primaryAccountNumber,(char*)carddata->primaryAccountNumber);
transdata->terminalData.maxTransAmount=termdata->maxTransAmount;
transdata->terminalData.transAmount=termdata->transAmount;
cpystring((char*)transdata->terminalData.transactionDate,(char*)termdata->transactionDate);

EN_transStat_t server_result = recieveTransactionData(transdata);
if(server_result==FRAUD_CARD){
	printf("!!!!!!!SERVER ERROR: TRANSACTION DECLINED, INVALID ACCOUNT, ACCOUNT NOT FOUND IN DATABASE\n\n");
	saveTransaction(transdata);
	continue;
}
else{
	printf(">>>>>ACCOUNT FOUND in DATABASE\n");
}
if(server_result==DECLINED_INSUFFECIENT_FUND){
	printf("\n");
	printf("!!!!!!SERVER ERROR: TRANSACTION DECLINED, INDUFFCIENT FUND\n");
	printf("TRANSACTION AMOUNT %f\n",transdata->terminalData.transAmount);
	printf("BALANCE:%f\n\n",accountRefrence->balance);
	saveTransaction(transdata);
	continue;
}
else{
	printf(">>>>>ACCOUNT BALANCE CHECKED, SUFFECIENT FUND\n");
}
if(server_result==DECLINED_STOLEN_CARD){
	printf("!!!!!!SERVER ERROR: TRANSACTION DECLINED, CARD IS BLOCKED\n\n");
	saveTransaction(transdata);
	continue;
}
else{
	printf(">>>>>ACCOUNT STATUS CHECKED, ACCOUNT IS ACTIVE\n\n");
}
printf("**************SERVER CHECKING COMPLETED, TRANSACTION IS VALID*************\n\n");
printf("****TRANSACTION INFO:****\n");
printf("TRANSACTION AMOUNT: %f\n",transdata->terminalData.transAmount);
printf("ACCOUNT BALANCE:%f\n",accountRefrence->balance);
saveTransaction(transdata);
printf("ACCOUNT UPDATED BALANCE:%f\n",accountRefrence->balance);
printf("SAVING TRANSACTION........\n");
printf("************TRANSACTION SAVED AND COMPLETED SUCCESSFULY**************\n\n\n");
	}
printf("*********ALL SERVER TRANSACTIONS DATABASE**********\n\n");
listSavedTransactions();
}

int main() {
termdata= (ST_terminalData_t*)malloc(sizeof(ST_terminalData_t));
carddata= (ST_cardData_t*)malloc(sizeof(ST_cardData_t));
transdata= (ST_transaction_t*)malloc(sizeof(ST_transaction_t));
accountRefrence= (ST_accountsDB_t*)malloc(sizeof(ST_accountsDB_t));
appStart();
free(termdata);
free(carddata);
free(transdata);
free(accountRefrence);


}

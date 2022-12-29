/*
 * server.c
 *
 *  Created on: Dec 6, 2022
 *      Author: ahmed bahaa alkomy
 */

#include "server.h"

ST_accountsDB_t accountsDB[255]={{2000.0, RUNNING, "8989 3746 1543 6851" },{6000.0, RUNNING, "0081 6483 3028 3333"},{10000.0, RUNNING, "6632 0044 1235 7777"},{8000.0000,RUNNING,"4517 0519 4588 3511"},{2000.0, RUNNING, "8912 0519 0734 4444"},{2000.0, BLOCKED,"5577 9944 3322 8769"}};
ST_transaction_t serverTransData[255]={};
char inputPAN[2][25]={"8989 3746 1543 6851","2345 7498 5746 8902"};
char testBlockedData[]={RUNNING,BLOCKED,RUNNING};
float inputTransAmount[]={500,3000,1500};
ST_transaction_t *transData=NULL;
ST_accountsDB_t *accountRefrence=NULL;
int transCount=0;


void copystring(char* str1,char* str2){
	int i=0;
	while(str2[i]!='\0'){
		str1[i]=str2[i];
		i++;
	}
	str1[i]='\0';
	}

void listSavedTransactions(void){
	for(int i=0;i<transCount;i++){
		printf("Transaction Sequence : %lu\n",serverTransData[i].transactionSequenceNumber);
		printf("Transaction Date : %s\n",serverTransData[i].terminalData.transactionDate);
		printf("Transaction Amount : %f\n",serverTransData[i].terminalData.transAmount);
		serverTransData[i].transState==APPROVED ? printf("Transaction State : APPROVED\n"):printf("Transaction State : DECLINED\n");
		printf("Terminal max amount : %f\n",serverTransData[i].terminalData.maxTransAmount);
		printf("Card holder name: %s\n",serverTransData[i].cardHolderData.cardHolderName);
		printf("PAN: %s\n",serverTransData[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n\n",serverTransData[i].cardHolderData.cardExpirationDate);

	}
}



EN_serverError_t saveTransaction(ST_transaction_t *transData){
if(transData->transState==APPROVED){
	copystring((char*)serverTransData[transData->transactionSequenceNumber].cardHolderData.cardExpirationDate,(char*)transData->cardHolderData.cardExpirationDate);
	copystring((char*)serverTransData[transData->transactionSequenceNumber].cardHolderData.cardHolderName,(char*)transData->cardHolderData.cardHolderName);
	copystring((char*)serverTransData[transData->transactionSequenceNumber].cardHolderData.primaryAccountNumber,(char*)transData->cardHolderData.primaryAccountNumber);
	serverTransData[transData->transactionSequenceNumber].terminalData.maxTransAmount=transData->terminalData.maxTransAmount;
	serverTransData[transData->transactionSequenceNumber].terminalData.transAmount=transData->terminalData.transAmount;
	copystring((char*)serverTransData[transData->transactionSequenceNumber].terminalData.transactionDate,(char*)transData->terminalData.transactionDate);
	serverTransData[transData->transactionSequenceNumber].transState=transData->transState;
	serverTransData[transData->transactionSequenceNumber].transactionSequenceNumber=transData->transactionSequenceNumber+1;
	accountRefrence->balance=(accountRefrence->balance)-(transData->terminalData.transAmount);
	transData->transactionSequenceNumber++;
	transCount++;
	return SERVER_OK;
}
else{

	copystring((char*)serverTransData[transData->transactionSequenceNumber].cardHolderData.cardExpirationDate,(char*)transData->cardHolderData.cardExpirationDate);
	copystring((char*)serverTransData[transData->transactionSequenceNumber].cardHolderData.cardHolderName,(char*)transData->cardHolderData.cardHolderName);
	copystring((char*)serverTransData[transData->transactionSequenceNumber].cardHolderData.primaryAccountNumber,(char*)transData->cardHolderData.primaryAccountNumber);
	serverTransData[transData->transactionSequenceNumber].terminalData.maxTransAmount=transData->terminalData.maxTransAmount;
	serverTransData[transData->transactionSequenceNumber].terminalData.transAmount=transData->terminalData.transAmount;
	copystring((char*)serverTransData[transData->transactionSequenceNumber].terminalData.transactionDate,(char*)transData->terminalData.transactionDate);
	serverTransData[transData->transactionSequenceNumber].transState=transData->transState;
	serverTransData[transData->transactionSequenceNumber].transactionSequenceNumber=transData->transactionSequenceNumber+1;
	transData->transactionSequenceNumber++;
	transCount++;
return SERVER_OK;
}
}

EN_transStat_t recieveTransactionData(ST_transaction_t *transData){

	if(isValidAccount(transData->cardHolderData,accountRefrence)==ACCOUNT_NOT_FOUND){
		transData->transState = FRAUD_CARD;
		return FRAUD_CARD;
	}
	if(isBlockedAccount(accountRefrence)==BLOCKED_ACCOUNT){
			transData->transState = DECLINED_STOLEN_CARD;
			return DECLINED_STOLEN_CARD;
		}
	if(isAmountAvailable(transData->terminalData,accountRefrence)==LOW_BALANCE){
			transData->transState = DECLINED_INSUFFECIENT_FUND;
			return DECLINED_INSUFFECIENT_FUND;
		}

	else {
	transData->transState=APPROVED;
	return APPROVED;
	}

}




EN_serverError_t isAmountAvailable(ST_terminalData_t termData, ST_accountsDB_t *accountRefrence){
	if(termData.transAmount > accountRefrence->balance){
		return  LOW_BALANCE;
	}
	else{

		return SERVER_OK;
	}
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
	if(accountRefrence->state==BLOCKED){
		return BLOCKED_ACCOUNT;
	}
	else{
		return SERVER_OK;
	}

}

EN_serverError_t isValidAccount(ST_cardData_t cardData, ST_accountsDB_t *accountRefrence){
	ST_accountsDB_t *ptr;
	bool foundFlag = false;
	for(int i=0;i<sizeof(accountsDB)/sizeof(accountsDB[0]);i++){
		ptr=&accountsDB[i];
		if(atoi((char*)ptr->primaryAccountNumber)== atoi ((char*)cardData.primaryAccountNumber)){
			accountRefrence->balance=accountsDB[i].balance;
			copystring((char*)accountRefrence->primaryAccountNumber,(char*)accountsDB[i].primaryAccountNumber);
			accountRefrence->state=accountsDB[i].state;
			foundFlag=true;
			break;
		}
		}
	if(foundFlag!=true){
	return 	ACCOUNT_NOT_FOUND;
	accountRefrence=NULL;
	}
	else{
		return 	SERVER_OK;
	}
	}

void recieveTransactionDataTest(void){


	 printf("tester Name: ahmed bahaa  \n");

	    		 	printf("recieveTransactionDataTest\n\n");
	    		 	for(int i=0;i<sizeof(inputPAN)/sizeof(inputPAN[0]);i++){
	    		 	printf("Test Case %d\n",i+1);
	    		 	copystring((char*)transData->cardHolderData.primaryAccountNumber,inputPAN[i]);
	    		 	transData->terminalData.transAmount= inputTransAmount[i];
	    		 	printf("input PAN: %s \n",transData->cardHolderData.primaryAccountNumber);
	    		 	printf("input transaction Amount: %f \n",transData->terminalData.transAmount);
	    		 	char expected_result[25];
	    		 	printf("Expected Result:   ");
	    		 	fflush(stdout);
	    		 	fgets(expected_result,24,stdin);
	    		 	EN_transStat_t serverTransResult=recieveTransactionData(transData);
	    		 	if(serverTransResult==FRAUD_CARD) {
	    		 	printf("actual results: server declines transaction : FRAUD CARD\n\n ");
	    		 	}
	    		 	if(serverTransResult==DECLINED_STOLEN_CARD){
	    		 	printf("actual results: server declines transaction : Stolen Card\n\n ");
	    		 	}
	    		 	if(serverTransResult==DECLINED_INSUFFECIENT_FUND){
	    		    printf("actual results: server declines transaction : Insufficient Fund\n\n ");
	    		 	}
	    		 	if(serverTransResult==APPROVED){
	    		 		 printf("actual results: server approves transaction \n\n");
	    		 		    }


	     }
}


void isValidAccountTest(void){

	 printf("tester Name: ahmed bahaa  \n");

		 	printf("function name: isValidAccountTest\n\n");
		 	for(int i=0;i<2;i++){
		 	printf("Test Case %d\n",i+1);
		 	printf("input data : %s \n",inputPAN[i]);
		 	char expected_result[25];
		 	printf("Expected Result:   ");
		 	fflush(stdout);
		 	fgets(expected_result,24,stdin);

            copystring((char*)transData->cardHolderData.primaryAccountNumber,inputPAN[i]);
		 	if(isValidAccount(transData->cardHolderData,accountRefrence)==SERVER_OK){
		 	printf("actual results: Valid Account \n\n");
		 	}
		 	else {
		 	printf("actual results: account not found, FRAUD CARD\n\n ");
		 	}
		 	}
		 	}

void isBlockedAccountTest(void){

	 printf("tester Name: ahmed bahaa  \n");

		 	printf("function name: isBlockedAccountTest\n\n");
		 	for(int i=0;i<(sizeof( testBlockedData)/sizeof( testBlockedData[0]));i++){
		 	printf("Test Case %d\n",i+1);
		 	testBlockedData[i]== RUNNING ? printf("input data: RUNNING\n"): printf("input data: BLOCKED\n");
		 	char expected_result[25];
		 	printf("Expected Result:   ");
		 	fflush(stdout);
		 	fgets(expected_result,24,stdin);
		 	accountRefrence->state= testBlockedData[i];
		 	if(isBlockedAccount(accountRefrence)==SERVER_OK){
		 	printf("actual results: Valid Account \n\n");
		 	}
		 	else {
		 	printf("actual results: account Blocked\n\n ");
		 	}
		 	}
		 	}

void isAmountAvailableTest(void){

	printf("tester Name: ahmed bahaa  \n");

			 	printf("function name: isAmountAvailableTest\n\n");
			 	for(int i=0;i<(sizeof( inputTransAmount)/sizeof(inputTransAmount[0]));i++){
			 	printf("Test Case %d\n",i+1);
			 	transData->terminalData.transAmount = inputTransAmount[i];
			 	accountRefrence->balance = accountsDB[0].balance;
				printf("input data : %f \n",transData->terminalData.transAmount);
				printf("account Balance : %f\n",accountRefrence->balance);
			 	char expected_result[25];
			 	printf("Expected Result:   ");
			 	fflush(stdout);
			 	fgets(expected_result,24,stdin);
			 	if(isAmountAvailable(transData->terminalData,accountRefrence)==SERVER_OK){
			 	printf("actual results: Valid Transaction \n\n");
			 	}
			 	else {
			 	printf("actual results: insufficient Fund\n\n ");
			 	}
			 	}

}

void saveTransactionTest(void){
	transData->transactionSequenceNumber=0;
	printf("tester Name: ahmed bahaa  \n");
				 	printf("function name: saveTransactionTest\n\n");
				 	for(int i=0;i<sizeof(inputTransAmount)/sizeof(inputTransAmount);i++){
				 	printf("Test Case %d\n",i+1);
				 	transData->terminalData.transAmount = inputTransAmount[i];
				 	transData->terminalData.maxTransAmount=5000;
				 	copystring((char*)transData->terminalData.transactionDate,"14/12/2022");
				 	copystring((char*)transData->cardHolderData.cardHolderName,"ahmedbahaaalkomy");
				 	copystring((char*)transData->cardHolderData.primaryAccountNumber,"8989374615436851");
				 	copystring((char*)transData->cardHolderData.cardExpirationDate,"08/25");
				 	transData->transState=inputTransAmount[i];
				 	char expected_result[25];
				 	printf("Expected Result:   ");
				 	fflush(stdout);
				 	fgets(expected_result,24,stdin);
				 	if(saveTransaction(transData)==SERVER_OK){
				 	printf("actual results: saving done \n\n");
				 	}
				 	else {
				 	printf("actual results: saving failed \n\n ");
				 	}
				 	}

	}




/*int main(){
	transData= (ST_transaction_t*)malloc(sizeof(ST_transaction_t));
	transData->transactionSequenceNumber=0;
	accountRefrence= (ST_accountsDB_t*)malloc(sizeof(ST_accountsDB_t));
	//isValidAccountTest();
	//isBlockedAccountTest();
	//isAmountAvailableTest();
	saveTransactionTest();
	//recieveTransactionDataTest();
	free(transData);

}*/

/*
 * card.c
 *
 *  Created on: Dec 6, 2022
 *      Author: ahmed bahaa alkomy
 */

#include <stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include"card.h"

ST_cardData_t *cardData=NULL;
char cardHolderName[][50]= {"ahmedbahaaalkomy","ahmed bahaa ibrahim al","ahmedbahaaibrahimalkomy","ahmedbahaaibrahimabdelrazik","","ah#e3bahaa+brahimalko3y"};
char exp_Date[][10] = {"08/21","6/15","13/20","00/25","114/19","22/22","","*8/2%"};
char cardPan[][100]= {"2736459801237654","1298764530987","12736458908764563789","1283746590987564536754","","a736+598@1237m541"};


EN_cardError_t getCardHolderName(ST_cardData_t *cardData){

 if(strlen((char*)cardData->cardHolderName)<20 || strlen((char*)cardData->cardHolderName)>24||strlen((char*)cardData->cardHolderName)==0){
  return WRONG_NAME;
 }
 for(int i=0;cardData->cardHolderName[i]!='\0';i++){
  if(!((cardData->cardHolderName[i]<=122 && cardData->cardHolderName[i]>=65)||cardData->cardHolderName[i]==32)){
	return WRONG_NAME;
  }
 }
return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
	char expire_month[3];
	for(int j= 0;j<2;j++){
	expire_month[j]=cardData->cardExpirationDate[j];
		}
	if(strlen((char*)cardData->cardExpirationDate)!=5 || cardData->cardExpirationDate[2]!='/' || atoi(expire_month)>12 || atoi(expire_month)==0){
	return WRONG_EXP_DATE;
	}
	if(isdigit(cardData->cardExpirationDate[0])==0||isdigit(cardData->cardExpirationDate[1])==0||isdigit(cardData->cardExpirationDate[3])==0||isdigit(cardData->cardExpirationDate[4])==0){
	return WRONG_EXP_DATE;
	}
	else{
	return CARD_OK;
	}
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){

	if(strlen((char*)cardData->primaryAccountNumber)<16 || strlen((char*)cardData->primaryAccountNumber)>19 || strlen((char*)cardData->primaryAccountNumber)==0){
		return WRONG_PAN;
		}

	for(int i=0;cardData->primaryAccountNumber[i]!='\0';i++){
		if(!((cardData->primaryAccountNumber[i]<=57 && cardData->primaryAccountNumber[i]>=48)||cardData->primaryAccountNumber[i]==32)){
			return WRONG_PAN;
		}
}
	return CARD_OK;
}

void getCardHolderNameTest(void){
	printf("tester Name: ahmed bahaa  \n");
	printf("function name: getCardHolderName\n\n");
	for(int i=0;i<sizeof(cardHolderName)/sizeof(cardHolderName[0]);i++){
	printf("Test Case %d\n",i+1);
	int j=0;
	while(cardHolderName[i][j]!='\0'){
		cardData->cardHolderName[j]= cardHolderName[i][j];
		j++;
		}
	cardData->cardHolderName[j]='\0';
	printf("input data : %s\n",(char*)cardData->cardHolderName);
	printf("input name length=  %d\n",strlen((char*)cardData->cardHolderName));
	char expected_result[25];
	printf("Expected Result:   ");
	fflush(stdout);
	fgets(expected_result,24,stdin);
	if(getCardHolderName(cardData)==0){
	printf("actual results: Card OK \n\n");
	}
	else {
	printf("actual results: Wrong Name\n\n ");
	}
	}
	}

void getCardExpiryDateTest(void){
	printf("tester Name: ahmed bahaa  \n");
	printf("function name: getExpirationDateTest\n\n");
	for(int i=0;i<sizeof(exp_Date)/sizeof(exp_Date[0]);i++){
	printf("Test Case %d\n",i+1);
	int j=0;
	while(exp_Date[i][j]!='\0'){
		cardData->cardExpirationDate[j]= exp_Date[i][j];
		j++;
	}
	cardData->cardExpirationDate[j]='\0';
	printf("input data : %s \n",cardData->cardExpirationDate);
	printf("input name length=  %d\n",strlen((char*)cardData->cardExpirationDate));
	char expected_result[25];
	printf("Expected Result:   ");
	fflush(stdout);
	fgets(expected_result,24,stdin);
	if(getCardExpiryDate(cardData)==0){
	printf("actual results: Card OK \n\n");
	}
	else {
	printf("actual results: WRONG_EXP_DATE\n\n ");

	}
	}
	}
void getCardPANTest (void){
	printf("tester Name: ahmed bahaa  \n");
	printf("function name: getCardPanTest\n\n");
	for(int i=0;i<sizeof(cardPan)/sizeof(cardPan[0]);i++){
	printf("Test Case %d\n",i+1);
	int j=0;
	while(cardPan[i][j]!='\0'){
	cardData->primaryAccountNumber[j]= cardPan[i][j];
	j++;
	}
	cardData->primaryAccountNumber[j]='\0';
	printf("input data : %s \n",cardData->primaryAccountNumber);
	printf("input name length=  %d\n",strlen((char*)cardData->primaryAccountNumber));
	char expected_result[25];
	printf("Expected Result:   ");
	fflush(stdout);
	fgets(expected_result,24,stdin);
	if( getCardPAN(cardData)==0){
	 printf("actual results: Card OK \n\n");
		}
	else {
	printf("actual results: WRONG_PAN\n\n ");
		}
		}
		}

/*int main()
{
cardData= (ST_cardData_t*)malloc(sizeof(ST_cardData_t));
//getCardHolderNameTest();
//getCardExpiryDateTest();
getCardPANTest();
free(cardData);
}*/


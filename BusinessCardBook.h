//BusinessCardBook.h
#ifndef _BUSINESSCARDBOOK_H
#define _BUSINESSCARDBOOK_H
#include"LinkedList.h"

typedef signed long int Long;

typedef struct _personal {
	char name[11];
	char position[32];
	char telephoneNumber[12];
	char emailAddress[64];
}Personal;

typedef struct _company {
	char name[64];
	char address[64];
	char telephoneNumber[12];
	char faxNumber[12];
	char url[64];
}Company;

typedef struct _businessCard {
	Personal personal;
	Company company;
}BusinessCard;

typedef struct _businessCardBook {
	LinkedList businessCards;
	Long length;
	BusinessCard *current;
}BusinessCardBook;

void BusinessCardBook_Create(BusinessCardBook *businessCardBook);
Long Load(BusinessCardBook *businessCardBook);
BusinessCard* TakeIn(BusinessCardBook *businessCardBook, BusinessCard businessCard);
BusinessCard TakeOut(BusinessCardBook *businessCardBook, BusinessCard *index);
void Find(BusinessCardBook *businessCardBook, char(*name), BusinessCard* *(*indexes), Long *count);
BusinessCard* BusinessCardBook_First(BusinessCardBook *businessCardBook);
BusinessCard* BusinessCardBook_Previous(BusinessCardBook *businessCardBook);
BusinessCard* BusinessCardBook_Next(BusinessCardBook *businessCardBook);
BusinessCard* BusinessCardBook_Last(BusinessCardBook *businessCardBook);
BusinessCard* FindByCompanyName(BusinessCardBook *businessCardBook, char(*companyName));
BusinessCard* BusinessCardBook_Move(BusinessCardBook *businessCardBook, BusinessCard *index);
Long Save(BusinessCardBook *businessCardBook);
void BusinessCardBook_Destroy(BusinessCardBook *businessCardBook);

int CompareNames(void *one, void *other);
int CompareCompanyNames(void *one, void *other);
int ComparePointers(void *one, void *other);

#endif _BUSINESSCARDBOOK_H
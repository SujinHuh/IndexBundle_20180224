//BusinessCardBook.c
#include"BusinessCardBook.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>


int main(int argc, char *argv[]) {
	BusinessCardBook businessCardBook;
	BusinessCard *index;
	BusinessCard businessCard = { 0, };
	BusinessCard *previous = NULL;
	BusinessCard* (*indexes);
	Long count;
	Long i = 0;

	//1. ����ö�� �����.
	BusinessCardBook_Create(&businessCardBook);
	//2. ��ũ���Ͽ��� ���Ե��� �ҷ��´�.
	Load(&businessCardBook);
	//3. ó����ġ�� �̵��Ѵ�.
	index = BusinessCardBook_First(&businessCardBook);
#if 0
	while (index != previous) {
		printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress,
			index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
		previous = index;
		index = BusinessCardBook_Next(&businessCardBook);
	}
#endif
	//4. "ȫ�浿", "����", "010", "hong@", "LG", "����", "02", "02-2", "LG.com", �� �Է��Ѵ�. .
	strcpy(businessCard.personal.name, "ȫ�浿");
	strcpy(businessCard.personal.position, "����");
	strcpy(businessCard.personal.telephoneNumber, "010");
	strcpy(businessCard.personal.emailAddress, "hong@");
	strcpy(businessCard.company.name, "LG");
	strcpy(businessCard.company.address, "����");
	strcpy(businessCard.company.telephoneNumber, "02");
	strcpy(businessCard.company.faxNumber, "02-2");
	strcpy(businessCard.company.url, "LG.com");
	//5. ������ �����.
	index = TakeIn(&businessCardBook, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	
	//4. "�����", "����", "011", "kim@", "KT", "����", "03", "03-3", "KT.com", �� �Է��Ѵ�. .
	strcpy(businessCard.personal.name, "�����");
	strcpy(businessCard.personal.position, "����");
	strcpy(businessCard.personal.telephoneNumber, "011");
	strcpy(businessCard.personal.emailAddress, "kim@");
	strcpy(businessCard.company.name, "KT");
	strcpy(businessCard.company.address, "����");
	strcpy(businessCard.company.telephoneNumber, "03");
	strcpy(businessCard.company.faxNumber, "03-3");
	strcpy(businessCard.company.url, "KT.com");
	//5. ������ �����.
	index = TakeIn(&businessCardBook, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	
	//4. "ȫ�浿", "����", "012", "hong@", "LG", "����", "02", "02-2", "LG.com", �� �Է��Ѵ�. .
	strcpy(businessCard.personal.name, "ȫ�浿");
	strcpy(businessCard.personal.position, "����");
	strcpy(businessCard.personal.telephoneNumber, "012");
	strcpy(businessCard.personal.emailAddress, "dong@");
	strcpy(businessCard.company.name, "Google");
	strcpy(businessCard.company.address, "State");
	strcpy(businessCard.company.telephoneNumber, "05");
	strcpy(businessCard.company.faxNumber, "05-5");
	strcpy(businessCard.company.url, "google.com");
	//5. ������ �����.
	index = TakeIn(&businessCardBook, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);

	//6. "ȫ�浿"�� ã�´�.
	Find(&businessCardBook, "ȫ�浿", &indexes, &count);
	while (i < count) {
		printf("%s %s %s %s %s %s %s %s %s\n", indexes[i]->personal.name, indexes[i]->personal.position, indexes[i]->personal.telephoneNumber, indexes[i]->personal.emailAddress,
			indexes[i]->company.name, indexes[i]->company.address, indexes[i]->company.telephoneNumber, indexes[i]->company.faxNumber, indexes[i]->company.url);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
		indexes = NULL;
	}

	//7. ��������ġ�� �̵��Ѵ�.
	index = BusinessCardBook_Last(&businessCardBook);
	printf("%s %s %s %s %s %s %s %s %s\n", index->personal.name, index->personal.position, index->personal.telephoneNumber, index->personal.emailAddress,
		index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url);
	//8. ������ġ�� �̵��Ѵ�.
	index = BusinessCardBook_Previous(&businessCardBook);
	//9. ������ ������.
	businessCard = TakeOut(&businessCardBook, index);
	printf("%s %s %s %s %s %s %s %s %s\n", businessCard.personal.name, businessCard.personal.position, businessCard.personal.telephoneNumber, businessCard.personal.emailAddress,
		businessCard.company.name, businessCard.company.address, businessCard.company.telephoneNumber, businessCard.company.faxNumber, businessCard.company.url);


	return 0;
}


void BusinessCardBook_Create(BusinessCardBook *businessCardBook) {

	Create(&businessCardBook->businessCards);
	businessCardBook->length = 0;
	businessCardBook->current = NULL;
}

Long Load(BusinessCardBook *businessCardBook) {
	Long companyNumber;
	BusinessCard businessCard;
	Node *node;
	Long i;

	int flagPersonals;
	int flagCompanies;
	FILE *filePersonals;
	FILE *fileCompanies;

	filePersonals = fopen("Personals.dat", "rb");
	fileCompanies = fopen("Companies.dat", "rb");
	if (filePersonals != NULL && fileCompanies != NULL) {
		flagPersonals = fread(&companyNumber, sizeof(Long), 1, filePersonals);
		flagPersonals = fread(&businessCard.personal, sizeof(Personal), 1, filePersonals);
		while (!feof(filePersonals) && flagPersonals != 0) {
			i = 1;
			fseek(fileCompanies, 0L, SEEK_SET);
			flagCompanies = fread(&businessCard.company, sizeof(Company), 1, fileCompanies);
			while (!feof(fileCompanies) && flagCompanies != 0 && i < companyNumber) {
				i++;
				flagCompanies = fread(&businessCard.company, sizeof(Company), 1, fileCompanies);
			}
			node = AppendFromTail(&businessCardBook->businessCards, &businessCard, sizeof(BusinessCard));
			businessCardBook->current = (BusinessCard*)(node + 1);
			businessCardBook->length++;
			flagPersonals = fread(&companyNumber, sizeof(Long), 1, filePersonals);
			flagPersonals = fread(&businessCard.personal, sizeof(Personal), 1, filePersonals);
		}
		fclose(fileCompanies);
		fclose(filePersonals);
	}
	return businessCardBook->length;
}

BusinessCard* TakeIn(BusinessCardBook *businessCardBook, BusinessCard businessCard) {
	Node *node;

	node = AppendFromTail(&businessCardBook->businessCards, &businessCard, sizeof(BusinessCard));
	businessCardBook->current = (BusinessCard*)(node + 1);
	businessCardBook->length++;

	return businessCardBook->current;
}

BusinessCard TakeOut(BusinessCardBook *businessCardBook, BusinessCard *index) {
	BusinessCard businessCard;
	Node *node;

	node = LinearSearchUnique(&businessCardBook->businessCards, index, ComparePointers);
	businessCardBook->current = (BusinessCard*)(node + 1);
	GetAt(&businessCardBook->businessCards, node, &businessCard, sizeof(BusinessCard));
	node = Delete(&businessCardBook->businessCards, node);
	businessCardBook->current = (BusinessCard*)businessCardBook->businessCards.current + 1;
	businessCardBook->length--;

	return businessCard;
}

int ComparePointers(void *one, void *other) {
	int ret = 1;

	if (one == other) {
		ret = 0;
	}
	return ret;
}

void Find(BusinessCardBook *businessCardBook, char(*name), BusinessCard* *(*indexes), Long *count) {
	Node* (*nodes);
	Long i = 0;

	LinearSearchDuplicate(&businessCardBook->businessCards, name, &nodes, count, CompareNames);
	*indexes = (BusinessCard*(*))calloc(businessCardBook->length, sizeof(BusinessCard*));
	while (i < *count) {
		(*indexes)[i] = (BusinessCard*)(nodes[i] + 1);
		i++;
	}
	if (nodes != NULL) {
		free(nodes);
		nodes = NULL;
	}
}

int CompareNames(void *one, void *other) {
	BusinessCard *one_ = (BusinessCard*)one;
	char(*other_) = (char(*))other;
	int ret;

	ret = strcmp(one_->personal.name, other);

	return ret;
}

BusinessCard* BusinessCardBook_First(BusinessCardBook *businessCardBook) {
	Node *node;

	node = First(&businessCardBook->businessCards);
	businessCardBook->current = (BusinessCard*)node + 1;

	return businessCardBook->current;
}

BusinessCard* BusinessCardBook_Previous(BusinessCardBook *businessCardBook) {
	Node *node;

	node = Previous(&businessCardBook->businessCards);
	businessCardBook->current = (BusinessCard*)(node + 1);

	return businessCardBook->current;
}

BusinessCard* BusinessCardBook_Next(BusinessCardBook *businessCardBook) {
	Node *node;

	node = Next(&businessCardBook->businessCards);
	businessCardBook->current = (BusinessCard*)(node + 1);

	return businessCardBook->current;
}

BusinessCard* BusinessCardBook_Last(BusinessCardBook *businessCardBook) {
	Node *node;

	node = Last(&businessCardBook->businessCards);
	businessCardBook->current = (BusinessCard*)(node + 1);

	return businessCardBook->current;
}

BusinessCard* FindByCompanyName(BusinessCardBook *businessCardBook, char(*companyName)) {
	Node *node;

	node = LinearSearchUnique(&businessCardBook->businessCards, companyName, CompareCompanyNames);
	if (node != NULL) {
		businessCardBook->current = (BusinessCard*)(node + 1);
	}
	else {
		businessCardBook->current = NULL;
	}
	return businessCardBook->current;
}

int CompareCompanyNames(void *one, void *other) {
	BusinessCard *one_ = (BusinessCard*)one;
	char(*other_) = (char(*))other;

	return strcmp(one_->company.name, other);
}

BusinessCard* BusinessCardBook_Move(BusinessCardBook *businessCardBook, BusinessCard *index) {
	Node *node;

	node = LinearSearchUnique(&businessCardBook->businessCards, index, ComparePointers);
	node = Move(&businessCardBook->businessCards, node);
	businessCardBook->current = (BusinessCard*)(node + 1);

	return businessCardBook->current;
}

Long Save(BusinessCardBook *businessCardBook) {
	Node *node;
	BusinessCard businessCard;
	Long companyNumber;
	Node *previous = NULL;
	Company company;

	int flag;
	FILE *filePersonals;
	FILE *fileCompanies;
	filePersonals = fopen("Personals.dat", "wb");
	fileCompanies = fopen("Companies.dat", "wb+");
	if (filePersonals != NULL && fileCompanies != NULL){
		node = First(&businessCardBook->businessCards);
		businessCardBook->current = (BusinessCard*)(node + 1);
		GetAt(&businessCardBook->businessCards, node, &businessCard, sizeof(BusinessCard));
		while (node != previous) {
			companyNumber = 1;
			fseek(fileCompanies, 0L, SEEK_SET);
			flag = fread(&company, sizeof(Company), 1, fileCompanies);
			while (!feof(fileCompanies) && flag != 0 && strcmp(businessCard.company.name, company.name) != 0) {
				companyNumber++;
				flag = fread(&company, sizeof(Company), 1, fileCompanies);
			}
			if (flag == 0) {
				fwrite(&businessCard.company, sizeof(Company), 1, fileCompanies);
			}
			fwrite(&companyNumber, sizeof(Long), 1, filePersonals);
			fwrite(&businessCard.personal, sizeof(Personal), 1, filePersonals);
			node = Next(&businessCardBook->businessCards);
			businessCardBook->current = (BusinessCard*)(node + 1);
			GetAt(&businessCardBook->businessCards, node, &businessCard, sizeof(BusinessCard));
		}
		fclose(fileCompanies);
		fclose(filePersonals);
	}
	return businessCardBook->length;
}

void BusinessCardBook_Destroy(BusinessCardBook *businessCardBook) {

	Destroy(&businessCardBook->businessCards);
}
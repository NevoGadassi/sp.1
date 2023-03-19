#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
	int ArrSize;
	PElement* objarr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;

}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy_Func, DEL_FUNC del_Func,PRINT_FUNC print_Func) 
{
	PAdptArray newADPT = (PAdptArray)malloc(sizeof(AdptArray));
	if (newADPT == NULL){
		return NULL;
    }
    newADPT->ArrSize = 0;
	newADPT->objarr = NULL;
	newADPT->delFunc = del_Func;
	newADPT->copyFunc = copy_Func;
    newADPT->printFunc = print_Func;

	return newADPT;
}
void DeleteAdptArray(PAdptArray newADPT)
{
	if (newADPT == NULL)
		return;
	for(int i = 0; i < newADPT->ArrSize; ++i)
	{   
        if((newADPT->objarr)[i]!=NULL)
		newADPT->delFunc((newADPT->objarr)[i]);
	}
	free(newADPT->objarr);
	free(newADPT);

}
Result SetAdptArrayAt(PAdptArray newADPT, int index, PElement obj)
{
	PElement* newpArr;
	if (newADPT == NULL)
		return FAIL;

    int size= newADPT->ArrSize;
	if (index >= size)
	{
		
		if ((newpArr = (PElement*)calloc((index + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpArr, newADPT->objarr, (newADPT->ArrSize) * sizeof(PElement));
        
		free(newADPT->objarr);
		newADPT->objarr = newpArr;
	}
    if((newADPT->objarr)[index]!=NULL){
        newADPT->delFunc((newADPT->objarr)[index]);
    }
	(newADPT->objarr)[index] = newADPT->copyFunc(obj);

	newADPT->ArrSize = (index >= newADPT->ArrSize) ? (index + 1) : newADPT->ArrSize;
	return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray newADPT, int index)
{
    if((newADPT->objarr)[index]==NULL)
        return NULL;
    PElement thisobj =(newADPT->objarr)[index];
    return newADPT->copyFunc(thisobj);

}


int GetAdptArraySize(PAdptArray newADPT){

    return newADPT->ArrSize;
}


void PrintDB(PAdptArray newADPT){
for(int i = 0; i < newADPT->ArrSize; ++i)
	{
        if((newADPT->objarr)[i]!=NULL)
		newADPT->printFunc((newADPT->objarr)[i]);
    }
}

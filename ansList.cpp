#include "ansList.h"
PTRA alloc_AList(int n){
	if(n<=0) return NULL;
	PTRA answers = new answer[n];
	return answers;
}
void free_AList(PTRA &answers){
    if(answers!=NULL) delete[] answers;	
}
int load_test(std::ifstream& ifile, test& testif){
	ifile.read((char*)&testif.nMin,sizeof(testif.nMin));
	ifile.read((char*)&testif.n,sizeof(testif.n));
	testif.answers = alloc_AList(testif.n);
	if(testif.answers == NULL) return 0;         
	ifile.read((char*)testif.answers,testif.n*sizeof(*(testif.answers)));
	return 1;
}   
void save_test(std::ofstream& ofile, const test &testif){
	ofile.write((const char*)&testif.nMin,sizeof(testif.nMin));
	ofile.write((const char*)&testif.n,sizeof(testif.n));
	ofile.write((const char*)testif.answers,testif.n*sizeof(*(testif.answers)));
}

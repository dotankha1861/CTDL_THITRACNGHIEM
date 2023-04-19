#include "classList.h"
void set_classInfor(classInfor &classif, char* classID, char* className){
	strcpy(classif.MALOP, classID);
	strcpy(classif.TENLOP, className);
}
PTRC new_class( Class& CLS){
	PTRC newClass = new Class;
	if(newClass == NULL) return NULL; 
	*newClass = CLS;
	return newClass;
}
bool CList_empty(classList& CList){
	return CList.nClass == 0;
}
bool CList_full(classList& CList){
	return CList.nClass == MAX_CLASS-1;
}
void init_CList(classList &CList){
	CList.nClass = 0;
}
PTRS search_student_all_class_MSSV(classList &CList,char* stuID){
	PTRS SNode;
	for(int i=0; i<CList.nClass;i++){
		SNode = search_SList_MSSV(CList.classes[i]->SFirst,stuID);
		if( SNode != NULL) return SNode;
	}
	return NULL;
}
int lop_da_co_sinh_vien_thi(PTRC CNode){
	if(CNode==NULL) return -1; 
	for(PTRS SNode = CNode->SFirst; SNode!=NULL; SNode = SNode->Next)
	    if(sinh_vien_da_thi(SNode)==1) return 1;
	return 0;
}
int insert_last_CList(classList &CList, Class &CLS){
	if(CList_full(CList)) return 0;
	PTRC newClass = new_class(CLS);
	CList.classes[CList.nClass++] = newClass;
	return 1;
}
int insert_CList_idx(classList &CList, Class &CLS, int idx){
	if(CList_full(CList)||idx<0||idx>CList.nClass) return 0;
	PTRC newClass = new_class(CLS);
	for(int i=CList.nClass; i > idx; i--) CList.classes[i] = CList.classes[i-1];
	CList.nClass++;
	CList.classes[idx]= newClass;
	return 1;
}
int insert_CList_CTT(classList &CList, Class &CLS){
	if(CList_full(CList)) return 0;
	char buff1[MAX_MALOP+MAX_TENLOP+1], buff2[MAX_MALOP+MAX_TENLOP+1];
	int i;
	for(i=0; i< CList.nClass; i++)
		if(stricmp(CLS.classi4.MALOP,CList.classes[i]->classi4.MALOP)<0) break;
    insert_CList_idx(CList, CLS, i);
    return 1;
}
void free_class(PTRC &CLS){
	if(CLS!=NULL){
		free_SList(CLS->SFirst);
		delete CLS;
	}
}
int search_CList_ML(classList& CList,char* classID){
	for(int i=0;i<CList.nClass;i++){
		if(stricmp(CList.classes[i]->classi4.MALOP,classID)==0) return i;
	}
	return -1;
}
void delete_CList_idx(classList &CList, int idx){
	if(CList_empty(CList)||idx<0||idx>=CList.nClass) return ;
	free_class(CList.classes[idx]);
	for(int i=idx; i <CList.nClass-1; i++) CList.classes[i] = CList.classes[i+1];
    CList.nClass--;
}
int delete_CList_MALOP(classList &CList, char* classID){
	if(CList_empty(CList)) return 0;
	for(int i=0; i<CList.nClass; i++)
	    if(stricmp(CList.classes[i]->classi4.MALOP,classID)==0){
	    	delete_CList_idx(CList,i);
	    	return 1;
		}
	return 0;	    
}
void load_CList(std::ifstream &ifile, classList& CList){
	int nClass;
	ifile.read((char*)&nClass, sizeof(nClass));
	Class CLS;
	for(int i=0; i<nClass; i++){
    	ifile.read((char*)&CLS.classi4, sizeof(CLS.classi4));
    	init_SList(CLS.SFirst);
    	load_SList(ifile, CLS.SFirst);
    	insert_last_CList(CList,CLS);
    }
}
void save_CList(std::ofstream &ofile, classList& CList){
	ofile.write((const char*)&CList.nClass, sizeof(CList.nClass));
	for(int i=0; i<CList.nClass; i++){
    	ofile.write((const char*)&CList.classes[i]->classi4, sizeof(classInfor));
    	save_SList(ofile,CList.classes[i]->SFirst);
    }
}
void free_CList(classList &CList){
	for(int i=0; i<CList.nClass; i++) free_class(CList.classes[i]);
}


#include "stuList.h"
void set_stuInfor(stuInfor& stuif,char* stuID, char* LName, char* FName, char* sex, char* PWRD){
	strcpy(stuif.MASV,stuID);
	strcpy(stuif.HO,LName);
	strcpy(stuif.TEN,FName);
	strcpy(stuif.PHAI,sex);
	strcpy(stuif.password,PWRD);
}
bool SList_empty(PTRS SFirst){
	return SFirst==NULL;
}
void init_SList(PTRS &SFirst){
	SFirst = NULL;
}
PTRS get_student_idx(PTRS SFirst, int idx){
	for(int i=0 ; i<idx && SFirst != NULL; i++, SFirst = SFirst->Next);
	return SFirst; 
}
PTRS new_stu_node(stuInfor &stuif, PTRM MFirst){
	PTRS SNode = new stuNode;
	if(SNode == NULL) return NULL;
	SNode->stui4 = stuif; 
	SNode->MFirst = MFirst;
    return SNode;
}
PTRS search_SList_MSSV(PTRS SFirst,char* stuID){
	for(PTRS SNode = SFirst; SNode!=NULL; SNode = SNode->Next){
		if(stricmp(SNode->stui4.MASV,stuID)==0) return SNode;
	}
	return NULL;
}
void insert_first_SList(PTRS &SFirst, stuInfor &stuif, PTRM MFirst){
	PTRS SNode = new_stu_node(stuif, MFirst);
	SNode->Next= SFirst;
	SFirst = SNode;
}
void insert_afterAt_SList(PTRS atSNode, stuInfor &stuif, PTRM MFirst){
	if(atSNode==NULL) return; 
	PTRS SNode = new_stu_node(stuif, MFirst);
	SNode->Next= atSNode->Next;
	atSNode->Next = SNode;
}
void insert_last_SList(PTRS &SFirst, stuInfor &stuif, PTRM MFirst){
	if(SList_empty(SFirst)) insert_first_SList(SFirst,stuif,MFirst);
	else{
	    PTRS nodeRun = SFirst;
	    while(nodeRun->Next!=NULL) nodeRun = nodeRun->Next;
	    insert_afterAt_SList(nodeRun,stuif,MFirst);
    }
}
void TEN_HO_MASV(char* buff, stuInfor& stuif){
	strcpy(buff,stuif.TEN);
	strcat(buff,stuif.HO);
	strcat(buff,stuif.MASV);
}
void insert_SList_CTT(PTRS &SFirst, stuInfor &stuif, PTRM MFirst){
	char i4Is[MAX_TEN+MAX_HO+MAX_MASV+1],i4At[MAX_TEN+MAX_HO+MAX_MASV+1];
	PTRS at = SFirst, before;
	TEN_HO_MASV(i4Is,stuif);
	while(at!=NULL){
		TEN_HO_MASV(i4At,at->stui4);
		if(stricmp(i4Is,i4At)<0) break;
		before=at;
	    at=at->Next;
	}
    if(at==SFirst) insert_first_SList(SFirst,stuif,MFirst);
    else insert_afterAt_SList(before,stuif,MFirst);
}
void free_SNode(PTRS &SNode){
	if(SNode!=NULL){
		free_MList(SNode->MFirst);
		delete SNode;
	}
}
void delete_first_SList(PTRS &SFirst){
	if(SList_empty(SFirst)) return;
	PTRS SNode = SFirst;
	SFirst = SFirst->Next;
	free_SNode(SNode);
}
void delete_afterAt_SList(PTRS atSNode){
	if(atSNode==NULL||atSNode->Next==NULL) return;
	PTRS SNode = atSNode->Next;
	atSNode->Next=SNode->Next;
	free_SNode(SNode);
}
void delete_SList_MSSV(PTRS& SFirst,char* stuID){
	if(SList_empty(SFirst)) return;
	if(stricmp(SFirst->stui4.MASV,stuID)==0) delete_first_SList(SFirst);
	else{
	    for(PTRS SNode = SFirst; SNode->Next!=NULL; SNode=SNode->Next){
		    if(stricmp(SNode->Next->stui4.MASV,stuID)==0){
		        delete_afterAt_SList(SNode);
		        break;
	        }
        }
	}
}
bool check_password(PTRS SNode,char* PSW){
	if(SNode == NULL) return 0;
	if(stricmp(SNode->stui4.password,PSW)==0) return 1;
	return 0;
}
int sinh_vien_da_thi(PTRS SNode){
	if(SNode==NULL) return -1;
	if(SNode->MFirst!=NULL) return 1;
	return 0;
}
void free_SList(PTRS &SFirst){
	PTRS SNode;
	while(SFirst!=NULL){
		SNode = SFirst;
		SFirst = SFirst->Next;
		free_SNode(SNode);
	}
}
int nStuNode(PTRS SFirst){
	int nSNode = 0;
	while(SFirst!=NULL){
		nSNode++;
		SFirst=SFirst->Next;
	}
	return nSNode;
}
void MH_GM(char* str){
	if(str == NULL) return;
	while(*str != '\0'){
		*str = - *str -1; 
		str++;
	} 
}
void load_SList(std::ifstream &ifile, PTRS &SFirst){
	int nSNode;
	ifile.read((char*)&nSNode,sizeof(nSNode));
    stuInfor stuif;
	PTRM MFirst;
	for(int i=0; i<nSNode; i++){
		ifile.read((char*)&stuif,sizeof(stuif));
		MH_GM(stuif.password);
		init_MList(MFirst);
		load_MList(ifile,MFirst);
		insert_last_SList(SFirst,stuif,MFirst);
    }
}
void save_SList(std::ofstream &ofile, PTRS SFirst){
	stuInfor buff;
	int nSNode = nStuNode(SFirst);
	ofile.write((const char*)&nSNode,sizeof(nSNode));
	for(PTRS SNode = SFirst; SNode!=NULL;SNode=SNode->Next){
		buff = SNode->stui4; 
		MH_GM(buff.password);
		ofile.write((const char*)&buff,sizeof(buff));
		save_MList(ofile, SNode->MFirst);
	}
}


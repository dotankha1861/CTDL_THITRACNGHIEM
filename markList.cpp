#include "markList.h"
void init_MList(PTRM &MFirst){
	MFirst = NULL;
}
void set_markInfor(markInfor& markif, char* subjID, float mark){
	strcpy(markif.Mamh, subjID);
	markif.Diem = mark;
}
bool MList_empty(PTRM MFirst){
	return MFirst==NULL;
}
PTRM new_mark_node( markInfor &markif, test &testif){
	PTRM MNode = new markNode;
	if(MNode==NULL) return NULL;
	MNode->marki4 = markif;
	MNode->testi4 = testif;
    return MNode;
}
PTRM get_mark_idx(PTRM MFirst, int idx){
	for(int i=0;i<idx && MFirst!=NULL;i++,MFirst=MFirst->Next);
	return MFirst; // SFirst = NULL if idx<0 ||idx >nStu CO VAN DE!!!!!
}
void insert_first_MList(PTRM &MFirst, markInfor &markif, test& testif){
	PTRM MNode = new_mark_node(markif,testif);
	MNode->Next= MFirst;
	MFirst = MNode;
}
void insert_afterAt_MList(PTRM atMNode, markInfor &markif,test& testif){
	if(atMNode==NULL) return; 
	PTRM MNode = new_mark_node(markif,testif);
	MNode->Next= atMNode->Next;
	atMNode->Next = MNode;
}
void insert_last_MList(PTRM &MFirst, markInfor &markif,test& testif){
	if(MList_empty(MFirst)) insert_first_MList(MFirst,markif,testif);
	else{
	    PTRM nodeRun = MFirst;
	    while(nodeRun->Next!=NULL) nodeRun = nodeRun->Next;
	    insert_afterAt_MList(nodeRun,markif,testif);
    }
}
void free_MNode(PTRM &MNode){
	if(MNode!=NULL){
		free_AList(MNode->testi4.answers);
		delete MNode;
	} 
}
void free_MList(PTRM &MFirst){
	PTRM MNode;
	while(MFirst!=NULL){
	    MNode = MFirst;
	    MFirst = MFirst->Next;
		free_MNode(MNode);	
	}
}
int nMarkNode(PTRM MFirst){
	int nMNode = 0;
	while(MFirst!=NULL){
		nMNode++;
		MFirst=MFirst->Next;
	}
	return nMNode;
}
void save_MList(std::ofstream &ofile, PTRM MFirst){
	int nMNode = nMarkNode(MFirst);
	ofile.write((const char*)&nMNode,sizeof(nMNode));
	for(PTRM MNode = MFirst; MNode!=NULL;MNode=MNode->Next){
		ofile.write((const char*)&MNode->marki4,sizeof(MNode->marki4));
		save_test(ofile,MNode->testi4);
	}
}
void load_MList(std::ifstream &ifile, PTRM &MFirst){
	int nMNode;
	ifile.read((char*)&nMNode,sizeof(nMNode));
	markInfor markif;
	test testif;
	for(int i=0; i<nMNode; i++){
		ifile.read((char*)&markif,sizeof(markif));
		load_test(ifile,testif);
		insert_last_MList(MFirst,markif,testif);
	}
}
float mark_of_subj(PTRM MFirst,char* subjID){
	for(PTRM MNode = MFirst; MNode!=NULL;MNode=MNode->Next){
		if(stricmp(MNode->marki4.Mamh,subjID)==0) return MNode->marki4.Diem;
	}
	return -1;
}
PTRM search_MList_MMH(PTRM MFirst,char* subjID){
	for(PTRM MNode = MFirst; MNode!=NULL;MNode=MNode->Next){
		if(stricmp(MNode->marki4.Mamh,subjID)==0) return MNode;
	}
	return NULL;
}	






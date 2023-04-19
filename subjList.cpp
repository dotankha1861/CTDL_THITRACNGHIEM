#include "subjList.h"
void set_subjInfor(subjInfor &subjif, char* subjID, char* subjName){
	strcpy(subjif.MAMH, subjID);
	strcpy(subjif.TENMH, subjName);
}
bool SubjList_Empty(SubjList &subj){
    return subj.nSubj==0 ;
}
bool SubjList_Full(SubjList &subj){ 
	return subj.nSubj==MAX_SUBJ-1;
}
void Init_SubjList(SubjList &subj){
	subj.nSubj=0;
}
int Search_Subject(SubjList &subj, char* SubjID)
{
	for (int i=0;i<subj.nSubj;i++)
  	     if (stricmp(subj.nodes[i].MAMH,SubjID)==0) return i;
	return -1;
}
int Insert_Subject(SubjList &subj, int i, subjInfor& info){
	int j; 
	if (i<0 || i>subj.nSubj || SubjList_Full(subj))
		return 0;
	for(j=subj.nSubj-1; j>=i; j--)
		subj.nodes[j+1] = subj.nodes[j];
	subj.nodes[i]=info;
	subj.nSubj++;
	return 1;
}
int delete_subjList_MAMH(SubjList &subj, char* SubjID){
	if(SubjList_Empty(subj)) return 0;
	int i = Search_Subject(subj, SubjID);
	if(i!=-1) {
		Delete_Subject(subj, i);
		return 1;
	}
	return 0;	    
}
int Delete_Subject(SubjList &subj, int i){
	int j;
	if (i<0 || i>=subj.nSubj || subj.nSubj==0) 
		return 0;
	for (j=i+1;j<subj.nSubj;j++)
		subj.nodes[j-1]=subj.nodes[j];
	subj.nSubj--;
	return 1; 
}
void MAMH_TENMH(char* buff,subjInfor& subji4){
	strcpy(buff,subji4.MAMH);
	strcat(buff,subji4.TENMH);
}
int Insert_SubjList_CTT(SubjList &subj, subjInfor &info){
	int i;
	for(i=0; i< subj.nSubj; i++)
		if(stricmp(info.MAMH,subj.nodes[i].MAMH)<0) break;
    Insert_Subject(subj, i,info);
    return 1;
}
void load_SubjList(std::ifstream &ifile, SubjList& subj){
	ifile.read((char*)&subj.nSubj, sizeof(subj.nSubj));
	for(int i=0; i<subj.nSubj; i++) ifile.read((char*)&subj.nodes[i], sizeof(subjInfor));
}
void save_SubjList(std::ofstream &ofile, SubjList& subj){
	ofile.write((const char*)&subj.nSubj, sizeof(subj.nSubj));
	for(int i=0; i<subj.nSubj; i++) ofile.write((const char*)&subj.nodes[i], sizeof(subjInfor));
}


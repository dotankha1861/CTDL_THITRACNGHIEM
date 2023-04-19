#ifndef _SUBJ_LIST
#define _SUBJ_LIST
#define MAX_MAMH  15
#define MAX_TENMH 50
#define MAX_SUBJ  500
#include <string.h>
#include <fstream>
struct subjInfor{
	char MAMH[MAX_MAMH+1];
	char TENMH[MAX_TENMH+1];
};
struct SubjList{	
	int nSubj;
	subjInfor nodes[MAX_SUBJ];
};
void set_subjInfor(subjInfor &subjif, char* subjID, char* subjName);
bool SubjList_Empty(SubjList &subj);
bool SubjList_Full(SubjList &subj);
void Init_SubjList(SubjList &subj);
int Insert_Subject(SubjList &subj, int i, subjInfor& info);
int Delete_Subject(SubjList &subj, int i);
int Insert_SubjList_CTT(SubjList &subj, subjInfor &info);
int delete_subjList_MAMH(SubjList &subj, char* SubjID);
int Search_Subject(SubjList &subj, char* SubjID);
void save_SubjList(std::ofstream &ofile, SubjList& subj);
void load_SubjList(std::ifstream &ifile, SubjList& subj);
void MAMH_TENMH(char* buff,subjInfor& subji4);
#endif


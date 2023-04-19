#ifndef _QUESTION_LIST
#define _QUESTION_LIST
#define MAX_MAMH 15
#define MAX_CH   90000
#define len_ID   5
#define MAX_ND   300
#define MAX_DA   200
#include <fstream>
struct quesInfor{
	int ID;
	char done;
	char MaMH[MAX_MAMH+1];
	char NoiDung[MAX_ND+1];
	char A[MAX_DA+1];
	char B[MAX_DA+1];
	char C[MAX_DA+1];
	char D[MAX_DA+1];
	char DapAn;	
};
struct quesNode{
    quesInfor quesi4;
	int bal;
	struct quesNode *left, *right;
};
typedef quesNode* PTRQ;
void set_quesInfor(quesInfor& quesif,int ID,char* subjID, char* ND, char* A, char* B, char* C, char* D, char DA);
void Initialize_QuesList(PTRQ& root);
bool Empty_QuesList(PTRQ root);
PTRQ GetQues(quesInfor quesif);
int height(PTRQ root);
int getbalance(PTRQ root);
PTRQ Right_Rotate(PTRQ root);
PTRQ Left_Rotate(PTRQ root);
void balance(PTRQ& root);
void Insert_Ques(PTRQ &root, quesInfor& infor);
void Free_Ques_List(PTRQ &root);
void Del_Ques(PTRQ &root, int infor);
int get_ID();
void set_pos_new_ID();
void save_QList(std::ofstream &ofile, PTRQ root);
PTRQ search(PTRQ root, int x);
void load_QList(std::ifstream &ifile,PTRQ &QFirst);
int nQuest(PTRQ root);
#endif

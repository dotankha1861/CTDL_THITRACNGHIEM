#include "quesList.h"
#include <string.h>
using namespace std;
void set_quesInfor(quesInfor& quesif,int ID,char* subjID, char* ND, char* A, char* B, char* C, char* D, char DA){
	quesif.ID = ID;
	strcpy(quesif.MaMH,subjID);
	strcpy(quesif.NoiDung,ND);
	strcpy(quesif.A,A);
	strcpy(quesif.B,B);
	strcpy(quesif.C,C);
	strcpy(quesif.D,D);
	quesif.DapAn = DA;
}
void Initialize_QuesList(PTRQ& root){
   root = NULL;
}
bool Empty_QuesList(PTRQ root){
	return root == NULL;
}
int height(PTRQ root){
   if(root == NULL ) return 0;
   return 1 + max(height(root->left), height(root->right));
}
//void create_file_ID(){
//	std::ofstream IDfile("ID.txt");
//	int size=0, id[MAX_CH], j , temp;
//    IDfile << size <<"\n";
//    for(int i = 1; i <= MAX_CH; i++) id[i] = 9999 + i;
//    srand(time(NULL));
//    for (int i = MAX_CH ; i> 0 ;i--){
//    	j=rand()%i+1;
//    	temp = id[i];
//    	id[i]=id[j];
//    	id[j]=temp;
//    	IDfile << id[i] <<" ";
//	}
//}
int get_ID(){
	int ID, size;
	std::ifstream IDfile ("ID.txt");
	IDfile >> size;
	IDfile.seekg(size+1,ios::cur);
	IDfile >> ID;
	IDfile.close();
	return ID;
}
void set_pos_new_ID(){
	int size;
	std::fstream IDfile("ID.txt",ios::in|ios::out);
	IDfile >> size;
	size += len_ID+1;
	IDfile.seekp(0);
	IDfile << size;
	IDfile.close();
}
PTRQ GetQues(quesInfor quesif){
    PTRQ p;
    p = new quesNode;
    if (p!=NULL){
        p->quesi4 = quesif;
        p->left = NULL;
        p->right = NULL;
        return p;
    }
    return NULL;
}
int getbalance(PTRQ root){
    if(root != NULL)
        return height(root->left)-height(root->right);
    return 0;
}
void find_left_node(PTRQ &root, PTRQ &p){
    if (p->left!= NULL)   //  p la nut la tm la nut trai nhat cua nhanh phai
        find_left_node(root, p->left);
    else{
        root->quesi4 = p->quesi4;  //  
        root = p; 
        p = p->right;
    }
}
void Del_Ques(PTRQ &root, int infor){
    if (root!=NULL){
        if (root->quesi4.ID<infor)
        	Del_Ques(root->right,infor);
        else if (root->quesi4.ID>infor)
        	Del_Ques(root->left,infor);
        else {	//if (root->quesi4.ID==infor)
        	PTRQ p1 = root;
			if (p1->right==NULL){// co 1 nhanh con ben trai
				root = p1->left;	
			}
			else if (p1->left==NULL){// co 1 nhanh con ben phai
				root = p1->right;
			}
			else {//cay co 2 nhanh con
				find_left_node(p1,root->right);
			}
			delete p1;
			if(root!=NULL){
				root->bal = getbalance(root);
				balance(root);
			} 
		}
	}
	else return;
}
PTRQ search(PTRQ root, int x){
   PTRQ p= root;
   while (p!= NULL && x!=p->quesi4.ID)
     if(x < p->quesi4.ID)
         p = p->left;
      else
         p = p->right;
	return p; 
}

void load_QList(std::ifstream &ifile,PTRQ &root){
	int nQuest;
	char buff[10];
	quesInfor quesi4;
	ifile >> nQuest;
	while(nQuest--){
		ifile >> quesi4.ID;
		ifile.getline(buff,10);
		ifile.getline(quesi4.MaMH,MAX_MAMH);
		ifile >> quesi4.done;
		ifile.getline(buff,10);
		ifile.getline(quesi4.NoiDung,MAX_ND); 
		ifile.getline(quesi4.A,MAX_DA);
		ifile.getline(quesi4.B,MAX_DA);
		ifile.getline(quesi4.C,MAX_DA);
		ifile.getline(quesi4.D,MAX_DA);
		ifile >> quesi4.DapAn;
		Insert_Ques(root,quesi4);
	}
}
int nQuest(PTRQ root){
	if(root==NULL) return 0;
	return 1 + nQuest(root->left) + nQuest(root->right);
}
void save_Questions(std::ofstream &ofile, PTRQ root){
	if(root == NULL) return;
	ofile<<root->quesi4.ID<<endl;
	ofile<<root->quesi4.MaMH<<endl;
	ofile<<root->quesi4.done<<endl;
	ofile<<root->quesi4.NoiDung<<endl;
	ofile<<root->quesi4.A<<endl;
	ofile<<root->quesi4.B<<endl;
	ofile<<root->quesi4.C<<endl;
	ofile<<root->quesi4.D<<endl;
	ofile<<root->quesi4.DapAn<<endl;
	save_Questions(ofile,root->left);
	save_Questions(ofile,root->right);
}
void save_QList(std::ofstream &ofile, PTRQ root){
    ofile << nQuest(root) <<endl;
	save_Questions(ofile,root);
}
PTRQ Right_Rotate(PTRQ root){
   PTRQ p = NULL;
   if(root != NULL&&root->left!=NULL){
	      p = root->left;
	      root->left = p->right;
	      p->right = root;
		  root->bal= getbalance(root);  //cap nhat chieu cao
    	  p->bal = getbalance(p);		//cap nhat chieu cao
    }
   return p;
}
PTRQ Left_Rotate(PTRQ root){
   PTRQ p = NULL;
   if (root != NULL&&root->right!=NULL){
   		p = root->right;
	    root->right = p->left;
	    p->left = root;
		root->bal= getbalance(root);//cap nhat chieu cao
		p->bal= getbalance(p);		//cap nhat chieu cao
   }
   return p;
}
void balance(PTRQ& root){
//	int bal = getbalance(root);
    if (root->bal>1 && getbalance(root->left)>=0)//lech trai trai
                root = Right_Rotate(root);
    if (root->bal>1 && getbalance(root->left)<0){// lech trai phai
                root->left = Left_Rotate(root->left);
                root = Right_Rotate(root);
    }
    if (root->bal<-1 && getbalance(root->right)<=0) // lech phai phai
               root = Left_Rotate(root);
    if (root->bal<-1 && getbalance(root->right)>0){ //lech phai trai
               root->right = Right_Rotate(root->right);
               root = Left_Rotate(root);
	}
}
void Free_Ques_List(PTRQ &root){
	if (root!=NULL){
		Free_Ques_List(root->left);
		Free_Ques_List(root->right);
		delete root;
	}
}
void Insert_Ques(PTRQ &root, quesInfor& infor){
    if (root==NULL) root = GetQues(infor);
    else {
        if(infor.ID< root->quesi4.ID)
            Insert_Ques(root->left,infor);    
        else
            Insert_Ques(root->right,infor);
        root->bal = getbalance(root); 
     	balance(root);
    }
}
	

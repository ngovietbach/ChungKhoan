#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
	char name[5];
	float gia_mo[10];
	float gia_dong[10];
}chungkhoan;
chungkhoan CK;
typedef struct node{
	chungkhoan data;
	struct node* left;
	struct node* right;
}node;
node* root;
node* add(node* root,chungkhoan CK){
    if(root==NULL){
        node* root=(node*)malloc(sizeof(node));
        root->data=CK;
        root->left=NULL;
        root->right=NULL;
        return root;
    }
    else if(strcmp(root->data.name,CK.name)>0)root->left=add(root->left,CK);
    else if(strcmp(root->data.name,CK.name)<0)root->right=add(root->right,CK);
    }
node* search(chungkhoan CK,node* root){
    if(root==NULL)return NULL;
    else if(strcmp(root->data.name,CK.name)==0)return root;
    else if(strcmp(root->data.name,CK.name)>0)return search(CK,root->left);
    else return search(CK,root->right); 
}
node* search2(char s[],node* root){
    if(root==NULL)return NULL;
    else if(strcmp(root->data.name,s)==0)return root;
    else if(strcmp(root->data.name,s)>0)return search2(s,root->left);
    else return search2(s,root->right); 
}
void inorder(node* root){
	if(root!=NULL){
        inorder(root->left);
		float f;
        f=-(root->data.gia_mo[0]+root->data.gia_mo[1]+root->data.gia_mo[2]+root->data.gia_mo[3]+root->data.gia_mo[4]+root->data.gia_mo[5]+root->data.gia_mo[6]+root->data.gia_mo[7]+root->data.gia_mo[8]+root->data.gia_mo[9])+root->data.gia_dong[0]+root->data.gia_dong[1]+root->data.gia_dong[2]+root->data.gia_dong[3]+root->data.gia_dong[4]+root->data.gia_dong[5]+root->data.gia_dong[6]+root->data.gia_dong[7]+root->data.gia_dong[8]+root->data.gia_dong[9];

        printf("%s %.3f\n",root->data.name,f/10.0);
        inorder(root->right);
    }
}
void inorder1(node* root){
	int i;
    int k=0;
    if(root!=NULL){
        inorder1(root->left);
		for(i=0;i<2;i++){
        if(root->data.gia_dong[i]>root->data.gia_mo[i])k++;
		}
        if(k==2)printf("%s\n",root->data.name);
        k=0;
		inorder1(root->right);
    }
}
void inorder2(node* root){
	int i;
    int k=0;
    int max=0;
    char s[5];
    if(root!=NULL){
        inorder1(root->left);
		for(i=0;i<10;i++){
        if(root->data.gia_dong[i]>root->data.gia_mo[i])k++;
		}
        if(k>max){
            max=k;
            strcpy(s,root->data.name);}
        k=0;
		inorder1(root->right);
    }
    printf("%s  Ngay: %d\n",s,max);
}	
node* doc_file(node* root){
	int i,j,n;
	float a,b;
	FILE* f1;
	char s[10];
	f1=fopen("data.txt","r");
	if(f1==NULL){
		printf("Mo file khong thanh cong \n");
		return NULL;
	}
	fscanf(f1,"%d\n",&n);
    for(i=0;i<10;i++){
        for(int j=0;j<n;j++){
            fscanf(f1,"%s\t",&CK.name);
            fscanf(f1,"%f\t",&CK.gia_mo[i]);
            fscanf(f1,"%f\n",&CK.gia_dong[i]);
            if(search(CK,root)==NULL){
                root=add(root,CK);
            }
            else{
                search(CK,root)->data.gia_mo[i]=CK.gia_mo[i];
                search(CK,root)->data.gia_dong[i]=CK.gia_dong[i];
            }
        }
    }
    fclose(f1);
	return root;
}	
void tim_kiem(node* root){
	char s[10];
	int i;
    float max,min;
    printf("Nhap ma chung khoan: ");fflush(stdin);gets(s);
	node* cur;
	cur=search2(s,root);
	if(cur==NULL){
		printf("khong co ma nay \n");
		return;
	}
	else{
		max=cur->data.gia_dong[0];
        min=cur->data.gia_dong[0];
        for(i=1;i<10;i++){
            if(cur->data.gia_dong[i]>max)max=cur->data.gia_dong[i];
            if(cur->data.gia_dong[i]<min)min=cur->data.gia_dong[i];
            }
        }
        printf("%s %.3f %.3f \n",cur->data.name,min,max);   
	}


void ma_tang(node* root){

};
void freenode(node* root){
	freenode(root->right);
	free(root);
	freenode(root->left);
}
void giaodien()
{
   printf("=============================================\n");
   printf("CHUNG KHOAN \n");
   printf("1. Doc file \n");	
   printf("2, Tim kiem theo ma chung khoan \n");
   printf("3. Tim kiem nhung ma chung khoan co xu huong tang \n");
   printf("4. Tim ma co so ngay tang lon nhat\n");
   printf("5. Thoat\n");	
   printf("=============================================\n"); 	
}
int main()
{
	char ch;
	do{
		giaodien();
		printf("Nhan so cau [1..5] de lua chon: \n ");
		fflush(stdin);
		scanf("%c",&ch);
		switch(ch){
			case '1':{
				root=doc_file(root);
                inorder(root);
				break;
			}
			case '2':{
				tim_kiem(root);
				break;
			}
			case '3':{
				inorder1(root);
				break;
			}
			case '4':{
				inorder2(root);
				break;
			}
			case '5':{
				printf("NgoVietBach 20205056 \n");
				freenode(root);
				break;
			}
		}
	}while(ch!='5');
    
	return 0;
}
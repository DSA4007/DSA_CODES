#include <iostream>
#include <string.h>
#include<stdlib.h>
using namespace std;

struct Node{
	
	char data;
	Node* left;
	Node* right;
	Node(){
		left = NULL;
		right = NULL;
	}
	
};

class stack{
	int top;
	Node* data[30];
	
	public:
		stack(){
			top = -1;
		}
		
		bool isempty(){
			return top==-1;
		}
		
		void push(Node* rp){
			data[++top] =rp;
		}
		
		Node* pop(){
			return data[top--];
		}
};

class Tree{

	char prefix[20];
	
	public:
		Node* top;
		
		void expression (char prefix[] ){
			
			char c;
			stack s;
			Node *op1 , *op2 ;
			int len , i;
			
			len = strlen(prefix);
			
			for(i = len - 1 ; i>=0 ; i--){ //Inserting in reverse order 
				top = new Node();
				
				if( isalpha(prefix[i]) ){ // OPERAND
					top->data = prefix[i];
					s.push(top);
				}else if(prefix[i]=='+'||prefix[i]=='-'||prefix[i]=='*'||prefix[i]=='/'){ //OPERATOR
				
					op2 = s.pop();
					op1 = s.pop();
					
					top->data = prefix[i]; //OPERATOR
					top->left = op2; //OPERAND
					top->right = op1;
					s.push(top);
				}
			}
			top = s.pop();
			
		}


		void non_rec_po(Node* root){
		
			if(root==NULL){
			  return;
			}
			
			stack s1 , s2;
			
			cout<<"\n";
			
			s1.push(root);
			
			//We need to push the root or parent node in s2  and the child nodes in s1 so that it will contain nodes in reverse order
			while(!s1.isempty() ){
			
			        Node * T = s1.pop();
			        
			        s2.push(T);
			        
				if(T->left !=NULL){
					s1.push(T->left);
				}
				if(T->right!=NULL){
					s1.push(T->right);
				}
			}
			
			while(!s2.isempty()){
				
				top = s2.pop();
				cout<<top->data<<"\t";
			}
			
		}

		void del(Node*root){
		
			if(root == NULL){
				return;
			}
			del(root->left);
			del(root->right);
			cout<<"Deleted Data: "<<root->data<<endl;
			delete root;
		}

};


int main(){
	
	char prefix[20];
	Tree t;
	cout<<"Enter prefix expression: ";
	cin>>prefix;
	
	cout<<prefix<<endl;
	
	t.expression(prefix);
	cout<<"Postorder Traversal"<<endl;
	t.non_rec_po(t.top);
	
	cout<<"Do you want to delete? (1/0)";
	int choice;
	cin>>choice;
	
	if(choice==1){
		t.del(t.top);
	}
	return 0;
	
}

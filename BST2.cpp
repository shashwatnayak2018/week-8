#include<iostream>
using namespace std;


class Node{
public:
    int data;
    Node * left;
    Node * right;
    Node * parent;

    Node(int value){
        data = value;
        left = NULL;
        right = NULL;
        parent = NULL;
    }  
};

class BST{
public:
    Node * root;
    BST(){
        root = NULL;
    }
    void insertHelper(int value){
        insert(root, value);
    }
    void insert(Node *curr, int value){
        // If root is NULL, then create a node and make it root. 
        if (root == NULL) root = new Node(value);
        // Else Decide to move left or right. 
        else if (value < curr->data)  {
            // if left is already NULL, create a new node and link it. 
            if (curr->left == NULL) {
                curr->left = new Node(value);
                curr->left->parent = curr;
            }
            // Move left and call insert there. 
            else insert(curr->left, value);
        }
        else {
            // if right is already NULL, create a new node and link it. 
            if (curr->right == NULL) {
                curr->right = new Node(value);
                curr->right->parent = curr;
            }
            // Move right and call insert there. 
            else insert(curr->right, value);
        }
    }
    void displayHelper(){
        display(root);
    }
    void display(Node * curr){
        // Case for empty tree and leaf nodes children.
        if( curr ==  NULL) return;
        // IN order print.
        // Print left. 
        display(curr->left);
        // Print myself.
        cout << curr->data << ", ";
        // Print right.
        display(curr->right);
    }
    Node * searchHelper(int value){
        return search(root, value);
    }
    Node * search(Node * curr, int value){
        // Are you the value? or Are you NULL?  if yes return curr
        if(curr == NULL || curr->data == value ) return curr;
        // else you search in right or left. 
        // Left
        else if(value < curr->data) return search(curr->left, value);
        // Right
        else  return search(curr->right, value);
    }
    void print2DUtil(Node *root, int space)  
    {  
        // Base case  
        if (root == NULL)  
            return;  
        // Increase distance between levels  
        space += 5;  
        // Process right child first  
        print2DUtil(root->right, space);  
    
        // Print current node after space  
        // count  
        cout<<endl;  
        for (int i = 5; i < space; i++)  
            cout<<" ";  
        cout<<root->data<<"\n";  
    
        // Process left child  
        print2DUtil(root->left, space);  
    }  
  
    // Wrapper over print2DUtil()  
    void print2D()  
    {  
        cout << "******************************" << endl;
        // Pass initial space count as 0  
        print2DUtil(root, 0);  
        cout << "******************************" << endl;
        
    }
	Node * findmin(Node * current)
	{
		if(current->left == NULL)
		{
			return current;
		}
		else
		{
			findmin(current->left);
		}
	}
	void rep(int a,int b)
	{
		replace_at_parent(searchHelper(a),searchHelper(b));
	}
	void replace_at_parent(Node * A, Node * B)
	{
		if(A->data < A->parent->data)
		{
			A->parent->left = B;
			B->parent = A->parent;
		}
		if(A->data > A->parent->data)
		{
			A->parent->right = B;
			B->parent = A->parent;
		}
	}
    

	void binary_delete(Node * curr, int key)
	{
		if(curr == NULL)
		{
			cout<<"BST is empty or does not have that element"<<endl;
		}
		else if(key < curr->data)
		{
			binary_delete(curr->left,key);
		}
		else if(key > curr->data)
		{
			binary_delete(curr->right,key);
		}
		else
		{
			//having no child
			if(curr->left == NULL && curr->right == NULL)
			{
				if(root->left == NULL && root->right == NULL)
				{
					delete root;
					root = NULL;
				}
				else
				{
					if(curr->parent->data < curr->data)
					{
						curr->parent->right = NULL;
						delete curr;
					}
					else if(curr->parent->data >curr->data)
					{
						curr->parent->left = NULL;
						delete curr;
					}
					else 
					{
						curr->parent->right = NULL;
						delete curr;
					}
				}
			}
			//havig one child
			else if(curr->left== NULL || curr->right == NULL)
			{
					if(curr == root)
					{
						if(curr->left == NULL)
						{
							root = curr->right;
						}
						else
						{
							root = curr->left;
						}
					}
					else{
					Node * temp = curr;
					if(curr->right != NULL)
					{
						replace_at_parent(curr,curr->right);
					}
					else
					{
						replace_at_parent(curr,curr->left);
					}
					delete temp;
					}
			}
			//having two child
			else
			{
				Node * temp = findmin(curr->right);
				int c;
				c = temp->data;
				binary_delete(curr->right,temp->data);
				curr->data = c;
			}
		}
	}

};

int main(){
    
    BST bst1;
    bst1.insertHelper(4);
    bst1.insertHelper(2);
    bst1.insertHelper(3);
    bst1.insertHelper(1);
    bst1.insertHelper(6);
    bst1.insertHelper(5);
    bst1.insertHelper(7);
    bst1.insertHelper(8);
    bst1.displayHelper();
    if(bst1.searchHelper(3) != NULL){
        cout << endl << bst1.searchHelper(3)->data << endl;
    }
	//bst1.rep(7,8);
	//bst1.displayHelper();
	
    bst1.print2D();
    bst1.binary_delete(bst1.root,5);
    bst1.print2D();
    bst1.binary_delete(bst1.root,6);
    bst1.print2D();
    cout << "Deleting 2" << endl;
    bst1.binary_delete(bst1.root,2);
    bst1.print2D();
    bst1.binary_delete(bst1.root,4);
    bst1.print2D();
    bst1.binary_delete(bst1.root,7);
    bst1.print2D();
    bst1.binary_delete(bst1.root,8);
    bst1.print2D();
    bst1.binary_delete(bst1.root,3);
    bst1.print2D();
    bst1.binary_delete(bst1.root,1);
    bst1.print2D();
    bst1.binary_delete(bst1.root,1);
    bst1.print2D();
	return 0;
}

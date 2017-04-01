#include<bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
   // TreeNode* mid;
    TreeNode* right;
};

TreeNode* add(int x)
{
    TreeNode* node= (TreeNode*) malloc(sizeof(TreeNode));
    node->val=x;
    node->left=NULL;
  //  node->mid=NULL;
    node->right=NULL;

    return node;
}

TreeNode* _insert(TreeNode* root, int x)
{
    if(root==NULL)
    {
        return add(x);
    }

    else
    {
        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty())
        {
            TreeNode * x1=q.front();
            q.pop();
            if(x1->left==NULL)
            {
                x1->left=add(x);
                return x1;
            }
            else q.push(x1->left);

//            if(x1->mid==NULL)
//            {
//                x1->mid=add(x);
//                return x1;
//            }
//            else q.push(x1->mid);

            if(x1->right==NULL)
            {
                x1->right=add(x);
                return x1;
            }
            else q.push(x1->right);
        }
    }
}

void in_order(TreeNode* root)
{
    if(root==NULL) return;

    in_order(root->left);
    cout<<root->val<<endl;
 //   in_order(root->mid);
    in_order(root->right);
}

int main()
{
    TreeNode* root=NULL;
    TreeNode* root1=NULL;
    root=_insert(root,12);
    root1=root;
    root=_insert(root,34);
    root=_insert(root,45);
    root=_insert(root,95);
    in_order(root1);

    return 0;
}

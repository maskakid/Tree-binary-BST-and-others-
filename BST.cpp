
#include<bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct TreeNode* newNode(int val)
{
    struct TreeNode* node = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    node->val   = val;
    node->left   = NULL;
    node->right  = NULL;

    return(node);
}

TreeNode* Add( int v)
{
    TreeNode* x= (TreeNode*) malloc(sizeof(TreeNode));

    x->val=v;
    x->left=NULL;
    x->right=NULL;
    return x;

}

TreeNode* _insert( TreeNode* node, int val)
{
    /* 1. If the tree is empty, return a new,
        single node */
    if (node == NULL)
        return(newNode(val));
    else
    {
        struct TreeNode *temp;

        /* 2. Otherwise, recur down the tree */
        if (val <= node->val)
        {
            //    temp = _insert(node->left, val);
            temp = _insert(node->left, val);
            node->left  = temp;
        }
        else
        {
            temp = _insert(node->right, val);
            node->right = temp;

        }

        /* return the (unchanged) node pointer */
        return node;
    }
}

int valid(TreeNode* root, int val,TreeNode** x)
{
    if(root==NULL) return 0;
    if(root->val==val)
    {
        * x=root;
        //  cout<<x->val<<endl;
        return 1;
    }

    int k=0,k1=0;

    if(root->left!=NULL) k=valid(root->left,val,x);
    if(root->right!=NULL) k1=valid(root->right,val,x);

    return k||k1;


}

int height(TreeNode* root)
{
    if(root==NULL) return 0;

    int x=height(root->left);
    int x1=height(root->right);

    return max(x,x1)+1;
}

int balacned(TreeNode* root)
{
    if(root==NULL) return true;

    int h=height(root->left);
    int h1=height(root->right);

    // if(abs(h-h1)<=1 ) return 1;
    if(abs(h-h1)>1 ) return 0;

    return (balacned(root->left) && balacned(root->right));
}

TreeNode * soln(TreeNode *root, int val)
{
    if(root==NULL) return NULL;
    TreeNode* x=NULL;
    int k=valid(root,val,&x);
    // cout<<k<<endl;

    if(x==NULL) return NULL;

    if(x->right!=NULL)
    {
        x=x->right;
        while(x->left!=NULL) x=x->left;
        return x;
    }

    TreeNode* ans=NULL;
    TreeNode* cur=root;

    while(cur!=x)
    {
        if(cur->val>val)
        {
            ans=cur;
            cur=cur->left;
        }
        else cur=cur->right;
    }
    return ans;

}

int Identical(TreeNode* root, TreeNode* root1)
{
    if(root==NULL and root1==NULL) return 1;

    if(  root1->val==root->val ) return 1;

    //  if(root==root1) return 1;

    if(root==NULL) return 0;
    if(root1==NULL) return 0;

    return  Identical(root->left,root1->left)
            && Identical(root1->right,root1->right);

//    if(root==root1) return 1;
//
//    if(root==NULL) return 0;
//    if(root1==NULL) return 0;
//
//    return  Identical(root->left,root1->left)
//                                    && Identical(root1->right,root1->right);
}

void Invert(TreeNode * root)
{
    if(root==NULL) return ;

    Invert(root->left);
    Invert(root->right);

    swap(root->left, root->right);
}

string con_string(int x)
{
    stringstream ss;
    ss<<x;
    string s;
    ss>>s;
    return s;
}

void pre_order(TreeNode * root, string &str)  // if tree X is subtree of tree Y or not check using preorder
{
    if(root==NULL)
    {
        str+='X';
        return;
    }

    str+=con_string(root->val);
    pre_order(root->left,str);
    pre_order(root->right,str);

}


TreeNode* Sorted_Array_to_BST(TreeNode* root, vector<int>& v, int l ,int h)
{
    if(l>h) return NULL;

    int mid=(l+h)/2;
    root=Add(v[mid]);

    root->left=Sorted_Array_to_BST(root->left,v,l,mid-1);
    root->right=Sorted_Array_to_BST(root->right,v,mid+1,h);

    return root;
}

vector<int>in_order(TreeNode * root) //without recursion
{
    stack<TreeNode*>st;
    vector<int>v;

    while(root!=NULL or !st.empty())
    {
        if(root!=NULL)
        {
            st.push(root);
            root=root->left;
        }
        else if(!st.empty())
        {
            TreeNode* tmp=st.top();
            st.pop();
            v.push_back(tmp->val);
            root=tmp->right;
        }
    }
    return v;
}

void in_order(TreeNode * root, string &str)
{
    if(root==NULL) return ;

    in_order(root->left,str);

    str+=con_string(root->val);
    str+=" ";

    in_order(root->right,str);


}

void post_order(TreeNode * root, string &str)
{
    if(root==NULL)
    {
        //str+='X';
        return;
    }

    post_order(root->left,str);
    post_order(root->right,str);

    str+=con_string(root->val);
    str+=" ";

}

TreeNode* flat(TreeNode* A)  // binary tree to linked list (only right child no left)
{
    stack<TreeNode*>st;
    TreeNode* AA=A;
   // if(A==NULL)
    while(A!=NULL or !st.empty())
    {
        cout<<"ddd\n";
        if(A->right!=NULL) st.push(A->right);

        if(A->left!=NULL)
        {
            A->right=A->left;
            A->left=NULL;
        }
        else if(!st.empty())
        {
            TreeNode* x=st.top();
            st.pop();
            A->right=x;
        }
        A=A->right;
    }
    return AA;
}

TreeNode* flatten(TreeNode * root) // using pre order not good
{
    vector<int>v;

    pre_order(root,v);

    TreeNode* root1=NULL;

    for(int i=0; i<v.size(); i++)
        root=_insert11(root1,v[i]);
    return root1;
}


vector<vector<int > > zigzag_traversal(TreeNode* root)
{
    if(root==NULL) return {};

    stack<TreeNode*>s1,s2;

    vector<vector<int > >vc;
    s1.push(root);

    while(!s1.empty() || !s2.empty())
    {
        vector<int>v,v1;
        while(!s1.empty())
        {
            TreeNode *x=s1.top();
            v.push_back(x->val);
            s1.pop();
            if(x->left!=NULL) s2.push(x->left);
            if(x->right!=NULL) s2.push(x->right);
        }

        while(!s2.empty())
        {
            TreeNode *x=s2.top();
            v1.push_back(x->val);
            s2.pop();
            if(x->right!=NULL) s1.push(x->right);
            if(x->left!=NULL) s1.push(x->left);

        }

        if(v.size()) vc.push_back(v);
        if(v1.size()) vc.push_back(v1);
    }

    return vc;

}

int main()
{
    struct TreeNode* root = NULL, *temp, *succ, *min;
    TreeNode* root1=NULL;

    //creating the tree given in the above diagram
    root = _insert(root, 20);
    root = _insert(root, 8);
    root = _insert(root, 22);
    root = _insert(root, 4);
    root = _insert(root, 12);
    root = _insert(root, 10);
    root = _insert(root, 14);
    root = _insert(root, 18);

    root1 = _insert(root1, 20);
    root1 = _insert(root1, 8);
    root1 = _insert(root1, 22);
    root1 = _insert(root1, 4);
    root1 = _insert(root1, 12);
    root1 = _insert(root1, 10);
    root1 = _insert(root1, 14);
    root1 = _insert(root1, 18);

    cout<<Identical(root,root1);

    //cout<<balacned(root);
//   TreeNode* x=soln(root,4);
   cout<<(root->val)<<endl;

//    vector<int>v={90, 228, 245, 290, 397, 471, 572, 649, 688, 710, 823, 829, 830, 859, 932, 939, 962};
//
//   int sz=v.size();
//
//   root=Sorted_Array_to_BST(root,v,0,sz-1);

//   string s="";
//   pre_order(root,s);
//  in_order(root,s);
//  post_order(root,s);
//   cout<<s<<endl;

}



// height and infront

/*
#include<bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    int _front;
    TreeNode* left;
    TreeNode*right;
};

TreeNode* Add(int x, int v)
{
    //TreeNode* p=new TreeNode();
    TreeNode* p= (TreeNode*) malloc(sizeof(TreeNode));

    p->left=NULL;
    p->right=NULL;
    p->val=x;
    p->_front=v;

    return p;
}

TreeNode* _insert(TreeNode* root, int x, int _front)
{
    if(root==NULL) return Add(x,_front);
    if(root->_front >=_front)
    {
        //if(root->left==NULL) root->left=Add(x,_front);
        //else
            root->left=_insert(root->left,x,_front);
        root->_front+=1;
    }
    else
    {
       // if(root->right==NULL) root->right=Add(x,_front);
        //else
        root->right=_insert(root->right,x,_front-root->_front);
    }

    return root;
}

bool comp(pair<int,int> a, pair<int,int> b)
{
    return a.first>b.first;
}

void in_order(TreeNode * root, vector<int>&v)
{
    if(root==NULL) return ;

    in_order(root->left,v);

    v.push_back(root->val);

    in_order(root->right,v);


}

vector<int>soln(vector<int>h, vector<int>in )
{
    vector<pair<int , int> >vc;
    for(int i=0;i<h.size();i++) vc.push_back( make_pair( h[i],in[i] ) );
    sort(vc.begin(),vc.end(),comp);

   // for(int i=0;i<vc.size();i++) cout<<vc[i].first<<" "<<vc[i].second<<endl;

    TreeNode* root=NULL;

    //root=Add(vc[0].first,vc[0].second);

    for(int i=0;i<vc.size();i++)
        root=_insert(root,vc[i].first,vc[i].second);

    vector<int>v;
    in_order(root,v);

   // for(int i=0;i<h.size();i++) cout<<v[i]<<" ";
    return v;
}


TreeNode* flat(TreeNode* A)
{
    stack<TreeNode*>st;
    while(A!=NULL or !st.empty())
    {
        if(A->right!=NULL) st.push(A->right);

        if(A->left!=NULL)
        {
            A->right=A->left;
            A->left=NULL;
        }
        else if(!st.empty())
        {
            TreeNode* x=st.top();
            st.pop();
            A->right=x;
        }
        A=A->right;
    }
    return A;
}

int main()
{
    TreeNode* root=NULL;
   // A.
//    int t;
//    scanf("%d",&t);
//    while(t--)
//    {
//        int n;
//        scanf("%d",&n);
//            vector<int>h;
//            vector<int>in;
//
//            for(int i=0;i<n;i++) {int x;
//            cin>>x;
//            h.push_back(x);}
//            for(int i=0;i<n;i++) {int x; cin>>x;
//            in.push_back(x);}
//
//            vector<int>v=soln(h,in);
//            for(int i=0;i<n-1;i++) cout<<v[i]<<" ";
//            cout<<v[n-1]<<endl;
//            h.clear();
//            in.clear();
//
//    }



}


*/


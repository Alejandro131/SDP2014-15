#include <cstring>
#include <iostream>

using namespace std;


template<typename Value>
struct Node
{
    Node() : val(0), left(0), mid(0), right(0), parent(0)
    {}
    Value* val;									// value associated with string
    Node<Value>* left, *mid, *right, *parent;
    char c;										// character
};

template <typename Value>
class TST
{
public:
    TST();
    ~TST();
    TST(const TST<Value>& tree);
    const TST<Value>& operator=(const TST<Value>& tree);

    int size() const;
    bool contains(const char * key);
    Value* search(const char * key);
    void insert(const char * s, const Value& val);
    bool deleteNode(const char * key);
    void print();
private:

    int N;       // size
    Node<Value>* root;   // root of TST

    Node<Value>* insert(Node<Value>*& x, Node<Value>* parent, const char * s, const Value& val, unsigned int d);
    Node<Value>* search(Node<Value>* x, const char * key, unsigned int d);
    void print_help(Node<Value>* x,  char * prefix);

    void copy(const TST<Value>& tree);
    void copy(Node<Value>*& node, Node<Value>* parent, Node<Value>* nodeToCopy);
    void del();
    void del(Node<Value>* node);
	void del1(Node<Value>* , const char*);
	void TST::remove(const char*);
};


template<typename Value>
bool TST<Value>::contains(const char * key)
{
    return search(key) != 0;
}

template<typename Value>
Value* TST<Value>::search(const char * key)
{
    if (!key) return 0;
    Node<Value>* x = search(root, key, 0);
    if (x == 0) return 0;
    return x->val;
}

template<typename Value>
Node<Value>* TST<Value>::search(Node<Value>* x, const char * key, unsigned int d)
{
    if (key==NULL || x == 0) return 0;
    char c = key[d];
    if (c < x->c)					return search(x->left, key, d);
    else if (c > x->c)              return search(x->right, key, d);
    else if (d < strlen(key) - 1)	return search(x->mid, key, d + 1);
    else							return x;
}

template<typename Value>
void TST<Value>::insert(const char * s, const Value& val)
{
    if (!contains(s)) ++N;
    root = insert(root, 0, s, val, 0);
}

template<typename Value>
Node<Value>* TST<Value>::insert(Node<Value>*& x, Node<Value>* parent, const char * s, const Value& val, unsigned int d)
{
    if(strlen(s)==0 || d>strlen(s)) return NULL;
    char c = s[d];
    if (x == 0)
    {
        x = new Node<Value>;
        x->c = c;
        x->parent = parent;
        //cout<<"inserting: "<<s[d]<<endl;
    }
    if (c < x->c)				x->left = insert(x->left, x, s, val, d);
    else if (c > x->c)			x->right = insert(x->right, x, s, val, d);
    else if (d < strlen(s) - 1)	x->mid = insert(x->mid, x, s, val, d + 1);
    else						x->val = new Value(val);
    return x;
}


template <typename Value>
bool TST<Value>::deleteNode(const char * key)
{
    if (!key)
    {
        return false;
    }

    if (!contains(key))
    {
        return false;
    }

	del1(root, key);
    return true;
}

template <typename Value>
void TST<Value>::del1(Node<Value>* node, const char* str)
{
	if(strlen(str) < 1)
		return;
	if(str[0] < node -> c)
	{
		del1(node->left, str);
	}
	else if(str[0] == node-> c)
	{
		del1(node->mid, ++str);
	}
	else
	{
		del1(node->right, str);
	}

	if(!node->left && !node->right && !node->mid)
	{
        if (node->parent)
        {
            if (node->parent->left == node)
            {
                node->parent->left = 0;
            }
            else if (node->parent->right == node)
            {
                node->parent->right = 0;
            }
            else
            {
                node->parent->mid = 0;
            }
        }
		delete node;
		return;
	}
	else if(strlen(str) == 1)
		return;
}


template <typename Value>
TST<Value>::TST(const TST<Value>& tree)
{
    copy(tree);
}

template <typename Value>
const TST<Value>& TST<Value>::operator=(const TST<Value>& tree)
{
    if (this != &tree)
    {
        del();
        copy(tree);
    }
    return *this;
}


template <typename Value>
void TST<Value>::copy(Node<Value>*& node, Node<Value>* parent , Node<Value>* nodeToCopy)
{
    if (nodeToCopy)
    {
        node = new Node<Value>;
        node->c = nodeToCopy->c;
        node->parent = parent;
        if (nodeToCopy->val)
            node->val = new Value(*nodeToCopy->val);
        copy(node->left, node, nodeToCopy->left);
        copy(node->right, node, nodeToCopy->right);
        copy(node->mid, node, nodeToCopy->mid);
    }
}

template <typename Value>
void TST<Value>::copy(const TST<Value>& tree)
{
    copy(this->root, 0, tree.root);
    this->N = tree.N;
}

template <typename Value>
void TST<Value>::del()
{
    del(root);
    this->root = 0;
    this->N = 0;
}

template <typename Value>
void TST<Value>::del(Node<Value>* node)
{
    if (node)
    {
        if (node->val)
            delete node->val;
        del(node->left);
        del(node->right);
        del(node->mid);
        delete node;
    }
}

template <typename Value>
TST<Value>::TST() : N(0), root(0)
{
}

template <typename Value>
TST<Value>::~TST()
{
    del();
}

template <typename Value>
int TST<Value>::size() const
{
    return N;
}

template<typename Value>
void TST<Value>::print()
{
    char prefix[]  = {};

    print_help(this->root, prefix);

}

template<typename Value>
void TST<Value>::print_help(Node<Value>* x,   char * prefix)
{
    if(x==NULL) return ;

    print_help(x->left,prefix);

    int i=strlen(prefix);
    char *nodeprefix= new char[strlen(prefix)+2];
    strncpy(nodeprefix,prefix,i);
    nodeprefix[i]=x->c;
    nodeprefix[i+1]='\0';

    if(x->val)
    {
        cout<<nodeprefix<<" "<<*(x->val)<<endl;
    }

    print_help(x->mid, nodeprefix);
    print_help(x->right, prefix);
    delete(nodeprefix);

}

int main()
{
    TST<int> t;
    t.insert("tanq",43);
    t.insert("ivan",53);
    t.insert("malina",23);
    t.insert("malin",223);
    t.insert("kalin",83);
    t.insert("paolina",13);
    t.deleteNode("malinatt");
    t.print();

    return 0;
}


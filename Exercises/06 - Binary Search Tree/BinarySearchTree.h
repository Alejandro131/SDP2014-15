#ifndef BINARY_SEARCH_TREE_H_INCLUDED
#define BINARY_SEARCH_TREE_H_INCLUDED

template <typename K, typename V>
class BinarySearchTree
{
	struct Node
	{
		Node* parent;
		Node* left;
		Node* right;
		K key;
		V value;

		Node()
		{
			parent = left = right = 0;
		}

		Node(K& k, V& v, Node* p = 0)
		{
			parent = left = right = 0;
			key = k;
			value = v;
			parent = p;
		}

		bool isLeftChild()
		{
			return (this == parent->left);
		}

		bool isRightChild()
		{
			return (this == parent->right);
		}
	};

	public:

		BinarySearchTree()
		{
			root = 0;
		}

        ~BinarySearchTree()
        {
		    deleteTree();
		}

        BinarySearchTree(const BinarySearchTree& b)
        {
        	copyTree(b);
        }

        BinarySearchTree& operator = (const BinarySearchTree& b)
        {
        	if (this != &b)
		    {
		        deleteTree();
		        copyTree(b);
		    }
		    return *this;
        }

		bool find(const K& k, V &val)
		{
			Node** ptr = lookup(k);

			if (*ptr)
			{
				val = (*ptr)->value;
				
				splay(*ptr);

				return true;
			}

			return false;
		}

		bool insert(K& k, V& val)
		{
			Node** ptr = lookup(k);
			Node** parent = lookupParent(k);

			if (!*ptr)
			{
				Node* node = new Node(k, val);
				node->parent = *parent;
				*ptr = node;

				return true;
			}

			return false;
		}

		void remove(K& key)
		{
			Node** ptr = lookup(k);

			if (*ptr)
			{
				if (!(*ptr)->right && (*ptr)->left)
					swap(*ptr, (*ptr)->left);
				else if (!(*ptr)->left && (*ptr)->right)
					swap(*ptr, (*ptr)->right);
				else
				{
					Node** node = findSubtreeMinimum(&(root->right));
					if ((*node)->parent != *ptr)
					{
						swap(*node, (*node)->right);
						(*node)->right = (*ptr)->right;
						(*node)->right->parent = *node;
					}
					swap(*ptr, *node);
					(*node)->left = (*ptr)->left;
					(*node)->left->parent = *node;
				}

				delete *ptr;
			}
		}

	private:
		Node* root;

		Node** lookup(const K& k)
		{
			Node** ptr;
			ptr = &root;

			while (*ptr)
			{
				if ((*ptr)->key == k)
					return ptr;
				else if ((*ptr)->key > k)
					ptr = &((*ptr)->left);
				else
					ptr = &((*ptr)->right);
			}

			return ptr;
		}

		Node** lookupParent(const K& k)
		{
			Node** ptr;
			Node** previous;
			previous = ptr = &root;

			while (*ptr)
			{
				if ((*ptr)->key == k)
				{
					return previous;
				}
				else if ((*ptr)->key > k)
				{
					previous = ptr;
					ptr = &((*ptr)->left);
				}
				else
				{
					previous = ptr;
					ptr = &((*ptr)->right);
				}
			}

			return previous;
		}

		Node** findSubtreeMinimum(Node** node)
		{
			if (*node)
			{
				if ((*node)->left)
				{
					return findSubtreeMinimum(&((*node)->left));
				}
			}

			return node;
		}

		Node** findSubtreeMaximum(Node** x)
		{
			if (*node)
			{
				if ((*node)->right)
				{
					return findSubtreeMinimum(&((*node)->right));
				}
			}

			return node;
		}

		void swap(Node* x, Node* y)
		{
			if (!x->parent)
			{
				root = y;
			}
			else if (x->isLeftChild())
			{
				x->parent->left = y;
			}
			else
			{
				x->parent->right = y;
			}

			if (y)
			{
				y->parent = x->parent;
			}
		}

		void copyTree(const BinarySearchTree& b)
		{
			root = 0;

		    if (b.root)
		    {
		        root = new Node;
		        copyNode(root, b.root);
		    }
		}

        void copyNode(Node* &node, const Node* other)
        {
        	node->key = other->key;
		    node->value = other->value;

		    if (other->left)
		    {
		        node->left = new Node;
		        node->left->parent = node;
		        copyNode(node->left, other->left);
		    }

		    if (other->right)
		    {
		        node->right = new Node;
		        node->right->parent = node;
		        copyNode(node->right, other->right);
		    }
        }

        void deleteTree()
        {
        	deleteNode(root);
        }

        void deleteNode(Node* node)
        {
        	if (!node)
		        return;

		    if (node->left)
		        deleteNode(node->left);

		    if (node->right)
		        deleteNode(node->right);

		    delete node;
        }
};

#endif
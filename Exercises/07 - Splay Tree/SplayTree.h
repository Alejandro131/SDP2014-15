#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

template <typename K, typename V>
class SplayTree
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

		SplayTree()
		{
			root = 0;
		}

        ~SplayTree()
        {
		    deleteTree();
		}

        SplayTree(const SplayTree& s)
        {
        	copyTree(s);
        }

        SplayTree& operator = (const SplayTree& s)
        {
        	if (this != &s)
		    {
		        deleteTree();
		        copyTree(s);
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

				splay(*ptr);

				return true;
			}

			return false;
		}

		void remove(K& key)
		{
			Node** ptr = lookup(k);

			if (*ptr)
			{
				splay(*ptr);
				
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

			int counter = 0;

			while (*ptr)
			{
				if ((*ptr)->key == k)
				{
					cout << "took " << counter << " steps to find this element.\n";
					return ptr;
				}
				else if ((*ptr)->key > k)
					ptr = &((*ptr)->left);
				else
					ptr = &((*ptr)->right);

				counter++;
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

		void rotateLeft(Node* x)
		{
			Node *y = x->right;

			x->right = y->left;

			if (y->left)
			{
				y->left->parent = x;
			}

			y->parent = x->parent;

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

			y->left = x;
			x->parent = y;
		}

		void rotateRight(Node* x)
		{
			Node *y = x->left;

			x->left = y->right;

			if (y->right)
			{
				y->right->parent = x;
			}

			y->parent = x->parent;

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

			y->right = x;
			x->parent = y;
		}

		void splay(Node *x)
		{

			while (x->parent)
			{
				if (!x->parent->parent)
				{
					if (x->isLeftChild())
					{
						rotateRight(x->parent);
					}
					else
					{
						rotateLeft(x->parent);
					}
				}
				else if (x->isLeftChild() && x->parent->isLeftChild())
				{
					rotateRight(x->parent->parent);
					rotateRight(x->parent);
				} 
				else if (x->isRightChild() && x->parent->isRightChild())
				{
					rotateLeft(x->parent->parent);
					rotateLeft(x->parent);
				}
				else if (x->isLeftChild() && x->parent->isRightChild())
				{
					rotateRight(x->parent);
					rotateLeft(x->parent);
				}
				else
				{
					rotateLeft(x->parent);
					rotateRight(x->parent);
				}
			}
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

		void copyTree(const SplayTree& s)
		{
			root = 0;

		    if (s.root)
		    {
		        root = new Node;
		        copyNode(root, s.root);
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
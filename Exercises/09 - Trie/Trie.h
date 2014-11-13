#ifndef TRIE_H
#define TRIE_H

#include "BinarySearchTree.h"
#include <string.h>

template <typename T>
struct Node
{
	BinarySearchTree<char, Node*> children;
	T value;
	bool isEnd;

	Node()
	{
		isEnd = false;
	}

	Node(T& val)
	{
		isEnd = false;
		value = val;
	}
};

template <typename T>
class Trie
{
	public:
		Trie()
		{
			root = new Node<T>();
		}

		~Trie()
		{
			deleteTrie();
		}

		Trie(const Trie& t)
		{
			copyTrie();
		}

		Trie& operator = (const Trie& t)
		{
			if (this != &t)
			{
				deleteTrie();
				copyTrie();
			}
			return *this;
		}

		bool insert(const char* word, const T& value)
		{
			Node<T>* current = root;
			Node<T>* next;

			for (int i = 0; i < strlen(word); i++)
			{
				if (current->children.find(word[i], next))
				{
					current = next;
				}
				else
				{
					next = new Node<T>();

					if (!next)
						return false;

					current->children.insert(word[i], next);
					current = next;
				}
			}

			current->isEnd = true;
			current->value = value;
			return true;
		}

		bool find(const char* word, T& value)
		{
			Node<T>* current = root;
			Node<T>* next;

			for (int i = 0; i < strlen(word); i++)
			{
				if (current->children.find(word[i], next))
				{
					current = next;
				}
				else
				{
					return false;
				}
			}

			if (current->isEnd)
			{
				value = current->value;
				return true;
			}
			else
				return false;
		}

	private:
		Node<T>* root;

		void copyTrie(const Trie& t)
		{
			//
		}

		void deleteTrie()
		{
			//
		}
};

#endif
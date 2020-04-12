#pragma once

#include "enum_define.h"
#include <iostream>

template <typename key, typename data>
struct PAIR{
	key first;
	data second;
};



template <typename key, typename data>
PAIR<key, data> makepair(const key& first, const data& second)
{
	PAIR<key, data>pair = { first, second };
	
	return pair;
}

template <typename key, typename data>
struct MapNode
{
private:
	PAIR<key, data> pair;
	MapNode* arraynode[BSTNODE_TYPE::END];

public:

	template <typename key, typename data> friend class MAP;

	MapNode*& Get(BSTNODE_TYPE _eType) {
		return arraynode[_eType];
	}
	bool IsRoot() {
		if (arraynode[BSTNODE_TYPE::BST_PARENT] == nullptr)
			return true;
		return false;
	}

	bool IsLeaf() {
		if (arraynode[BST_LEFTCHILD] == nullptr && arraynode[BST_RIGHTCHILD] == nullptr)
			return true;
		return false;
	}

	bool IsLeftChild() {
		if (IsRoot())
			return false;
		if (arraynode[BST_PARENT]->arraynode[BST_LEFTCHILD] == this)
			return true;
		return false;
	}

	bool IsRightChild()
	{
		if (IsRoot())
			return false;
		if (arraynode[BST_PARENT]->arraynode[BST_RIGHTCHILD] == this)
			return true;
		return false;
	}

	bool HasParent()
	{
		if (arraynode[BST_PARENT])
			return true;
		return false;
	}

	bool HasRightChild()
	{
		if (arraynode[BST_RIGHTCHILD])
			return true;
		return false;
	}

	bool HasLeftChild()
	{
		if (arraynode[BST_LEFTCHILD])
			return true;
		return false;
	}

	MapNode()
		: pair()
		, arraynode{}
	{}

	MapNode<key, data>(const PAIR<key,data>& _pair)
		: pair(_pair)
		, arraynode{ nullptr , nullptr , nullptr }
	{}

	MapNode<key,data>(const PAIR<key, data>& _pair, MapNode* _pLeft = nullptr, MapNode* _pRight = nullptr, MapNode* _pParent = nullptr)
		: pair(_pair)
		, arraynode{ _pLeft , _pRight , _pParent }
	{}
};

template <typename key,typename data>
class MAP
{
private:
	MapNode<key, data>* root;

public:
	class iterator;

public:
	void insert(const PAIR<key, data>& _pair);
	iterator find(const key& k);
//	iterator erase(const iterator& _iter); // 반환타입이 iterator 인 이유 : 삭제된 데이터 다음(중위 후속자) 를 반환
//	iterator begin();
//	iterator end();

	MAP()
		:root(nullptr)
	{}
private:
	MapNode<key, data>* find_node(const key& key);
public:
	class iterator
	{
	private :
		MAP<key, data>* iterator_map;
		MapNode<key, data>* target;

	public :
		iterator()
		: iterator_map(nullptr)
		, target(nullptr)
		{}
		iterator(MAP<key, data> *map, MapNode<key, data> *tar)
		: iterator_map(map)
		, target(tar)
		{}
	};
};

template <typename key,typename data>
void MAP<key, data>::insert(const PAIR<key, data>& _pair)
{
	MapNode<key, data>* newnode = new MapNode<key, data>(_pair,nullptr, nullptr, nullptr);

	if (nullptr == this->root)
	{
		//아직 아무것도 넣지 않았다!(첫번째 데이터가 들어온다!)
		this->root = newnode;
	}
	else
	{
		//이미 데이터가 한개 이상 있는 경우
		MapNode<key, data>* search = this->root;
		MapNode<key, data>* parent = {};
		while (nullptr != search)
		{

			parent = search;
			if (_pair.first < search->pair.first)
			{
				search = search->Get(BST_LEFTCHILD);
			}
			else
			{
				search = search->Get(BST_RIGHTCHILD);
			}
		}

		if (_pair.first < parent->pair.first)
		{
			parent->Get(BST_LEFTCHILD) = newnode;
		}
		else
		{
			parent->Get(BST_RIGHTCHILD) = newnode;
		}
	}

}

template<typename key,typename data>
MapNode<key, data>* MAP<key, data>::find_node(const key& k)
{
	MapNode<key, data>* search = root;

	while (search != nullptr)
	{
		if (k == search->pair.first)
		{
			return search;
		}

		if (k > search->pair.first)
		{
			search = search->arraynode[BST_RIGHTCHILD];
		}
		else
		{
			search = search->arraynode[BST_LEFTCHILD];
		}
	}

	printf("해당 값을 찾을 수가 없습니다.(return nullptr) \n");
	return nullptr;
}


template <typename key,typename data>
typename MAP<key, data>::iterator MAP<key, data>::find(const key& k)
{
	MapNode<key, data>* temp = find_node(k);

	if (temp != nullptr)
	{
		printf("값 찾앗음 \n");
	}

	return iterator(this, temp);
}

// erase iterator 4/13일까지 완성 + redblack tree
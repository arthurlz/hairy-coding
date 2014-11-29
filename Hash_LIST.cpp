// Hash.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define HASH_LENGTH 13

typedef struct HashNode
{
	int addr;
	HashNode* next;
	string key;
	HashNode() {}
	HashNode(int a, HashNode* n, string str) : addr(a), next(n), key(str) {}
}HashNode, *P_HashNode;


typedef struct HashList
{
	P_HashNode HashArray[HASH_LENGTH];

}HashList, *P_HashList;

void init_hash_list(HashList& hasharr)
{
	for (int i = 0; i < HASH_LENGTH; i++)
	{
		hasharr.HashArray[i] = new HashNode(0, NULL, "");
	}
}

void delete_hash_list(HashList& hasharr)
{
	for (int i = 0; i < HASH_LENGTH; i++)
	{
		delete hasharr.HashArray[i];
		hasharr.HashArray[i] = nullptr;
	}
}
bool delete_key(string key, HashList& hashlist)
{
	int ocd = 0;
	for (size_t i = 0; i < key.length(); i++)
	{
		if (islower(key[i]))
			ocd += key[i] - 'a' + 1;
		else
			ocd += key[i] - 'A' + 1;
	}

	int pos = ocd % 13;

	if (hashlist.HashArray[pos]->key == "")
		return false;
	else
	{
		if (hashlist.HashArray[pos]->key == key)
		{
			hashlist.HashArray[pos]->key = "";
			return true;
		}
		P_HashNode t = hashlist.HashArray[pos]->next;
		P_HashNode p = hashlist.HashArray[pos];
		while (t)
		{
			if (t->key == key)
			{
				delete t;
				p->next = nullptr;
				return true;
			}
			else
			{
				p = t;
				t = t->next;
				
			}
		}
	}
}

void hash_func(string key, HashList& hashlist)
{
	int ocd = 0;
	for (size_t i = 0; i < key.length(); i++)
	{
		if (islower(key[i]))
			ocd += key[i] - 'a' + 1;
		else
			ocd += key[i] - 'A' + 1;
	}

	int pos = ocd % 13;
	cout << pos << endl;

	if (hashlist.HashArray[pos]->next)
	{
		hashlist.HashArray[pos]->next = new HashNode(pos, NULL, key);
	}
	else
	{
		hashlist.HashArray[pos]->key = key;
		hashlist.HashArray[pos]->addr = pos;
	}

}

/*
HashList hli;
init_hash_list(hli);
hash_func("are", hli);
hash_func("soon", hli);

hash_func("ayumi", hli);
delete_key("ayumi", hli);

if (hli.HashArray[4]->next)
cout << " hehe ";
else
cout << "bingo";

delete_hash_list(hli);

int _tmain(int argc, _TCHAR* argv[])
{

	system("pause");
	return 0;
}
*/

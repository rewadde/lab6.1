#include <iostream> 
#include <fstream> 
#include <list> 
#include <vector>

using namespace std;
const int N_SEG = 12; // 1500 кол-во сегментов 
const int KEY_LEN = 7; // длина ключа

struct Key
{
	char key[KEY_LEN + 1];
	Key() {}
	Key(const char* s)
	{
		for (int i = 0; i < KEY_LEN + 1; i++)
			key[i] = s[i];
	}

	// Оператор для сравнения ключей посимвольно 
	bool operator==(Key k2)
	{
		for (int i = 0; i < KEY_LEN; i++)
			if (this->key[i] != k2.key[i])
				return false;
		return true;
	}

	void gen()
	{
		for (int i = 0; i < 3; i++)
			key[i] = '0' + rand() % 10;
		key[3] = 'A' + rand() % 26;
		for (int i = 4; i < 6; i++)
			key[i] = '0' + rand() % 10;
		key[6] = 0; // для разделения ключей  
	}
};

typedef  vector<list<Key>> HashTable;
//using HashTable = vector<list<Keys>>; 

int hashFunc(Key k)
{
	int sum = 0;
	for (int i = 0; i < KEY_LEN; i++)
		sum += k.key[i] * k.key[i];
	return sum % N_SEG;
}

void print(const HashTable& ht)
{
	cout << "Hash Table:" << endl;
	for (int i = 0; i < ht.size(); i++)
	{
		cout << i << "\t";
		auto keys = ht[i];
		for (auto it = keys.begin(); it != keys.end(); ++it)
		{
			cout << it->key << " ";
		}
		cout << endl;
	}
}

bool find(const HashTable& ht, Key key)
{
	int i = hashFunc(key); // номер сегмента в таблице 
	auto keys = ht[i]; // список в i-ом сегменте хеш-таблицы 
	// перебираю все ключи в списке 
	for (auto it = keys.begin(); it != keys.end(); ++it)
	{
		if (*it == key)
			return true;
	}
	return false;
}

void insert(HashTable& ht, Key key)
{
	if (!find(ht, key))
	{
		int i = hashFunc(key); // номер сегмента в таблице 
		//  
		cout << "insert: i=" << i << endl;
		ht[i].push_back(key); // добавляем ключ в конец списка в i-ом сегменте 
	}
}

void remove(HashTable& ht, Key key)
{
	int i = hashFunc(key); // номер сегмента в таблице 
	ht[i].remove(key); // удаление элемента из списка 
}

void stat(const HashTable& ht)
{
	ofstream fout("stat.txt");
	for (int i = 0; i < ht.size(); i++)
	{
		auto keys = ht[i];
		fout << i << "\t" << keys.size() << endl;
	}
	fout.close();
}

void mainmenu()
{
	cout << "1. Generated hash table" << endl;
	cout << "2. Print hash table" << endl;
	cout << "3. Delete key" << endl;
	cout << "4. Find key" << endl;
	cout << "5. Print statistics hash table" << endl;
	cout << "9. Exit menu" << endl;
}

int main()
{
	int choose = 0;
	HashTable hashTable(N_SEG);
	do
	{
		mainmenu();

		cout << "Choose item menu: ";
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
			for (int i = 0; i < 30; i++)
			{
				Key k;
				k.gen();
				insert(hashTable, k);
			}
			break;
		}
		case 2:
		{
			print(hashTable);
			break;
		}
		case 3:
		{
			cout << "Input key to delete: ";
			char buf[7];
			cin >> buf;

			// проверка ключа 
			Key k(buf);
			remove(hashTable, k);
			print(hashTable);
			break;
		}
		case 4:
		{
			cout << "Input key to find: ";
			char buf[7];
			cin >> buf;

			// проверка ключа 
			Key k(buf);
			bool res = find(hashTable, Key(buf)); // true, false 
			cout << std::boolalpha << res << endl;
			break;
		}
		case 5:
		{
			stat(hashTable);
			break;
		}
		}

	} while (choose != 9);

	system("pause");

	return 0;
}

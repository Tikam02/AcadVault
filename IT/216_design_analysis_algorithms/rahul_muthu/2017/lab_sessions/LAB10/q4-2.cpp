/*
Name: Mohamed Shadab
ID: 201601211
C++ Program to Implement Hash Tables with Quadratic Probing
*/
#include <iostream>
#include <cstdlib>
#define MIN_TABLE_SIZE 10
using namespace std;
/*
* Node Type Declaration
*/
enum EntryType {Legitimate, Empty, Deleted};
/*
* Node Declaration
*/
struct HashNode
{
  int element;
  enum EntryType info;
};
/*
* Table Declaration
*/
struct HashTable
{
  int size;
  HashNode *table;
};
/*
* Returns whether n is prime or not
*/
bool isPrime (int n)
{
  if (n == 2 || n == 3)
  return true;
  if (n == 1 || n % 2 == 0)
  return false;
  for (int i = 3; i * i <= n; i += 2)
  if (n % i == 0)
  return false;
  return true;
}
/*
* Finding next prime size of the table
*/
int nextPrime(int n)
{
  if (n <= 0)
  n == 3;
  if (n % 2 == 0)
  n++;
  for (; !isPrime( n ); n += 2);
  return n;
}
/*
* Function To Generate Hash
*/
int HashFunc(int key, int size)
{
  return key % size;
}
/*
* Function to Initialize Table
*/
HashTable *initializeTable(int size)
{
  HashTable *htable;
  if (size < MIN_TABLE_SIZE)
  {
    cout<<"Table Size Too Small"<<endl;
    return NULL;
  }
  htable = new HashTable;
  if (htable == NULL)
  {
    cout<<"Out of Space"<<endl;
    return NULL;
  }
  htable->size = nextPrime(size);
  htable->table = new HashNode [htable->size];
  if (htable->table == NULL)
  {
    cout<<"Table Size Too Small"<<endl;
    return NULL;
  }
  for (int i = 0; i < htable->size; i++)
  {
    htable->table[i].info = Empty;
    htable->table[i].element = NULL;
  }
  return htable;
}
/*
* Function to Find Element at a key
*/
int Find(int key, HashTable *htable)
{
  int pos = HashFunc(key, htable->size);
  int collisions = 0;
  while (htable->table[pos].info != Empty &&
    htable->table[pos].element != key)
    {
      pos = pos + 2 * ++collisions -1;
      if (pos >= htable->size)
      pos = pos - htable->size;
    }
    return pos;
  }
  /*
  * Function to Insert Element into a key
  */
  void Insert(int key, HashTable *htable)
  {
    int pos = Find(key, htable);
    if (htable->table[pos].info != Legitimate)
    {
      htable->table[pos].info = Legitimate;
      htable->table[pos].element = key;
    }
  }
  /*
  * Function to Rehash the Table
  */
  HashTable *Rehash(HashTable *htable)
  {
    int size = htable->size;
    HashNode *table = htable->table;
    htable = initializeTable(2 * size);
    for (int i = 0; i < size; i++)
    {
      if (table[i].info == Legitimate)
      Insert(table[i].element, htable);
    }
    free(table);
    return htable;
  }
  /*
  * Function to Retrieve Hash Table
  */
  void Retrieve(HashTable *htable)
  {
    for (int i = 0; i < htable->size; i++)
    {
      int value = htable->table[i].element;
      if (!value)
      cout<<"Position: "<<i + 1<<" Element: Null"<<endl;
      else
      cout<<"Position: "<<i + 1<<" Element: "<<value<<endl;
    }

  }
  /*
  * Main Contains Menu
  */
  int main()
  {
    int value, size, pos, i = 1;
    int choice;
    HashTable *htable;
    while(1)
    {
      cout<<"\n----------------------"<<endl;
      cout<<"Operations on Quadratic Probing"<<endl;
      cout<<"\n----------------------"<<endl;
      cout<<"1.Initialize size of the table"<<endl;
      cout<<"2.Insert element into the table"<<endl;
      cout<<"3.Display Hash Table"<<endl;
      cout<<"4.Rehash The Table"<<endl;
      cout<<"5.Exit"<<endl;
      cout<<"Enter your choice: ";
      cin>>choice;
      switch(choice)
      {
        case 1:
        cout<<"Enter size of the Hash Table: ";
        cin>>size;
        htable = initializeTable(size);
        cout<<"Size of Hash Table: "<<nextPrime(size);
        break;
        case 2:
        if (i > htable->size)
        {
          cout<<"Table is Full, Rehash the table"<<endl;
          continue;
        }
        cout<<"Enter element to be inserted: ";
        cin>>value;
        Insert(value, htable);
        i++;
        break;
        case 3:
        Retrieve(htable);
        break;
        case 4:
        htable = Rehash(htable);
        break;
        case 5:
        exit(1);
        default:
        cout<<"\nEnter correct option\n";
      }
    }
    return 0;
  }

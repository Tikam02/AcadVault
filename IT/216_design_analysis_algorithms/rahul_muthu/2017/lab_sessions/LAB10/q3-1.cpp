/*
Name: Mohamed Shadab
ID: 201601211
C++ Program To Implement Direct Addressing Tables
 */
 #include<iostream>
 #include<cstdlib>
 #include<string>
 #include<cstdio>
 using namespace std;

 /*
  * Table Declaration
  */
 struct table
 {
     string english;
     int key;
     table()
     {}
     table( int k, string e )
     {
         english=e;
         key = k;
     }
 };

 /*
  * Insertion of element at a key
  */
 void INSERT( table T[], table x )
 {
     T[ x.key ] = x;
 }

 /*
  * Deletion of element at a key
  */
 void DELETE( table T[], table x )
 {
     T[ x.key ] = table(0, "");
 }

 /*
  * Searching of element at a key
  */
 table SEARCH( table T[], int k )
 {
     return T[ k ];
 }

 /*
  * Main Contains Menu
  */
 int main()
 {
     int i, key, ch;
     string str;
     table T[65536];
     table x;
     for(i = 0; i < 65536;i++)
         T[i] = table(0,"");
     while (1)
     {
         cout<<"\n-------------------------------------"<<endl;
         cout<<"\nOperations on Direct Addressing Table"<<endl;
         cout<<"\n-------------------------------------"<<endl;
         cout<<"1.Insert element into the key"<<endl;
         cout<<"2.Delete element from the table"<<endl;
         cout<<"3.Search element into the table"<<endl;
         cout<<"4.Exit"<<endl;
         cout<<"Enter your Choice: ";
         cin>>ch;
         switch(ch)
         {
         case 1:
         {
             string str1 = "";
             cout<<"Enter the key value: ";
             cin>>key;
             cout<<"Enter the string to be inserted: ";
             cin.ignore();
             getline(cin, str);
             INSERT(T, table(key, str));
             break;
         }
         case 2:
             cout<<"Enter the key of element to be deleted: ";
             cin>>key;
             x = SEARCH(T, key);
             DELETE(T, x);
             break;
         case 3:
 	    cout<<"Enter the key of element to be searched: ";
             cin>>key;
             x = SEARCH(T, key);
             if (x.key == 0)
             {
                 cout<<"No element inserted at the key"<<endl;
                 continue;
             }
             cout<<"Element at key "<<key<<" is-> ";
             cout<<"\""<<x.english<<"\""<<endl;
             break;
         case 4:
             exit(1);
         default:
             cout<<"Wrong Choice"<<endl;
         }
     }
     return 0;
 }

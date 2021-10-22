#include <iostream>
using namespace std;

struct product
{
	int type;
	int amount;
	union id
	{
		long id_long;
		char id_char[20];
	}id1;
};
//Using union
int main() {
	product p;
    cout << "id len:" << sizeof(p.id1) << endl;
	p.id1.id_long = 123456; //store a long number
	cout << p.id1.id_long<<endl; //print 123456
	cin>>p.id1.id_char; //store a char array, long value is lost
	cout <<"p.id1.id_char: "<< p.id1.id_char<<endl;
	cout << "p.id1.id_long: " << p.id1.id_long;
}
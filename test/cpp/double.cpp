#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <math.h>
using namespace std;


int main()
{
    //double比较大小
	//double比较大小
	const double eps=1e-6;//1的负6次方	
    const double min = 1e-6;
    const double max = 1.00;
	double dNum1=0.0, dNum2=0.0;

	cout<<"输入dNum1和dNum2的值：";
	cin>>dNum1>>dNum2;

	if(dNum1+eps < dNum2)//way1. 判断a是否小于b
		cout << "<" << endl;

	if(dNum1 < dNum2-eps)//way2. 判断a是否小于b
		cout << "<" << endl;

	if(fabs(dNum1-dNum2) < eps)//判断是否相等
		cout << "==" << endl;
    if(dNum1 >= min && dNum1 <= max)
    {
        cout << "dNum1: " << min << " " << dNum1 << " " << max << endl;
    }
    else {
        cout << "dNum1 no range" << endl;
    }

    if(dNum2 >= min && dNum2 <= max)
    {
        cout << "dNum2: " << min << " " << dNum2 << " " << max << endl;
    }
    else {
        cout << "dNum2 no range" << endl;
    }

    cout << dNum1 << " " << dNum2 << endl;

    return 0;
}
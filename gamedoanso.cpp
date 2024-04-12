#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(NULL));
	while (true)
	{

	int somay=1+rand()%100;
	cout <<"Chuong trinh choi game doan so :\n" ;
	cout <<"May da doan so [1...100], moi ban doan :\n";
	int solandoan=0;
	bool iswin=false;
	do {
	int songuoi;
	cin>>songuoi;
	solandoan++;
	cout <<"Ban doan lan thu " << solandoan << endl;
	if (songuoi==somay)
	{
		cout <<"Ha ha ban tai that, so may = " << somay << endl;
		iswin=true;
		break;// thang va ngung vong lap
	}
	else if (songuoi>somay){
		cout <<"ban doan sai, so nguoi > so may "<<endl;
		
	}
	else 
	{
		cout<<"ban doan sai ,so nguoi < so may "<<endl;
	}
	if (solandoan==7)
	{
		break;
	}
	
	}while(true);
	if (iswin !=true)
	{
		cout <<"Game over"<< endl;
		cout <<"So cua may = "<<somay<<endl;
	}
	cout <<"Tiep khong thim ? (c/k) :";
	char c;
	cin>>c;
	if (c=='k')
	{
		break;
	}
}
cout <<"Goodbye!";
	
return 0;	
}
#include<stdio.h>
#include<math.h>
#include<iostream>
using namespace std;
int songuyento(int n){
	for(int i=2; i<=sqrt(n); i++){
		if(n%i==0){
			return 0;
		} 
	}
	return 1;
} 
int soNUAnguyento(int n){
	for(int i=2; i<n; i++ ){
		for(int j=2; j<n; j++){
			if(songuyento(i)&&songuyento(j)==1){
				if(i*j==n){
					return 1;
				}
			}
		}
	}return 0;
}
int main(){
	int a[100], blumNumber[100];
	int count=0;
	for(int i=0;i<100;i++){
		a[i]=i+1;
	}
	for(int i=0;i<100;i++){
		if(soNUAnguyento(a[i])==1){
			blumNumber[count++]=a[i];	 
		}	
	}
	for(int i=0;i<count;i++){
		for(int j=0;j<count;j++){
			int sum=blumNumber[j]+blumNumber[i];
			for(int k=0;k<count;k++){
				if(sum==blumNumber[k]){  //tong 2 so blum bang so 1 blum trong day blumNumber
					cout << "(" << blumNumber[i] << ", " << blumNumber[j] << ")" << endl;
				}
			}
		}		
	}
	int M;
	bool check=false;
	cout<<"nhap M:";
	cin>>M;
	for(int i=0;i<count;i++){
		if(M==blumNumber[i]){
			check=true;//cout<<"M co ton tai trong day Blum"<< endl;
		} 
	}
	if(check==true){
		cout<<"M co ton tai trong day Blum"<< endl;
	} else cout<<"khong ton tai";	 
}
    return 0;
}

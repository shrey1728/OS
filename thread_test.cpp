#include<iostream>
#include<thread>

using namespace std;

int n=5;
int a[5];
int i=0,j=0;
static int mutex=1;
static int empty=5;
int full=0;

void wait(int *S){
	while((*S)<=0);
	//cout<<"jhgj"<<*S;
	(*S)--;
	//cout<<"lkj"<<*S;
}

void signal(int *S){
	(*S)++;
}

void prod(){
	do{
    	int item=i;
    	wait(&empty);
    	wait(&mutex);
    	a[i]=item;
    	i=(i+1)%n;
    	cout<<"Item produced : "<<item<<endl;
		signal(&mutex);
		signal(&full);
		//<<empty<<full
	}while(1);
}

void cons(){
	do{
    	int item;
		wait(&full);
		wait(&mutex);
		item=a[j];
		j=(j+1)%n;
		cout<<"Item consumed : "<<item<<endl;
		signal(&mutex);
		signal(&empty);
		
	}while(1);
}

int main(){
	thread t(prod);
	thread p(cons);
    t.join();
    p.join();
	return 0;
}

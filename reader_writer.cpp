#include<iostream>
#include<thread>
#include<queue>

using namespace std;

queue <char> q;
int nreaders=0;
static int mutex=1;
static int nrcount=1;
static int book=1;

void wait(int *S){
	while((*S)<=0);
	(*S)--;
}

void signal(int *S){
	(*S)++;
}

void reader(){
	do{
    	q.push('r');
    	wait(&nrcount);
    	if(nreaders=0)
			wait(&book);
		nreaders++;
		char item=q.front();
		q.pop();
		signal(&nrcount);
		cout<<"reading"<<item<<endl;
		wait(&nrcount);
		nreaders--;
		if(nreaders==0)
			signal(&book);
		signal(&nrcount);
	}while(1);
}

void writer(){
	do{
    	q.push('w');
		wait(&book);
		char item=q.front();
		q.pop();
		cout<<"writing : "<<item<<endl;
		signal(&book);
		
	}while(1);
}

int main(){
	thread t(reader);
	thread p(writer);
    t.join();
    p.join();
	return 0;
}

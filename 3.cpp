#include <bits/stdc++.h>
using namespace std;
int QUANTA=2;
struct task{
	string name;
    int id;
    int burst;
    int waitingTime;
    int remaningTime;
    int turnAroundTime;
    int responseTime;

};

bool mycompare(task &a,task &b){
	return a.burst<b.burst;
}
void calWaitingTime(vector<task>  &taskList,int QUANTA){
	int t=0;
	while(1){
		bool allFinished=true;
		for(int i=0;i<taskList.size();i++)
			if(taskList[i].remaningTime >0){
				allFinished=false;
				if(taskList[i].responseTime == -1)
					taskList[i].responseTime=t;
				if(taskList[i].remaningTime > QUANTA){
					t +=QUANTA;
					taskList[i].remaningTime -=QUANTA;
				}

				else{
					t += taskList[i].remaningTime;
					taskList[i].remaningTime=0;
					taskList[i].waitingTime = t-taskList[i].burst;
				}

			}
		if(allFinished)
			break;	
	}

}

void calTurnAroundTime(vector<task>  &taskList){
	for(int i=0;i<taskList.size();i++)
		taskList[i].turnAroundTime = taskList[i].waitingTime+taskList[i].burst; 
}

void roundRobin(vector<task>  &taskList,int QUANTA){
	calWaitingTime(taskList,QUANTA);
	calTurnAroundTime(taskList);
}



void oldalgo(vector<task>  &taskList){
	sort(taskList.begin(),taskList.end(),mycompare);
	double averageburst=0;
	for(int i=0;i<taskList.size();i++)
		averageburst +=taskList[i].burst;
	averageburst = (double) averageburst/taskList.size();
	QUANTA = averageburst +taskList[0].burst;
	cout<<"QUANTA ="<<QUANTA<<endl;
	int t=0;
	while(1){
		bool allFinished=true;
		for(int i=0;i<taskList.size();i++)
			if(taskList[i].remaningTime >0){
				allFinished=false;
				if(taskList[i].responseTime == -1)
					taskList[i].responseTime=t;
				if(taskList[i].remaningTime > QUANTA){
					t +=QUANTA;
					taskList[i].remaningTime -=QUANTA;
				}

				else{
					t += taskList[i].remaningTime;
					taskList[i].remaningTime=0;
					taskList[i].waitingTime = t-taskList[i].burst;
				}

			}
		if(allFinished)
			break;	
	}
	calTurnAroundTime(taskList);

}

void myalgo(vector<task>  &taskList){
	sort(taskList.begin(),taskList.end(),mycompare);
	double averageburst=0;
	for(int i=0;i<taskList.size();i++)
		averageburst +=taskList[i].burst;
	averageburst = (double) averageburst/taskList.size();
	QUANTA = averageburst +taskList[0].burst;
	cout<<"QUANTA ="<<QUANTA<<endl;
	int t=0;
	while(1){
		bool allFinished=true;
		for(int i=0;i<taskList.size();i++)
			if(taskList[i].remaningTime >0){
				allFinished=false;
				if(taskList[i].responseTime == -1)
					taskList[i].responseTime=t;
				if(taskList[i].remaningTime > QUANTA){
					t +=QUANTA;
					taskList[i].remaningTime -=QUANTA;
					if(taskList[i].remaningTime < QUANTA)
						goto there;
				}

				else{
					there:
					t += taskList[i].remaningTime;
					taskList[i].remaningTime=0;
					taskList[i].waitingTime = t-taskList[i].burst;
				}

			}
		if(allFinished)
			break;	
	}
	calTurnAroundTime(taskList);

}


int main(){
	int n;
	vector<task> taskList;
	task t0;
	int id=0;
	while(cin>>t0.name>>t0.burst){
		t0.remaningTime = t0.burst;
		t0.id=id++;
		t0.responseTime=-1;
		taskList.push_back(t0);
	}
	n=id;


	roundRobin(taskList,QUANTA);
	
	//myalgo(taskList);
	
	double averageWaitingTime=0;
	double averageTurnAroundTime=0;
	double averageResponseTime=0;
	for(int i=0;i<n;i++){
		averageWaitingTime += taskList[i].waitingTime;
		averageTurnAroundTime += taskList[i].turnAroundTime;
		averageResponseTime += taskList[i].responseTime;
	//	cout<<" P"<<taskList[i].id<<" "<<taskList[i].responseTime<<" "<<taskList[i].waitingTime<<" "<<taskList[i].turnAroundTime<<endl;
	}

	averageWaitingTime = (double)averageWaitingTime/n;
	averageTurnAroundTime = (double) averageTurnAroundTime/n;
	averageResponseTime = (double) averageResponseTime/n;
	//cout<<"averageResponseTime = "<<averageResponseTime<<endl;
	cout<<"averageWaitingTime = "<<averageWaitingTime<<endl;
	cout<<"averageTurnAroundTime = "<<averageTurnAroundTime<<endl;



	return 0;
	}

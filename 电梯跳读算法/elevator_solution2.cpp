// The second method is shown below:
// first, I suppose that the stop floor is i, the peoples that below the ith floor is #N1
// the peoples that stop in the ith floor is #N2, the peoples that above the ith floor 
// is #N3.
// then, if we set the stop floor is i+1, so the each of the N2 and N1 should plus one, the each
// of the N3 should minus one, similar to the choice of i+1, if we set the stop floor is i-1,
// the each of the N3 and N2 should plus one and the each of N1 should minus one.
// According this law when N1>N2+N3 we should choose the i-1 and when N1+N2<N3 we should choost the i+1

#include <iostream>
using namespace std;

int get_targetfloor(int nPerson[],int length){
	int N=length-1;
	int T=0;
	int N1=0;
	int N2=nPerson[1];
	int N3=0;
	int floor=1;
	for(int i=2;i<=N;i++){
		T+=nPerson[i]*(i-1);
		N3+=nPerson[i];
	}
	for(int i=2;i<=N;i++){
		if(N1+N2<=N3){
			T+=N1+N2-N3;
			N1+=N2;
			N2=nPerson[i];
			N3-=nPerson[i];
			floor=i;
		}
		else
			break;
	}
	return floor;
}
int main(){
	int nPerson[]={0,4,3,6,7};

	int targetfloor=get_targetfloor(nPerson,sizeof(nPerson)/sizeof(int));
	cout<<"The num of the best floor is :"<<targetfloor<<endl;

	return 1;
}
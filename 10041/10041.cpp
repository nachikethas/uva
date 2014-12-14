// Find the median.
//
#include<iostream>
#include<list>
#include<cmath>
#include<algorithm>

using namespace std;

int main(){
	int numTests;
	cin>>numTests;

	list<int> s;

	int r,tmp;
	float med;
	int sum1, sum2;
	for (int i=0; i<numTests; i++){
		cin>>r;
		for (int j=0; j<r; j++){
			cin>>tmp;
			s.push_back(tmp);
		}
		s.sort();
		
		if (r%2 ==0)
			med = r/2 - 0.5;
		else
			med = (r-1)/2.0;
		
		int j=0; 
		sum1 = 0;
		sum2 = 0;
		for (auto it = s.begin(); it != s.end(); it++){
			if (j<med)
				sum1 += (*it);
			if (j>med)
				sum2 += (*it);
			j++;
		}
		cout<<(sum2-sum1)<<endl;
		s.clear();
	}
}

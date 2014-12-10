#include<iostream>
#include<sstream>
#include<string>
#include<stack>
#include<map>

using namespace std;

int main(void) {
	stringstream ss;
	string inp;

	while(getline(cin,inp)){
		ss.clear();
		ss.str("");
		ss << inp;
		stack<int> nums;
		map<int,char> difs;
		int ti,n;
		bool jolly = false;

		// Push all numbers into a stack
		ss >> n;
		while(ss >> ti){
			nums.push(ti);
		}

		int prev = nums.top();
		nums.pop();
		while(!nums.empty()){
			int cur = nums.top();
			nums.pop();
			int dif = cur - prev;
			if (dif<0){
				dif = -1*dif;
			}
			if ((dif == 0) || (dif>=n)) break;

			difs[dif] = 'T';
			prev = cur;
		} // while(!nums.empty())

		if (difs.size() == n-1){
			jolly = true;
		}
		
		if (jolly) {
			cout<<"Jolly\n";
		} else {
			cout<<"Not jolly\n";
		}
	} // while(getline(cin,inp))
	return 0;
} // main

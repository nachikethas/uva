#include<iostream>
#include<stack>
#include<sstream>
#include<map>

using namespace std;

int testcase(void) {
	int N,P;

	cin >> N;
	cin >> P;

	stack<int> h;
	map<int,bool> days;

	for (int i=0; i<P; i++) {
		int tmp;
		cin >> tmp;
		h.push(tmp);
	} // for (int i=0; i<P; i++)

	while (!h.empty()) {
		int cur = h.top();
		h.pop();

		for (int i=0; i*cur <= N; i++) {
			int day = i*cur;
			// No Fridays or Saturdays
			if ( (day % 7 != 6) && (i % 7 != 0)){
				days[day] = true;
			}
		}
	} // while (!h.empty())
	
	cout<<days.size()<<endl;
	return 0;

} // int testcase(void)

int main(void) {
	int T;
	cin >> T;
	for (int i=0; i<T; i++){
		testcase();
	}
	return 0;
}

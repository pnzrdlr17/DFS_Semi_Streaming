#include <iostream>
using namespace std;
#define ll long long

int main(void){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);

	const ll M = 1806067135;
        ll maxNode = 1;

	for (ll i = 0, u; i < M; i++){
		cin>>u;
		maxNode = max(maxNode, u);
		cin>>u;
		maxNode = max(maxNode, u);
	}

	cout<<maxNode;

	return 0;
}

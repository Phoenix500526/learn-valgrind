#include <iostream>
using namespace std;

/* There are two kinds of memory leak, one is forgetting to free 
 * the memroy you allocate, another is for exception returns.
 */

class test
{
public:
	test():ptr(new char[10]){
		throw std::runtime_error("nothing");
	}
	~test(){
		cout << "测试" << endl;
		delete ptr;
	}
private:
	const char* ptr;
};

int main(){
	try{
		test tmp;
	}catch(...){}


	char* ptr = new char[10];
	return 0;
}
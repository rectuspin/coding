#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> stack;

bool isPrior(char c,char d) {
	if (c == '(')
		return true;
	if (c == '*') {
		if (d == '(')
			return false;
		else
			return true;
	}
	if (c == '+'|| c == ')')
		return false;
}

bool isOperand(char c) {
	if (c != '+'&&c!='*'&&c!='('&&c!=')')
		return true;
	return false;
}

string toPostfix(string str,int len) {//주어진 string과 길이 받아옴
	int i, j;
	string newStr; //후위식 string
	char c,t;
	for (i = 0;i < len;i++) {//주어진 문자열에서 한글자씩 받아옴
		c = str[i];
		//피연산자는 그대로 출력.
		if (isOperand(c)) {
			newStr += c;
		}
		//연산자는 stack내 연산자보다 우선순위 높을 때만 push 아니면 그때까지 pop
		else {
			if (stack.empty()) {//
				stack.push_back(string(1, c));
			}
			else {
				//입력된 연산자가 stack 내 연산자보다 우선순위가 높지 않으면 높아질 때까지 pop
				while (!isPrior(c, stack.back()[0])) {
					if (c == ')') {
						// )가 오면 왼쪽괄호가 올 때까지 pop하고 (를 만나면 pop. 출력은 x					
						while (!stack.empty()) {
							if (stack.back()[0] == '(') {
								stack.pop_back();
								break;
							}
							newStr += stack.back();
							stack.pop_back();							
						}
					}
					else {
						newStr += stack.back();
						stack.pop_back();					
					}
					if (stack.empty())
						break;
				}
				//입력된 연산자가 stack 내 연산자보다 우선순위가 높으면 push
				stack.push_back(string(1, c));
			}
		}		
	}
	while (!stack.empty()) {
		
		newStr+=stack.back();
		stack.pop_back();
	}
	return newStr;
}

int postfixCal(string str,int len) {//후위식 계산
	string temp;
	int res,a,b;
	char c;
	for (int i = 0;i < len;i++) {
		temp = "";
		//피연산자 stack에 push	
		if (isOperand(str[i])) {
			temp += str[i];
			stack.push_back(temp);
		}
		//연산자를 만나면 필요한 만큼의 피연산자를 stack에서 pop하여 연산하고 연산결과를 다시 stack에 psuh
		else if (!isOperand(str[i])) {
			a = stoi(stack.back());	stack.pop_back();
			b = stoi(stack.back());	stack.pop_back();

			if (str[i] == '*')
				stack.push_back(to_string(a * b));
			else if (str[i] == '+') stack.push_back(to_string(a + b));
		}
	}

	res = stoi(stack.back());	stack.pop_back();
	return res;
}	

void solve() {
	int res, len;
	string str;
	cin >> len;
	cin >> str;
	str.assign(toPostfix(str,len));
	res = postfixCal(str,len);
	
	cout <<" "<< res << "\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int i;
	for (i = 1;i <= 10;i++) {
		cout << "#" << i;
		solve();
		
	}
	return 0;
}



//#include <iostream>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//vector<char> stack;
//
//bool isPrior(char c) {
//	if (c == '*' || c == '/')
//		if(stack.back()== '+'|| stack.back()=='-'|| stack.back() == '(')
//			return true;		
//	else if (c == '+' || c == '-')
//			if (stack.back() == '(')
//				return true;
//	return false;
//}
//
//bool isOperand(char c) {
//	if (c == '+'||c=='-'||c=='*'||c=='/'||c=='('||c==')')
//		return false;
//	return true;
//}
//
//string toPostfix(string str,int len) {
//	int i, j;
//	string temp="";
//	char c;
//	for (i = 0;i < len;i++) {
//		c = str[i];
//		//피연산자는 그대로 출력.
//		if (isOperand(c))
//			temp += c;
//		else {
//			// )가 오면 왼쪽괄호가 올 때까지 pop하고 (를 만나면 pop. 출력은 x
//			if (c == ')') {
//				while ('(' != stack.back()) {
//					temp += stack.back();
//					stack.pop_back();
//				}
//			}
//			//연산자는 stack 내의 연산자보다 우선순위 높을 때까지 pop하고 그렇게 될 때 push
//			else {
//				while ((isPrior(c))) {
//					temp += stack.back();
//					stack.pop_back();
//				}
//			}
//			stack.push_back(c);
//			
//		}
//	}
//	
//	return temp;
//}
//
//int postfixCal(string str) {
//	string temp;
//	int res,a,b;
//	//피연산자 stack에 push	
//	//연산자를 만나면 필요한 만큼의 피연산자를 stack에서 pop하여 연산하고 연산결과를 다시 stack에 psuh
//	//수식이 끝나면 마지막으로 stack을 pop하여 출력
//
//	return res;
//}
//
//void solve() {
//	int res, len;
//	string str;
//	cin >> len;
//	cin >> str;
//	str.assign(toPostfix(str,len));
//	res = postfixCal(str);
//	
//	cout <<" "<< str << "\n";
//}
//
//int main()
//{
//	ios::sync_with_stdio(false);
//	cin.tie(NULL);
//
//	int i;
//	
//	for (i = 1;i <= 10;i++) {
//		cout << "#" << i;
//		solve();
//		
//	}
//	return 0;
//}
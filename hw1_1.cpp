#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;


string dictfilename = "./step2-master/anagram/words.txt";
vector < string > maketestcase();
string mysort(string c, const long long clen);
vector < string > worddict(const string filename, const long long clen);
pair < int, long long > search (const string c, const vector < string > wd, const long long wdlen);
int anagram(string c, const string filename);


int main(){
	vector < string > test_c = maketestcase();
	int testnum = test_c.size();
	
	for(int i=0; i<testnum; i++){
		cout << "Given Characters: " << test_c[i] << endl;
		cout << "Results:" << endl;
		anagram(test_c[i], dictfilename);
		cout << endl;
	}
	return 0;
}


vector < string > maketestcase(){
	vector < string > test_c;
	
	test_c.push_back("owl");
	test_c.push_back("acdr");
	test_c.push_back("eat");
	test_c.push_back("a");
	test_c.push_back("");
	
	// test_c.push_back("abcdefghijklmn");
	return test_c;
}


string mysort(string c, const long long clen){
	// bubble sort for string
	long long sorted = 0;
	for(int sorted=0; sorted<clen-1; sorted++){
		for(int i=sorted+1; i>0; i--){
			if(c[i] < c[i-1]){ swap(c[i],c[i-1]); }
		}
	}
	return c;
}


vector < string > worddict(const string filename, const long long clen){
	ifstream ifs(filename);
	string temp;
	vector < string > wd;
	while (getline(ifs, temp)){
		if (temp.size()==clen){
			wd.push_back(temp);
		}
	}
	return wd;
}


pair < int, long long > search (const string c, const vector < string > wd, const long long wdlen, long long bfleft){
	long long left = bfleft;
	long long right = wdlen;
	long long mid;
	int success = 0;
	while(left < right){
		mid = floor((left+right)/2);
		if(wd[mid]==c){ success = 1; left = mid; break;}
		else if (c  < wd[mid]){right = mid;}
		else if (wd[mid] < c){left = mid+1;}
	}
	pair < int, long long > result;
	result.first = success;
	result.second = left;
	return result;
}



int anagram(string c, const string filename){
	// sort given characters
	long long clen = c.size(); // length of characters
	c =  mysort(c, clen);
	
	// make (sorted) dictionary 
	vector < string > wd = worddict(filename, clen);
	long long wdlen = wd.size();
	long long bfleft = 0;
	pair < int, long long > result;
	
	// search
	if(wdlen!=0){
		do {
			cout << c << endl;
			result = search(c, wd, wdlen, bfleft);
			bfleft = result.second;
			if(result.first){ cout << c << endl;}
			cout << result.first << ":"<<result.second << endl;
		} while(next_permutation(c.begin(), c.end()));
	}
	return 0;
}


/*
・文字列と辞書が与えられる
・文字列の全部を並べ替えてできる文字列のうち、辞書にあるものを出力
*/
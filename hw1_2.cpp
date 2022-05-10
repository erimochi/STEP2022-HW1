#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

string dictfilename = "./step2-master/anagram/words.txt";
string queryfilefolder = "./step2-master/anagram/";
string queryfilename = "small.txt";
string outputfilename = "small_answer.txt";
int n = 26;
int c_score[] = {1,3,2,2,1,3,3,1,1,4,4,2,2,1,1,3,4,1,1,1,2,3,3,4,3,4};


vector < string > worddict2(const string filename);
vector < vector < int > > worddict2_2(const vector < string > wd, const long long wdlen);
int anagram2(string c, const vector < string > wd, const long long wdlen, vector < vector < int > >  wd_alp, ofstream& ofs);
int calcscore(const string w);



int main(int argc, char *argv[]){
	if(argc==3){
		queryfilename = argv[1];
		outputfilename = argv[2];	
	}else{
		cout << "Usage:  ./ 1_2  [inputfilename] [outputfilename]" << endl
			<< "These files are read from or made in: ' " << queryfilefolder <<" ' "<< endl;
			return 0;
	}
	
	// make dictionary and count alphabets
	vector < string > wd = worddict2(dictfilename);
	long long wdlen = wd.size();
	vector < vector < int > > wd_alp = worddict2_2(wd,wdlen);
	
	// read test strings
	vector < string > test_c = worddict2(queryfilefolder+queryfilename);
	long long testnum = test_c.size();
	
	// prepare for output
	ofstream ofs;
	ofs.open(queryfilefolder+outputfilename);  //ios::trunc?
	if(!ofs){cout << "Failed to open output file"; exit(1);}
	ofs <<  "Input File: " << queryfilefolder+queryfilename << endl << endl;
	
	// calcurate score
	// testnum = 1; // In case of test
	long long totalscore = 0;
	for(int i=0; i<testnum; i++){
		totalscore += anagram2(test_c[i], wd, wdlen, wd_alp, ofs);	
	}
	ofs << endl << "Total Score: " <<  totalscore<< endl;
	ofs.close();
	
	// Show Result on Terminal
	cout << "File: " << queryfilefolder+queryfilename << endl;
	cout << "Total Score:" <<  totalscore<< endl;

	return 0;
}


vector < string > worddict2(const string filename){
	ifstream ifs(filename);
	if(!ifs){cout << "Failed to open input file"; exit(1);}
	string temp;
	vector < string > wd;
	while (getline(ifs, temp)){ wd.push_back(temp); }
	return wd;
}


vector < vector < int > > worddict2_2(const vector < string > wd, const long long wdlen){
	string temp;
	vector < vector < int > > wd_alp;
	vector < int > temp_alp;
	for(int j=0;j<n;j++){temp_alp.push_back(0);}
	for(int i=0;i<wdlen;i++){wd_alp.push_back(temp_alp);}
	for (int i=0; i<wdlen; i++){
		temp = wd[i];
		int tempsize = temp.length();
		for(int j=0; j<tempsize; j++){wd_alp[i][(int)temp[j]- 97] +=1;}
	}
	return wd_alp;	
}


int calcscore(const string w){
	int score = 0;
	int wlen = w.length();
	for(int i=0; i<wlen; i++){score += c_score[(int)w[i]- 97];}
	return score;
}


int anagram2(string c, const vector < string > wd, const long long wdlen, vector < vector < int > >  wd_alp, ofstream& ofs){
	// count alphabets in characters
	long long clen = c.length();
	vector < int >  c_alp;
	for(int j=0;j<n;j++){c_alp.push_back(0);}
	for (long long i=0; i<clen; i++){ c_alp[(int)c[i]-97] +=1; }
	
	// check, calcurate score
	int ok;
	int max_score = 0;
	vector < int > w_scores;
	for(int i=0; i<wdlen;i++){
		ok = 1;
		for(int j=0; j<n; j++){
			if(wd_alp[i][j] > c_alp[j]){ok =0; break;}
		}
		if(ok){
			w_scores.push_back(calcscore(wd[i]));
			if(max_score < w_scores[i]){max_score = w_scores[i];} 
		}else{w_scores.push_back(-1);}
	}

	//write in file
	ofs << "Given Characters: " << c << endl;
	ofs << "Max Score: " << max_score << endl << "Anagram:" << endl;
	for(int i=0; i<wdlen;i++){ if(w_scores[i] == max_score){ofs << wd[i] << endl;}}
	ofs << endl;
		
	return max_score;
}


/*
・文字列と辞書が与えられる
・文字列の一部を並べ替えてできる文字列のうち、辞書にあるものを出力
・それらのスコアの合計を標準出力
*/
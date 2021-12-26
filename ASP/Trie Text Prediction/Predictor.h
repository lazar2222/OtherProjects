#ifndef _Predictor_H_
#define _Predictor_H_

#include <iostream>

#include "TrieStablo.h"
#include <stack>
#include <queue>

using std::istream;

class Predictor
{
public:

	struct Prediction
	{
	private:
		struct PredicitonElem
		{
			int* freq;
			int weight;
			string key;

			PredicitonElem(int w, string k, int* f) :weight(w), key(k), freq(f) {}

			void print(int i,int f);
		};

		friend class Predictor;

		class PEcomparer
		{
		public:
			bool operator() (PredicitonElem A, PredicitonElem B)
			{
				return A.weight < B.weight;
			}
		};

	public:
		int* correct=nullptr;
		string q;
		priority_queue<PredicitonElem, vector<PredicitonElem>, PEcomparer> PRE;
		priority_queue<PredicitonElem, vector<PredicitonElem>, PEcomparer> ERR;
		int* r[3] = { nullptr,nullptr,nullptr };
		void select(int i);
		friend std::ostream& operator<<(std::ostream& str, Prediction& p);
		Predictor* caller=nullptr;
	};

	void init();
	void clear();
	bool contains(string& s);
	int find(string& s);
	int& insert(string& s);
	void insert(istream& stream);
	Prediction predict(string& s);
	void stats();
	static int getFormat(string& s);
	static string format(string& s,int f);
	static string stringGuard(string& s);

private:
	struct PredictionJob
	{
		TrieStablo::TrieCvor* start;
		int errorsleft = 3;
		string word;
		int penalty=0;
		string remainder;

		PredictionJob(TrieStablo::TrieCvor* s, int el, string w, int p, string r) :start(s),errorsleft(el),word(w),penalty(p),remainder(r){}
	};

	TrieStablo TS;

	static const int userWeight;
	static const int errorPenalty;
	static const int lenghtPenalty;
	static const int brojsuseda[26];
	static const char* susedi[26];

	void doJob(stack<PredictionJob>& S, Prediction& P);

};


#endif // !_Predictor_H_


#include "Predictor.h"

const int Predictor::userWeight = 50;
const int Predictor::lenghtPenalty = 5;
const int Predictor::errorPenalty = 15;
const int Predictor::brojsuseda[26] = { 4,5,5,7,4,7,7,7,4,7,6,4,4,5,4,2,2,4,6,4,4,5,4,5,4,4 };
const char* Predictor::susedi[26] = { "qwsz","vnghj","xvdfg","ersfzxc","wrsd","rtdgxcv","tyfhcvb","yugjvbn","uojk","uihkbnm","iojlnm","opkm","njkl","bmhjk","ipkl","ol","wa","etdf","weadzx","ryfg","yihj","cbfgh","qeas","zcsdf","tugh","xasd" };

void Predictor::init()
{
	clear();
}

void Predictor::clear()
{
	if (TS.m_koren)
		delete TS.m_koren;
	TS.m_koren = nullptr;
	TS.m_brCvorova = 0;
	TS.m_brKljuceva = 0;
}

bool Predictor::contains(string& s)
{
	return TS.contains(s.c_str());
}

int Predictor::find(string& s)
{
	return TS.dohvatiInfo(s.c_str());
}

int& Predictor::insert(string& s)
{
	return TS.umetni(s.c_str());
}

void Predictor::insert(istream& stream)
{
	char buf[100];
	int i = 0;
	int j = 0;
	int last = 0;
	bool flag = false;
	while (true)
	{
		bool r = stream.getline(buf, 100, ' ').eof();

		i = 0;
		j = 0;
		last = 0;
		flag = false;

		while (buf[i] != '\0')
		{
			if (buf[i] == '\n' || buf[i] == '\r')
			{
				buf[j++] = '\0';
				if (flag) {
					//cout << buf + last << "|" << endl;
					TS.umetni(buf + last)++;
				}
				flag = false;
				last = j;
			}
			else if (buf[i] <= 'z' && buf[i] >= 'a')
			{
				buf[j++] = buf[i];
				flag = true;
			}
			else if (buf[i] <= 'Z' && buf[i] >= 'A')
			{
				buf[j++] = buf[i] + 32;
				flag = true;
			}

			i++;
		}
		buf[j] = '\0';
		if (flag) {
			//cout << buf + last << "|" << endl;
			TS.umetni(buf + last)++;
		}

		if (r) { break; }
	}
}

Predictor::Prediction Predictor::predict(string& s)
{
	Prediction p;
	p.caller = this;
	p.q = s;
	s = stringGuard(s);
	stack<PredictionJob> S;
	S.push(PredictionJob(TS.m_koren, 3, "", 0, s));
	while (!S.empty())
	{
		doJob(S, p);
	}
	return p;
}

void Predictor::stats()
{
	TS.ispisiStatistiku(cout);
}

int Predictor::getFormat(string& s)
{
	int c = s.length();
	int m = 0;
	int v = 0;
	for (int i = 0; i < c; i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			m++;
		}
		else if (s[i] <= 'Z' && s[i] >= 'A')
		{
			v++;
		}
	}
	if (v == c)
	{
		return 2;
	}
	else if (v == 1 && s[0] <= 'Z' && s[0] >= 'A')
	{
		return 1;
	}
	return 0;

}

string Predictor::format(string& s, int f)
{
	string r = stringGuard(s);

	if (f == 1)
	{
		r[0] = r[0] - 32;
	}
	else if (f == 2)
	{
		for (int i = 0; i < r.length(); i++)
		{
			r[i] = r[i] - 32;
		}
	}

	return r;
}

string Predictor::stringGuard(string& s)
{
	string res = "";
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			res += s[i];
		}
		else if (s[i] <= 'Z' && s[i] >= 'A')
		{
			res += s[i] + 32;
		}
		else
		{
			throw 27;
		}
	}
	return res;
}

void Predictor::doJob(stack<PredictionJob>& S, Prediction& P)
{
	PredictionJob job = S.top(); S.pop();
	if (job.start == nullptr) { return; }
	if (job.remainder != "")
	{
		if (job.start->pronadjiPodstablo(job.remainder[0]) != nullptr) {
			S.push(PredictionJob(job.start->pronadjiPodstablo(job.remainder[0]), job.errorsleft, job.word + job.remainder[0], job.penalty, job.remainder.substr(1)));
		}
		if (job.errorsleft > 0)
		{
			for (int i = 0; i < brojsuseda[job.remainder[0] - 'a']; i++)
			{
				char s = susedi[job.remainder[0] - 'a'][i];
				if (job.start->pronadjiPodstablo(s) != nullptr) {
					S.push(PredictionJob(job.start->pronadjiPodstablo(s), job.errorsleft - 1, job.word + s, job.penalty + errorPenalty, job.remainder.substr(1)));
				}
			}
		}
	}
	else
	{
		if (job.start->dohvatiInfo() != 0)
		{
			int& f = job.start->dohvatiInfo();
			if (job.penalty == 0)
			{
				P.correct = &f;
			}
			else if (job.errorsleft == 3)
			{
				P.PRE.push(Prediction::PredicitonElem(f*0.01 - job.penalty, job.word, &f));
			}
			else
			{
				P.ERR.push(Prediction::PredicitonElem(f*0.01 - job.penalty, job.word, &f));
			}
		}
		for (int i = 0; i < 26; i++)
		{
			char ch = 'a' + i;
			TrieStablo::TrieCvor* c = job.start->pronadjiPodstablo(ch);
			if (c != nullptr)
			{
				S.push(PredictionJob(c, job.errorsleft, job.word + ch, job.penalty + lenghtPenalty, ""));
			}
		}


	}

}

std::ostream& operator<<(std::ostream& str, Predictor::Prediction& p)
{
	int format = Predictor::getFormat(p.q);
	int brp = 0;
	if (p.correct != nullptr)
	{
		cout << "1" << ". " << Predictor::format(p.q, format) << '\t' << *(p.correct) << " (" << (int)(*(p.correct)*0.01) << ") tacna rec" << endl;
		p.r[brp] = p.correct;
		brp++;
	}
	if (p.PRE.size() == 1)
	{
		Predictor::Prediction::PredicitonElem pe = p.PRE.top(); p.PRE.pop();
		pe.print(brp + 1, format);
		cout << " jedinstven prefiks" << endl;
		p.r[brp] = pe.freq;
		brp++;
	}
	while (brp < 3)
	{
		if (p.PRE.empty() && p.ERR.empty()) {}
		else if (p.PRE.empty() || (!p.ERR.empty() &&  p.ERR.top().weight > p.PRE.top().weight))
		{
			Predictor::Prediction::PredicitonElem pe= p.ERR.top(); p.ERR.pop();
			pe.print(brp + 1, format);
			cout << endl;
			p.r[brp] = pe.freq;
		}
		else if (p.ERR.empty() || p.ERR.top().weight <= p.PRE.top().weight)
		{
			Predictor::Prediction::PredicitonElem pe= p.PRE.top(); p.PRE.pop();
			pe.print(brp + 1, format);
			cout << endl;
			p.r[brp] = pe.freq;
		}
		brp++;
	}
	return str;
}

void Predictor::Prediction::select(int i)
{
	if (i == 0) { string sg = stringGuard(q); caller->insert(sg) += userWeight; }
	else if(i < 4 && i>0)
	{
		if (r[i-1] != nullptr) { *r[i-1] += userWeight; }
	}
}

void Predictor::Prediction::PredicitonElem::print(int i, int f)
{
	cout << i << ". " << format(key, f) << '\t' << *freq << " (" << weight << ")";
}

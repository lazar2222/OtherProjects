// TrieStablo.h: interface for the TrieStablo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIESTABLO_H__EA14736F_A30C_4DA9_A044_C865B9328099__INCLUDED_)
#define AFX_TRIESTABLO_H__EA14736F_A30C_4DA9_A044_C865B9328099__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stablo.h"

class TrieStablo : public Stablo
{
protected:

	class TrieCvor
	{
		TrieCvor* m_niz_pokazivaca[26];
		TrieCvor* m_roditelj;
		int m_info;
		int m_brojPodstabala;

		TrieCvor(const TrieCvor&)=default;
		TrieCvor& operator=(const TrieCvor&)=default;

	public:
		TrieCvor(TrieCvor* roditelj);

		virtual ~TrieCvor();

		TrieCvor* roditelj()
		{
			return m_roditelj;
		}

		TrieCvor* pronadjiPodstablo(char deoKljuca);
		void dodajPodstablo(char deoKljuca, TrieCvor* cvor);
		void ukloniPodstablo(char deoKljuca);

		int brojPodstabala() const { return m_brojPodstabala; }

		int& dohvatiInfo();
		void postaviInfo(const int tekst);

		void poseti(ostream& it);
	};

	TrieCvor* m_koren;

	TrieStablo(const TrieStablo&) =default;
	TrieStablo& operator=(const TrieStablo&) =default;

	TrieCvor* pronadjiCvor(const char* kljuc);   // pronalazi cvor koji sadrzi dati kljuc

	friend class Predictor;

public:
	TrieStablo();
	virtual ~TrieStablo();

	virtual int& umetni(const char* kljuc);
	virtual bool obrisi(const char* kljuc);

	virtual void obidji(ostream& it);

	virtual int& dohvatiInfo(const char* kljuc);
	virtual bool contains(const char* kljuc);

	
};

#endif // !defined(AFX_TRIESTABLO_H__EA14736F_A30C_4DA9_A044_C865B9328099__INCLUDED_)

#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;
/*
* clasa Oferta : denumire, destinatie, tip-string
*				 pret- int pozitiv
*/
class Oferta {
	std::string denumire;
	std::string destinatie;
	std::string tip;
	int pret;
public:
	Oferta() = default;
	Oferta(const string denumire, const string destinatie, const string tip, int pret) :denumire{ denumire }, destinatie{ destinatie }, tip{ tip }, pret{ pret }{}
	Oferta(const Oferta& of) :denumire{ of.denumire }, destinatie{ of.destinatie }, tip{ of.tip }, pret{ of.pret } {
		cout << "!!!!!!!!!!!!!!!!!!!! denumire " + of.getDenumire() + "\n";
	}

	/*getter pentru denumire*/
	string getDenumire() const {
		return denumire;
	}
	/*getter pentru destinatie*/
	string getDestinatie() const {
		return destinatie;
	}
	/*getter pentru tip*/
	string getTip() const {
		return tip;
	}
	/*getter pentru pret*/
	int getPret() const noexcept {
		return pret;
	}
	/*setter pentru destinatie*/
	void setDestinatie(string destinatie1) {
		this->destinatie = destinatie1;
	}
	/*setter pentru tip*/
	void setTip(string tip1) {
		this->tip = tip1;
	}/*setter pentru pret*/
	void setPret(int pret1) {
		this->pret = pret1;
	}
};
/*
Compara dupa denumire
returneaza true daca of1.denumire e mai mic decat of2.denumire
*/
//bool cmpDenumire(const Oferta& of1, const Oferta& of2);

/*
Compara dupa destinatie
returneaza true daca of1.destinatie e mai mic decat of2.destinatie
*/
//bool cmpDestinatie(const Oferta& of1, const Oferta& of2);

//bool cmpTypePrice(const Oferta& of1, const Oferta& of2);
//bool findDenumire();
//bool findOferta(const Oferta& of, string denumire, string destinatie, string tip, int pret);
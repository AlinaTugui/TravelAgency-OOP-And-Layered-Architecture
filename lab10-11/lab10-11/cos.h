#pragma once
#include "ofertaRepo.h"
#include <vector>
#include "observer.h"
using std::vector;
class Cos:public Observable {
private:
	Repository& rep;
	vector<Oferta> cos;
public:
	//constructorul pentru cos
	Cos(Repository& rep) noexcept : rep{ rep } {

	}
	//metoda inline getCos care returneaza cosul
	const vector<Oferta>& getCos() noexcept {
		return cos;
	}
	/*
	sterge toate ofertele din cos existente la un moment dat
	*/
	void golesteCos();

	/*
	adauga o oferta din wishlist data de utilizator in cos
	*/
	void addCos(string denumire);

	/*
	se populeaza cosul cu oferte aleatorii, utilizatorul da numarul de oferte care sa fie generate
	*/
	void genereazaCos(int nr);

	/*
	salveaza cosul intr un fisier csv, numele fisierului se da ca argument
	*/
	void exportHTML(const string& filename);
};

//clasa de exceptii pentru cos
class OfertaCosException {
	string msg;
public:
	OfertaCosException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const OfertaCosException& ex);
	string getMessage() const {
		return msg;
	}
};

ostream& operator<<(ostream& out, const OfertaCosException& ex);
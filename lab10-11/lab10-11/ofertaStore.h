#pragma once

#include "oferta.h"
#include "ofertaRepo.h"
#include <string>
#include <vector>
#include "VectorDinamic.h"
#include <functional>
#include "validator.h"
#include "cos.h"
#include<map>
#include "undo.h"
using std::vector;
using std::function;
using std::map;
using std::unique_ptr;

//clasa DTO OferteDestinatie
class OferteDestinatie {
private:
	string destinatie;
	int nr_oferte;
public:
	//constructori
	OferteDestinatie() { nr_oferte = 0; }
	OferteDestinatie(const string& destinatie, int nr_oferte) :destinatie{ destinatie }, nr_oferte{ nr_oferte } {

	}
	int get_nr_oferte() const noexcept {
		return this->nr_oferte;
	}
	void creste_nr_oferte() noexcept {
		this->nr_oferte++;
	}
};

class OfertaStore {
	Repository& rep;
	OfertaValidator& val;
	vector<unique_ptr<ActiuneUndo>> undoActions;
	Cos& cos;

	/*
	 Functie de sortare generala
	 maiMareF - functie care compara 2 Oferte, verifica daca are loc relatia mai mare
			  - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametri Oferta)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
	 returneaza o lista sortata dupa criteriu dat ca parametru
	*/
	//vector<Oferta> generalSort(bool (*maiMicF)(const Oferta&, const Oferta&));
	/*
	Functie generala de filtrare
	fct - poate fi o functie
	fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar ofertele care trec de filtru (fct(pet)==true)
	*/
	//vector<Oferta> filtreaza(function<bool(const Oferta&)> fct);
public:
	OfertaStore(Repository& rep, OfertaValidator& val, Cos& cos) :rep{ rep }, val{ val }, cos{ cos } {
	}
	//nu permitem copierea de obiecte OfertaStore
	OfertaStore(const OfertaStore& ot) = delete;
	~OfertaStore() = default;
	/*
	 returneaza toate ofertele in ordinea in care au fost adaugate
	*/
	const vector<Oferta>& getAll() noexcept {
		return rep.getAll();
	}
	/*returneaza toate ofertele existente la un moment dat in cos in ordinea in care au fost adaugate*/
	const vector<Oferta>& getCos() noexcept {
		return cos.getCos();
	}
	/*
	Adauga o noua oferta
	arunca exceptie daca: nu se poate salva, nu este valida
	*/
	void addOferta(const string& denumire, const string& destinatie, const string& tip, int pret);

	/*
	* functie care sterge o oferta data prin denumire, daca oferta respectiva exista
	*/
	void deleteOfertaStore(string denumire);

	/*functie care actualizeaza o oferta data prin denumire cu noua destinatie, noul tip si noul pret, in cazul in care oferta exista
	exceptiile se prind in repo*/
	void updateOfertaStore(string denumire, string destinatie, string tip, int pret);

	/*functie de cautare a unei oferte dupa denumire*/
	const Oferta& cauta(string denumire) const;
	/*
	Sorteaza dupa denumire
	*/
	vector<Oferta> sortByDenumire();

	/*
	Sorteaza dupa destinatie
	*/
	vector<Oferta> sortByDestinatie();


	/*
	Sorteaza dupa tip si pret
	*/
	vector<Oferta> sortByTypePrice();

	/*functie de filtrare dupa destinatie*/
	vector<Oferta> filtrareDestinatie(string destinatie);
	/*
	returneaza doar ofertele cu pret mai mic decat cel dat
	*/
	vector<Oferta> filtrarePretMaiMic(int pret);

	/*
	returneaza doar ofertele cu pret intre cele doua preturi
	*/
	vector<Oferta> filtrarePret(int pretMin, int pretMax);

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

	map<string, OferteDestinatie> numarOferteDestinatie();

	/*
	salveaza cosul intr un fisier csv, numele fisierului se da ca argument
	*/
	void exportHTML(const string& filename);

	void undo();

	Cos& getCosCurent() {
		return cos;
	}
};
//void testCtr();

class OfertaStoreException {
	string msg;
public:
	OfertaStoreException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	//friend ostream& operator<<(ostream& out, const OfertaStoreException& ex);
};

//ostream& operator<<(ostream& out, const OfertaStoreException& ex);
#pragma once
#include "oferta.h"
#include "VectorDinamic.h"
#include <vector>
#include <string>
#include <ostream>
#include<map>
using std::vector;
using std::string;
using std::ostream;
using std::map;

class Repository {
public:
	virtual void store(const Oferta& of) = 0;
	virtual const Oferta& find(string denumire) const = 0;
	virtual void deleteOferta(const string& denumire) = 0;
	virtual void updateOferta(const Oferta& oferta, string denumire) = 0;
	virtual const vector<Oferta>& getAll() noexcept = 0;
	virtual ~Repository() = default;
};

class OfertaRepo :public Repository {
	vector<Oferta> all;
	/*
	metoda privata verifica daca exista deja of in repository
	*/
	bool exist(const Oferta& of) const;
public:
	OfertaRepo() = default;
	//nu permitem copierea de obiecte
	OfertaRepo(const OfertaRepo& of) = delete;
	/*
	Salvare oferta
	arunca exceptie daca mai exista o oferta cu acelasi tip, aceeasi denumire si aceeasi destinatie
	*/
	void store(const Oferta& of) override;

	/*
	Cauta
	arunca exceptie daca nu exista oferta
	*/
	const Oferta& find(string denumire) const override;
	/*functie care sterge o oferta de tip Oferta
	daca oferta nu exista ridica exceptie OfertaRepoException*/
	void deleteOferta(const string& denumire) override;
	/*functie care actualizeaza o oferta data prin denumire cu noul pret, noul tip si noua destinatie
	daca oferta care se doreste a fi actualizata nu exista ridica exceptie OfertaRepoException*/
	void updateOferta(const Oferta& oferta, string denumire) override;

	/*
	returneaza toate ofertele salvate
	*/
	const vector<Oferta>& getAll() noexcept override;
	//virtual ~OfertaRepo() = default;
};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class OfertaRepoException {
	string msg;
public:
	OfertaRepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const OfertaRepoException& ex);
	string getMessage() const {
		return msg;
	}

};

ostream& operator<<(ostream& out, const OfertaRepoException& ex);

//void testeRepo();

class OfertaRepoFile : public OfertaRepo {
private:
	string filename;
	void loadFromFile();
	void storeToFile();
public:
	OfertaRepoFile(string filename) : OfertaRepo(), filename{ filename } {
		loadFromFile();
	};
	void store(const Oferta& of) override;
	void deleteOferta(const string& denumire) override;
	void updateOferta(const Oferta& oferta, string denumire) override;
	//const vector<Oferta>& getAll() const noexcept override;
};

class OfertaRepoMap :public Repository {
private:
	map<string, Oferta> oferteDictionar;
	vector<Oferta> oferte;
	double p;
public:
	OfertaRepoMap(double p) :p{ p } {}
	OfertaRepoMap() = default;
	void store(const Oferta& of) override;
	const vector<Oferta>& getAll() noexcept override;
	const Oferta& find(string denumire) const override;
	void deleteOferta(const string& denumire) override;
	void updateOferta(const Oferta& oferta, string denumire) override;

};
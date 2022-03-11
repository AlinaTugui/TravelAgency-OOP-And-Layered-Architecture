#include "oferta.h"
#include "ofertaRepo.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include<fstream>
#include<random>
#include<chrono>
using std::ostream;
using std::stringstream;

void OfertaRepo::store(const Oferta& of)
{
	if (exist(of)) {
		throw OfertaRepoException("Exista deja oferta denumire:" + of.getDenumire() + " destinatie:" + of.getDestinatie() + " tip:" + of.getTip());
	}
	all.push_back(of);
}

bool OfertaRepo::exist(const Oferta& of) const {
	try {
		find(of.getDenumire());
		return true;
	}
	catch (OfertaRepoException&) {
		return false;
	}
}
/*
Cauta
arunca exceptie daca nu exista oferta
*/
const Oferta& OfertaRepo::find(string denumire) const {
	const auto& rez = std::find_if(all.begin(), all.end(), [denumire](const Oferta& of) {
		return of.getDenumire() == denumire;
		});
	if (rez == all.end()) {
		throw OfertaRepoException("Nu exista oferta cu denumirea: " + denumire);
	}
	else
		return *rez;
}

void OfertaRepo::deleteOferta(const string& denumire) {
	int ok = 0;
	int p = -1;
	for (const auto& of : all) {
		p++;
		if (of.getDenumire() == denumire) {
			all.erase(p + all.begin());
			ok = 1;
			break;
		}
	}
	if (ok == 0)
		throw OfertaRepoException("Nu exista oferta cu denumirea: " + denumire);

	/*
	const auto& of = std::find(all.begin(), all.end(), [denumire](const Oferta& of) {
		return denumire == of.getDenumire();
		});
	if (of != all.end()) {
		all.erase(of);
	}
	else
		throw OfertaRepoException("Nu exista oferta cu denumirea: " + denumire);

	*/
}

void OfertaRepo::updateOferta(const Oferta& oferta, string denumire) {
	int ok = 0;
	for (auto& of : all) {
		if (of.getDenumire() == oferta.getDenumire()) {
			of.setDestinatie(oferta.getDestinatie());
			of.setTip(oferta.getTip());
			of.setPret(oferta.getPret());
			ok = 1;
			break;
		}
	}
	if (ok == 0) {
		throw OfertaRepoException("Nu exista oferta cu denumirea: " + denumire);
	}
	/*
	auto of=std::find_if(all.begin(),all.end(), [denumire](const Oferta& of) {
		return denumire == of.getDenumire();
		});
	if (of != all.end()) {
		of.setDestinatie(oferta.getDestinatie());
		of.setTip(oferta.getTip());
		of.setPret(oferta.getPret());
	}
	else
		throw OfertaRepoException("Nu exista oferta cu denumirea: " + denumire);
	*/
}

/*
returneaza toate ofertele salvate
*/
const vector<Oferta>& OfertaRepo::getAll() noexcept {
	return all;
}

ostream& operator<<(ostream& out, const OfertaRepoException& ex) {
	out << ex.msg;
	return out;
}

void OfertaRepoFile::store(const Oferta& of) {
	OfertaRepo::store(of);
	storeToFile();
}

void OfertaRepoFile::deleteOferta(const string& denumire) {
	OfertaRepo::deleteOferta(denumire);
	storeToFile();
}

void OfertaRepoFile::loadFromFile() {
	std::ifstream f(filename);
	//if (!f.is_open())
		//throw OfertaRepoException("Eroare la deschiderea fisierului\n");
	while (!f.eof()) {
		string denumire, destinatie, tip;
		int pret;
		f >> denumire;
		if (f.eof())
			break;
		f >> destinatie >> pret >> tip;
		Oferta of{ denumire,destinatie,tip,pret };
		try {
			OfertaRepo::store(of);
		}
		catch (OfertaRepoException& ex) {
			ex.getMessage();
		}
	}
	f.close();
}

void OfertaRepoFile::storeToFile() {
	std::ofstream g(filename);
	//if (!g.is_open())
		//throw OfertaRepoException("Eroare la deschiderea fisierului\n");
	for (const auto& of : OfertaRepo::getAll()) {
		g << of.getDenumire() << " " << of.getDestinatie() << " " << of.getPret() << " " << of.getTip() << '\n';
	}
	g.close();
}

void OfertaRepoFile::updateOferta(const Oferta& oferta, string denumire) {
	OfertaRepo::updateOferta(oferta, denumire);
	storeToFile();
}


void OfertaRepoMap::store(const Oferta& oferta) {
	double nr;
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<> const dist(0, 1);
	nr = dist(mt);
	cout << "Probabilitatea generata: " << nr << '\n';
	if (p > nr) {
		for (const auto& of : oferteDictionar) {
			if (oferta.getDenumire() == of.second.getDenumire())
				throw OfertaRepoException("Exista deja oferta denumire:" + oferta.getDenumire() + " destinatie:" + oferta.getDestinatie() + " tip:" + oferta.getTip());
		}
		oferteDictionar.insert({ oferta.getDenumire(),oferta });
	}
	else
		throw OfertaRepoException("Probabilitatea este mai mica decat cea generata\n");
}

const vector<Oferta>& OfertaRepoMap::getAll() noexcept {
	oferte.clear();
	for (const auto& ofDict : oferteDictionar)
		oferte.push_back(ofDict.second);
	return oferte;
}

const Oferta& OfertaRepoMap::find(string denumire) const {
	double nr;
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<> const dist(0, 1);
	nr = dist(mt);
	cout << "Probabilitatea generata: " << nr << '\n';
	if (p > nr) {
		for (const auto& of : oferteDictionar)
		{
			if (of.second.getDenumire() == denumire)
				return of.second;
		}
		throw OfertaRepoException("Aceasta oferta nu exista!\n");
	}
	else
		throw OfertaRepoException("Probabilitatea este mai mica decat cea generata\n");
}

void OfertaRepoMap::deleteOferta(const string& denumire) {
	double nr;
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<> const dist(0, 1);
	nr = dist(mt);
	cout << "Probabilitatea genereata:" << nr << std::endl;
	if (p > nr) {
		for (const auto& of : oferteDictionar)
		{

			if (of.second.getDenumire() == denumire)
			{
				oferteDictionar.erase(of.first);
				break;
			}
		}
	}
	else
		throw OfertaRepoException("Probabilitatea este mai mica decat cea generata\n");
}

void OfertaRepoMap::updateOferta(const Oferta& activ, string denumire) {
	double nr;
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<> const dist(0, 1);
	nr = dist(mt);
	cout << "Probabilitatea genereata:" << nr << '\n';
	if (p > nr) {
		int ok = 0;
		for (auto& of : oferteDictionar)
		{
			if (of.second.getDenumire() == denumire) {
				of.second.setDestinatie(activ.getDestinatie());
				of.second.setPret(activ.getPret());
				of.second.setTip(activ.getTip());
				ok = 1;
				break;
			}
		}
		if (ok == 0)
			throw OfertaRepoException("Aceasta oferta nu exista!\n");
	}
	else
		throw OfertaRepoException("Probabilitatea este mai mica decat cea generata\n");
}
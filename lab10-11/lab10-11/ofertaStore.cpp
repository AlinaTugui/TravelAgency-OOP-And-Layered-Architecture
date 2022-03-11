#include "oferta.h"
#include "ofertaStore.h"
#include <functional>
#include <algorithm>
#include <assert.h>
#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock

/*
Adauga o noua oferta
arunca exceptie daca: nu se poate salva, nu este valida
*/
void OfertaStore::addOferta(const string& denumire, const string& destinatie, const string& tip, int pret) {
	Oferta of{ denumire,destinatie,tip,pret };
	val.validate(of);
	rep.store(of);
	undoActions.push_back(std::make_unique<UndoAdauga>(rep, of));
}

void OfertaStore::deleteOfertaStore(string denumire) {
	const Oferta& of = rep.find(denumire);
	undoActions.push_back(std::make_unique<UndoSterge>(rep, of));
	rep.deleteOferta(denumire);
}

void OfertaStore::updateOfertaStore(string denumire, string destinatie, string tip, int pret) {
	const Oferta& of = rep.find(denumire);
	Oferta oferta{ denumire, destinatie, tip, pret };
	val.validate(oferta);
	undoActions.push_back(std::make_unique<UndoModifica>(rep, of));
	rep.updateOferta(oferta, denumire);
}
const Oferta& OfertaStore::cauta(string denumire) const {
	const Oferta& of = rep.find(denumire);
	return of;
}

/*
Sorteaza dupa denumire
*/
vector<Oferta> OfertaStore::sortByDenumire() {
	auto copyAll = rep.getAll();
	std::sort(copyAll.begin(), copyAll.end(), [](const Oferta& of1, const Oferta& of2) {
		return of1.getDenumire() < of2.getDenumire();
		});
	return copyAll;

}

/*
Sorteaza dupa destinatie
*/
vector<Oferta> OfertaStore::sortByDestinatie() {
	auto copyAll = rep.getAll();
	std::sort(copyAll.begin(), copyAll.end(), [](const Oferta& of1, const Oferta& of2) {
		return of1.getDestinatie() < of2.getDestinatie();
		});
	return copyAll;
}


/*
Sorteaza dupa tip+pret
*/
vector<Oferta> OfertaStore::sortByTypePrice() {
	auto copyAll = rep.getAll();
	std::sort(copyAll.begin(), copyAll.end(), [](const Oferta& of1, const Oferta& of2) {
		if (of1.getTip() == of2.getTip()) {
			return of1.getPret() < of2.getPret();
		}
		return of1.getTip() < of2.getTip();
		});
	return copyAll;
}

vector<Oferta> OfertaStore::filtrareDestinatie(string destinatie) {
	vector<Oferta> rez;
	auto all = rep.getAll();
	std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [destinatie](const Oferta& of) {
		return of.getDestinatie() == destinatie; });
	return rez;
}

vector<Oferta> OfertaStore::filtrarePretMaiMic(int pret) {
	vector<Oferta> rez;
	auto all = rep.getAll();
	std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [pret](const Oferta& of) {
		return of.getPret() < pret; });
	return rez;
}

vector<Oferta> OfertaStore::filtrarePret(int pretMin, int pretMax) {
	vector<Oferta> rez;
	auto all = rep.getAll();
	std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [pretMin, pretMax](const Oferta& of) {
		return of.getPret() >= pretMin && of.getPret() <= pretMax; });
	return rez;
}

void OfertaStore::golesteCos() {
	/*if (cos.size() == 0)
		throw OfertaStoreException("Cosul este deja gol!\n");
	else*/
	cos.golesteCos();
}

void OfertaStore::addCos(string denumire) {
	/*const auto& of = cauta(denumire);
	if (exist(of)) {
		throw OfertaStoreException("Exista deja oferta denumire:" + of.getDenumire() + " destinatie:" + of.getDestinatie() + " tip:" + of.getTip());
	}
	cos.push_back(of);
	*/
	cos.addCos(denumire);
}

void OfertaStore::genereazaCos(int nr) {
	//auto all = rep.getAll();
	cos.genereazaCos(nr);
}

//functionalitatea noua
//functie care returneaza un map <string, OferteDestinatie> care contine chei destinatiile ofertelor si ca valori numarul de oferte cu
//destinatia data
map<string, OferteDestinatie> OfertaStore::numarOferteDestinatie() {
	map<string, OferteDestinatie> dict_of_dest;
	const auto& lista_oferte = rep.getAll();
	for (const auto& of : lista_oferte) {
		if (dict_of_dest.find(of.getDestinatie()) == dict_of_dest.end())
			dict_of_dest[of.getDestinatie()] = OferteDestinatie(of.getDestinatie(), 1);
		else
			dict_of_dest[of.getDestinatie()].creste_nr_oferte();
	}
	return dict_of_dest;
}

void OfertaStore::exportHTML(const string& filename) {
	cos.exportHTML(filename);

}

void OfertaStore::undo() {
	if (undoActions.empty()) {
		throw OfertaRepoException("S a ajuns la stadiul initial\n");
	}
	undoActions.back()->doUndo();//apel polimorific
	undoActions.pop_back();
}
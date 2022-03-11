#include "teste.h"
#include <assert.h>
#include <sstream>
#include <map>
#include <fstream>
using std::stringstream;
using std::map;

void testAdauga() {
	OfertaRepo rep;
	rep.store(Oferta{ "a", "a","a",4 });
	assert(rep.getAll().size() == 1);
	assert(rep.find("a").getDenumire() == "a");

	rep.store(Oferta{ "b", "b","b",4 });
	assert(rep.getAll().size() == 2);

	//nu pot adauga 2 cu aceeasi denumire, acelasi tip si aceeasi destinatie
	try {
		rep.store(Oferta{ "a", "a", "a", 4 });
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}
	//cauta inexistent
	try {
		rep.find("c");
	}
	catch (const OfertaRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void testCauta() {
	OfertaRepo rep;
	rep.store(Oferta{ "a", "a","a",4 });
	rep.store(Oferta{ "b", "b","b",4 });

	const auto& of = rep.find("a");
	assert(of.getDenumire() == "a");
	assert(of.getDestinatie() == "a");
	assert(of.getTip() == "a");
	//arunca exceptie daca nu gaseste
	try {
		rep.find("d");
	}
	catch (OfertaRepoException&) {
		assert(true);
	}
}

void testDelete() {
	OfertaRepo rep;
	Oferta of{ "a", "a","a",4 };
	rep.store(of);
	assert(rep.getAll().size() == 1);
	rep.deleteOferta("a");
	assert(rep.getAll().size() == 0);
	try {
		rep.deleteOferta("a");
	}
	catch (OfertaRepoException&) {
		assert(true);
	}
}

void testUpdate() {
	OfertaRepo rep;
	Oferta of{ "a", "a","a",4 };
	rep.store(of);
	assert(rep.getAll().size() == 1);
	Oferta of1{ "a", "aa","aa",14 };
	rep.updateOferta(of1, "a");
	Oferta of2 = rep.find("a");
	assert(of2.getDestinatie() == "aa");
	assert(of2.getTip() == "aa");
	assert(of2.getPret() == 14);
	try {
		rep.updateOferta(Oferta{ "c","c","C",5 }, "c");
	}
	catch (OfertaRepoException&) {
		assert(true);
	}
}

void testeRepo() {
	testAdauga();
	testCauta();
	testDelete();
	testUpdate();
}

void testAdaugaCtr() {
	OfertaRepo rep;
	OfertaValidator val;
	Cos cos{ rep };
	OfertaStore ctr{ rep,val, cos };
	ctr.addOferta("a", "a", "a", 6);
	assert(ctr.getAll().size() == 1);

	//adaug ceva invalid
	try {
		ctr.addOferta("", "", "", -1);
	}
	catch (ValidateException&) {
		assert(true);
	}
	//incerc sa adaug ceva ce existadeja
	try {
		ctr.addOferta("a", "a", "a", -1);
	}
	catch (ValidateException&) {
		assert(true);
	}
}

void testFiltrare() {
	OfertaRepo rep;
	OfertaValidator val;
	Cos cos{ rep };
	OfertaStore ctr{ rep,val, cos };
	ctr.addOferta("a", "a", "a", 6);
	ctr.addOferta("b", "b", "a", 60);
	ctr.addOferta("c", "c", "a", 600);
	assert(ctr.filtrarePret(6, 70).size() == 2);
	assert(ctr.filtrarePret(6, 60).size() == 2);
	assert(ctr.filtrarePretMaiMic(60).size() == 1);
	assert(ctr.filtrarePretMaiMic(7).size() == 1);
	assert(ctr.filtrarePretMaiMic(6).size() == 0);
	assert(ctr.filtrareDestinatie("a").size() == 1);
}

void testSortare() {
	OfertaRepo rep;
	OfertaValidator val;
	Cos cos{ rep };
	OfertaStore ctr{ rep,val, cos };
	ctr.addOferta("z", "z", "z", 6);
	ctr.addOferta("b", "b", "a", 60);
	ctr.addOferta("c", "c", "a", 600);

	auto firstO = ctr.sortByDenumire()[0];
	assert(firstO.getTip() == "a");

	firstO = ctr.sortByDestinatie()[0];
	assert(firstO.getDenumire() == "b");

	firstO = ctr.sortByTypePrice()[0];
	assert(firstO.getPret() == 60);

}

void testUpdateCtr() {
	OfertaRepo rep;
	OfertaValidator val;
	Cos cos{ rep };
	OfertaStore ctr{ rep,val, cos };
	ctr.addOferta("z", "z", "z", 6);
	ctr.updateOfertaStore("z", "zz", "zzz", 66);
	Oferta of = rep.find("z");
	assert(of.getDestinatie() == "zz");
	assert(of.getTip() == "zzz");
	assert(of.getPret() == 66);
	try {
		ctr.updateOfertaStore("z", "zzzz", "z", -12333);
	}
	catch (ValidateException&) {
		assert(true);
	}
}

void testDeleteCtr() {
	OfertaRepo rep;
	OfertaValidator val;
	Cos cos{ rep };
	OfertaStore ctr{ rep,val, cos };
	ctr.addOferta("z", "z", "z", 6);
	ctr.addOferta("b", "b", "a", 60);
	assert(rep.getAll().size() == 2);
	ctr.deleteOfertaStore("z");
	assert(rep.getAll().size() == 1);
	try {
		ctr.deleteOfertaStore("z");
	}
	catch (OfertaRepoException&) {
		assert(true);
	}
	try {
		ctr.deleteOfertaStore("A");
	}
	catch (const OfertaRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void testCautaCtr() {
	OfertaRepo rep;
	OfertaValidator val;
	Cos cos{ rep };
	OfertaStore ctr{ rep,val, cos };
	ctr.addOferta("z", "z", "z", 6);
	Oferta of = ctr.cauta("z");
	assert(of.getDestinatie() == "z");
	assert(of.getTip() == "z");
	assert(of.getPret() == 6);

}
void testRaport() {
	OfertaRepo rep;
	OfertaValidator val;
	Cos cos{ rep };
	OfertaStore ctr{ rep,val, cos };
	ctr.addOferta("z", "z", "z", 6);
	ctr.addOferta("a", "z", "b", 11);
	ctr.addOferta("zqq", "zz", "z", 6);
	ctr.addOferta("aa", "z", "bdd", 111);
	map<string, OferteDestinatie> all = ctr.numarOferteDestinatie();
	assert(all["z"].get_nr_oferte() == 3);
	assert(all["zz"].get_nr_oferte() == 1);

}
void testCtr() {
	testAdaugaCtr();
	testFiltrare();
	testSortare();
	testUpdateCtr();
	testDeleteCtr();
	testCautaCtr();
	testRaport();
}

void testValidator() {
	OfertaValidator v;
	Oferta of{ "", "","",-1 };
	try {
		v.validate(of);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto& mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
		assert(mesaj.find("vida") >= 0);
	}

}

void testeWishlist() {
	OfertaRepo rep;
	OfertaValidator val;
	Cos cos{ rep };
	OfertaStore ctr{ rep,val, cos };
	ctr.addOferta("z", "z", "z", 6);
	ctr.addCos("z");
	vector<Oferta> cos1 = ctr.getCos();
	assert(cos1.size() == 1);
	try {
		ctr.addCos("z");
	}
	catch (const OfertaCosException&) {
		assert(true);
	}
	ctr.golesteCos();
	cos1 = ctr.getCos();
	assert(cos1.size() == 0);
	try {
		ctr.genereazaCos(0);
	}
	catch (const OfertaCosException&) {
		assert(true);
	}
	try {
		ctr.genereazaCos(2);
	}
	catch (OfertaCosException&) {
		assert(true);
	}
	ctr.genereazaCos(1);
	cos1 = ctr.getCos();
	assert(cos1.size() == 1);

	try {
		ctr.genereazaCos(-1);
	}
	catch (const OfertaCosException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto& mesaj = sout.str();
		assert(mesaj.find("Numarul de oferte care doriti sa fie generate trebuie sa fie mai mare decat 0") >= 0);
	}
	ctr.exportHTML("test");
	std::ifstream f("D:/faculta/sem2/poo/lab9/test.html");
	int nr = 0;
	string line;
	while (f >> line)
		nr++;
	assert(nr > 0);

}
void testeUndo() {
	OfertaRepo rep;
	OfertaValidator val;
	Cos cos{ rep };
	OfertaStore ctr{ rep,val, cos };
	ctr.addOferta("z", "z", "z", 6);
	vector<Oferta> all = ctr.getAll();
	ctr.undo();
	all = ctr.getAll();
	assert(all.size() == 0);

	ctr.addOferta("z", "z", "z", 6);
	ctr.updateOfertaStore("z", "zz", "zz", 66);
	const Oferta of = rep.find("z");
	assert(of.getDestinatie() == "zz");
	assert(of.getTip() == "zz");
	assert(of.getPret() == 66);
	ctr.undo();
	all = ctr.getAll();
	const Oferta& of1 = rep.find("z");
	assert(of1.getDestinatie() == "z");
	assert(of1.getTip() == "z");
	assert(of1.getPret() == 6);

	ctr.deleteOfertaStore("z");
	ctr.undo();
	const Oferta& of2 = rep.find("z");
	assert(of2.getDestinatie() == "z");
	assert(of2.getTip() == "z");
	assert(of2.getPret() == 6);
	ctr.undo();
	try {
		ctr.undo();
	}
	catch (OfertaRepoException&) {
		assert(true);
	}

}
void testeFisiere() {
	OfertaRepoFile rep{ "oferteTest.txt" };
	OfertaValidator val;
	Cos cos{ rep };
	OfertaStore ctr{ rep,val,cos };
	ctr.addOferta("vacanta", "Londra", "mare", 3);
	ctr.addOferta("calatorie", "Paris", "munte", 5);
	ctr.addOferta("transport", "Londra", "scufundari", 4);
	ctr.addOferta("relaxare", "Italia", "munte", 4);
	ctr.addOferta("petrecere", "Londra", "scufundari", 4);

	assert(ctr.getAll().size() == 5);

	ctr.deleteOfertaStore("vacanta");
	assert(ctr.getAll().size() == 4);

	ctr.updateOfertaStore("relaxare", "zzzzzzzzz", "zzz", 22);

	OfertaRepoFile rep2{ "oferteTest.txt" };
	OfertaStore ctr2{ rep2, val,cos };

	assert(ctr2.getAll().size() == 4);

	std::ofstream out("oferteTest.txt", std::ofstream::trunc);
	out.close();


}

void testeRepoMap() {
	OfertaRepoMap rep{ 1 };
	rep.store(Oferta{ "a", "a","a",4 });
	assert(rep.getAll().size() == 1);
	assert(rep.find("a").getDenumire() == "a");

	rep.store(Oferta{ "b", "b","b",4 });
	assert(rep.getAll().size() == 2);

	//nu pot adauga 2 cu aceeasi denumire, acelasi tip si aceeasi destinatie
	try {
		rep.store(Oferta{ "a", "a", "a", 4 });
	}
	catch (const OfertaRepoException&) {
		assert(true);
	}
	//cauta inexistent
	try {
		rep.find("c");
	}
	catch (const OfertaRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}


	rep.store(Oferta{ "aa", "a","a",4 });
	rep.store(Oferta{ "bb", "b","b",4 });

	const auto& of = rep.find("aa");
	assert(of.getDenumire() == "aa");
	assert(of.getDestinatie() == "a");
	assert(of.getTip() == "a");
	//arunca exceptie daca nu gaseste
	try {
		rep.find("d");
	}
	catch (OfertaRepoException&) {
		assert(true);
	}

	Oferta of11{ "aaa", "a","a",4 };
	rep.store(of11);
	//assert(rep.getAll().size() == 1);
	rep.deleteOferta("aaa");
	//assert(rep.getAll().size() == 0);
	try {
		rep.deleteOferta("aaa");
	}
	catch (OfertaRepoException&) {
		assert(true);
	}

	Oferta of111{ "ab", "a","a",4 };
	rep.store(of111);
	//assert(rep.getAll().size() == 1);
	Oferta of12{ "ab", "aa","aa",14 };
	rep.updateOferta(of12, "ab");
	Oferta of2 = rep.find("ab");
	assert(of2.getDestinatie() == "aa");
	assert(of2.getTip() == "aa");
	assert(of2.getPret() == 14);
	try {
		rep.updateOferta(Oferta{ "c","c","C",5 }, "c");
	}
	catch (OfertaRepoException&) {
		assert(true);
	}
}

void testAll() {
	testeRepo();
	testCtr();
	testValidator();
	testeWishlist();
	testeUndo();
	testeFisiere();
	testeRepoMap();
}

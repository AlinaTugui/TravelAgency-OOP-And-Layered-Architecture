#include "cos.h"
#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock
#include <fstream>

void Cos::golesteCos() {
	{
		cos.clear();
	}
	notifyObservers();
}


void Cos::addCos(string denumire) {
	for (const auto& of : cos) {
		if (of.getDenumire() == denumire)
			throw OfertaCosException("Oferta cu denumirea: " + denumire + " exista deja in cos!\n");
	}
	cos.push_back(rep.find(denumire));
	notifyObservers();
}


void Cos::genereazaCos(int nr) {
	const size_t number = nr;
	if (nr <= 0)
		throw OfertaCosException("Numarul de oferte care doriti sa fie generate trebuie sa fie mai mare decat 0\n");
	if (number > rep.getAll().size())
		throw OfertaCosException("Nu exista suficiente oferte in lista\n");
	cos.clear();
	cos = rep.getAll();
	const auto seed = static_cast<size_t>(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(cos.begin(), cos.end(), std::default_random_engine(static_cast<unsigned int>(seed))); //amesteca vectorul 	
	cos.erase(cos.begin() + nr, cos.end());
	notifyObservers();
}

void Cos::exportHTML(const string& filename) {
	std::ofstream out{ "D:/faculta/sem2/poo/lab9/" + filename + ".html", std::ios::trunc };
	out << "<html><body>";
	for (const auto& of : cos) {
		out << of.getDenumire() << " ";
		out << of.getDestinatie() << " ";
		out << of.getPret() << " ";
		out << of.getTip() << " ";
		out << "<BR>";
	}
	out << "</body></html>";
}

//void export(string filename)
ostream& operator<<(ostream& out, const OfertaCosException& ex) {
	out << ex.msg;
	return out;
}
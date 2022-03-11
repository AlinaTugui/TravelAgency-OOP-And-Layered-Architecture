#pragma once
#include "oferta.h"
#include "ofertaRepo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	//destructorul e virtual pt a ne asigura ca daca dau delete se apeleaza destructorul
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga :public ActiuneUndo {
	Oferta ofAdaugata;
	Repository& rep;
public:
	UndoAdauga(Repository& rep, const Oferta& of) :rep{ rep }, ofAdaugata{ of } {}
	void doUndo() override {
		rep.deleteOferta(ofAdaugata.getDenumire());
	}
};

class UndoSterge :public ActiuneUndo {
	Oferta ofStearsa;
	Repository& rep;
public:
	UndoSterge(Repository& rep, const Oferta& of) : rep{ rep }, ofStearsa{ of } {}
	void doUndo() override {
		rep.store(ofStearsa);
	}
};

class UndoModifica : public ActiuneUndo {
	Oferta ofModificata;
	Repository& rep;
public:
	UndoModifica(Repository& rep, const Oferta& of) : rep{ rep }, ofModificata{ of } {}
	void doUndo() override {
		//Oferta of = rep.find(ofModificata.getDenumire());
		//rep.deleteOferta(of.getDenumire());
		//rep.store(ofModificata);
		rep.updateOferta(ofModificata, ofModificata.getDenumire());
	}

};
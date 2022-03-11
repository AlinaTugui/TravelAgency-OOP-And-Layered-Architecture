#pragma once
#include <string>
#include "oferta.h"
#include <vector>

using std::vector;
using std::string;
using std::ostream;
/*clasa de exceptii pentru validare*/
class ValidateException {
	vector<string> msgs;
public:
	ValidateException(const vector<string>& errors) :msgs{ errors } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
	vector<string> getMessage() const {
		return msgs;
	}

};

ostream& operator<<(ostream& out, const ValidateException& ex);

/*validator oferta*/
class OfertaValidator {
public:
	void validate(const Oferta& p);
};

//void testValidator();
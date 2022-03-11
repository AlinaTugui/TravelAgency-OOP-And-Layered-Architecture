#include "validator.h"
#include <assert.h>
#include <sstream>

void OfertaValidator::validate(const Oferta& of) {
	vector<string> msgs;
	if (of.getDenumire().size() == 0) msgs.push_back("Denumire vida!!!");
	if (of.getDestinatie().size() == 0) msgs.push_back("Destinatie vida!!!");
	if (of.getTip().size() == 0) msgs.push_back("Tip vid!!!");
	if (of.getPret() < 0) msgs.push_back("Pret negativ!!!");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

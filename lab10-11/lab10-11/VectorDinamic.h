#pragma once
#define INITIAL_CAPACITY 2


template <typename ElemType>
class IteratorVectorD;

template <typename ElemType>
class VectorDinamicOferta
{
public:
	/*
	* Constructor default
	*/
	VectorDinamicOferta();

	/*
	* Constructor de copiere
	*/
	VectorDinamicOferta(const VectorDinamicOferta& ot);

	/*
	* Eliberam memoria
	*/
	~VectorDinamicOferta();

	/*
	* Operator assignement
	* eleibereaza ce era in obiectul curent(this)
	* aloca spatiu pentru elemente
	* copiaza elemnte din other in this
	*/
	VectorDinamicOferta& operator=(const VectorDinamicOferta& ot);

	/*
	Move constructor
	Apelat daca construim un nou vector dintr-un r-value (ex temporary, expresie de la return)
	Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
	*/
	VectorDinamicOferta(VectorDinamicOferta&& ot); //rule of 5 

	/*
	Move assignment
	Similar cu move constructor
	Folosit la assignment
	*/
	VectorDinamicOferta& operator=(VectorDinamicOferta&& ot); //rule of 5

	void add(const ElemType& el);

	void stergere(int poz);

	ElemType& get(int poz) const;

	void set(int poz, const ElemType& el);

	int size() const;

	friend class IteratorVectorD<ElemType>;
	//functii care creeaza iteratori
	IteratorVectorD<ElemType> begin() const;
	IteratorVectorD<ElemType> end() const;

private:
	int lg;
	int cap;
	ElemType* elems;
	void ensureCapacity();

};

template<typename ElemType>
VectorDinamicOferta<ElemType>::VectorDinamicOferta() : elems{ new ElemType[INITIAL_CAPACITY] }, cap{ INITIAL_CAPACITY }, lg{ 0 }{

}



template<typename ElemType>
VectorDinamicOferta<ElemType>::VectorDinamicOferta(const VectorDinamicOferta<ElemType>& ot) {
	elems = new ElemType[ot.cap];
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];
	}
	lg = ot.lg;
	cap = ot.cap;
}

template<typename ElemType>
VectorDinamicOferta<ElemType>& VectorDinamicOferta<ElemType>::operator=(const VectorDinamicOferta<ElemType>& ot) {
	if (this == &ot) {
		return *this;//s-a facut l=l;
	}
	delete[] elems;
	elems = new ElemType[ot.cap];
	//copiez elementele
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];  //assignment din Pet
	}
	lg = ot.lg;
	cap = ot.cap;
	return *this;
}


template<typename ElemType>
VectorDinamicOferta<ElemType>::~VectorDinamicOferta() {
	delete[] elems;
}



template<typename ElemType>
VectorDinamicOferta<ElemType>::VectorDinamicOferta(VectorDinamicOferta&& ot) {
	// Copy the data pointer from other
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	// Release the data pointer from the source object so that  
	// the destructor does not free the memory multiple times.  
	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
}


template<typename ElemType>
VectorDinamicOferta<ElemType>& VectorDinamicOferta<ElemType>::operator=(VectorDinamicOferta<ElemType>&& ot) {
	if (this == &ot) {
		return *this;
	}
	delete[] elems;
	// Copy the data pointer from other
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	// Release the data pointer from the source object so that  
	// the destructor does not free the memory multiple times.  
	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
	return *this;
}

template<typename ElemType>
void VectorDinamicOferta<ElemType>::add(const ElemType& el) {
	ensureCapacity();//daca e nevoie mai alocam memorie
	elems[lg++] = el;
}


template<typename ElemType>
void VectorDinamicOferta<ElemType>::stergere(int poz) {
	lg--;
	for (int i = poz; i < lg; i++)
		elems[i] = elems[i + 1];

}


template<typename ElemType>
ElemType& VectorDinamicOferta<ElemType>::get(int poz) const {
	return elems[poz];
}

template<typename ElemType>
void VectorDinamicOferta<ElemType>::set(int poz, const ElemType& el) {
	elems[poz] = el;
}

template<typename ElemType>
int VectorDinamicOferta<ElemType>::size() const {
	return lg;
}

template<typename ElemType>
void VectorDinamicOferta<ElemType>::ensureCapacity() {
	if (lg < cap) {
		return; //mai avem loc
	}
	cap *= 2;
	ElemType* aux = new ElemType[cap];
	for (int i = 0; i < lg; i++) {
		aux[i] = elems[i];
	}
	delete[] elems;
	elems = aux;
}

template<typename ElemType>
IteratorVectorD<ElemType> VectorDinamicOferta<ElemType>::begin() const
{
	return IteratorVectorD<ElemType>(*this);
}

template<typename ElemType>
IteratorVectorD<ElemType> VectorDinamicOferta<ElemType>::end() const
{
	return IteratorVectorD<ElemType>(*this, lg);
}


/*clasa de iterator pe vectorul dinamic*/
template<typename ElemType>
class IteratorVectorD {
private:
	const VectorDinamicOferta<ElemType>& v;

	int poz = 0;
public:
	/*constructor implicit*/
	IteratorVectorD(const VectorDinamicOferta<ElemType>& v) noexcept;
	/*contructor de copiere*/
	IteratorVectorD(const VectorDinamicOferta<ElemType>& v, int poz)noexcept;
	/*validare iterator*/
	bool valid()const;
	/*functie care returneaza elementul de pe o pozitie data*/
	ElemType& element() const;
	/*functie pentru urmatorul element*/
	void next();
	/*suprascriu operatorii*/
	ElemType& operator*();
	IteratorVectorD& operator++();
	bool operator==(const IteratorVectorD& ot)noexcept;
	bool operator!=(const IteratorVectorD& ot)noexcept;
};

template<typename ElemType>
IteratorVectorD<ElemType>::IteratorVectorD(const VectorDinamicOferta<ElemType>& v) noexcept :v{ v } {}

template<typename ElemType>
IteratorVectorD<ElemType>::IteratorVectorD(const VectorDinamicOferta<ElemType>& v, int poz)noexcept : v{ v }, poz{ poz } {}

template<typename ElemType>
bool IteratorVectorD<ElemType>::valid()const {
	return poz < v.lg;
}

template<typename ElemType>
ElemType& IteratorVectorD<ElemType>::element() const {
	return v.elems[poz];
}

template<typename ElemType>
void IteratorVectorD<ElemType>::next() {
	poz++;
}

template<typename ElemType>
ElemType& IteratorVectorD<ElemType>::operator*() {
	return element();
}

template<typename ElemType>
IteratorVectorD<ElemType>& IteratorVectorD<ElemType>::operator++() {
	next();
	return *this;
}

template<typename ElemType>
bool IteratorVectorD<ElemType>::operator==(const IteratorVectorD<ElemType>& ot) noexcept {
	return poz == ot.poz;
}

template<typename ElemType>
bool IteratorVectorD<ElemType>::operator!=(const IteratorVectorD<ElemType>& ot)noexcept {
	return !(*this == ot);
}





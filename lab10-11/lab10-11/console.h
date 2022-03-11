#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qspinbox.h>

#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets\qformlayout.h>
#include <QtWidgets\qgridlayout.h>
#include <qtextedit.h>
#include <vector>
#include <string>
#include <qpainter.h>
#include <qdebug.h>
#include <qbrush.h>
#include "ofertaStore.h"
#include "oferta.h"
#include "observer.h"
#include <random>
#include "OferteTableViewModel.h"
using std::vector;
using std::string;

class CosOferteCrudGUI :public QWidget, public Observer {
private:
	Cos& cos;
	QListWidget* listActivitatiCos = new QListWidget;
	QPushButton* golire = new QPushButton("Golire cos");
	QPushButton* generare = new QPushButton("Genereaza cos");
	QLineEdit* genereazaBox = new QLineEdit;
	QSlider* sliderGen1 = new QSlider(Qt::Orientation::Horizontal);
	QLabel* labelGen = new QLabel;

	void reloadListaCos(const vector<Oferta>& activitati);
	void createCos();
	void initListeners();
public:
	CosOferteCrudGUI(Cos& cos) : cos{ cos } {
		cos.addObserver(this);
		createCos();
		reloadListaCos(cos.getCos());
		initListeners();
	}

	void update() override {
		reloadListaCos(cos.getCos());
	}

	~CosOferteCrudGUI() {
		cos.removeObserver(this);
	}

};


class CosReadOnlyGUI :public QWidget, public Observer {
private:
	Cos& cos;

public:
	CosReadOnlyGUI(Cos& cos) :cos{ cos } {
		cos.addObserver(this);
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		//int x = 100;
		//for (const auto& of : cos.getCos()) {
			/*p.drawRect(x, 200, 10, 30);
			x += 20;
			of.getDenumire() = of.getDenumire();*/
		ev = 0;
		int n = static_cast<int>(cos.getCos().size());
		for (int i = 0; i < n; i++) {
			std::random_device rdm;
			std::mt19937 eng{ rdm() };
			std::uniform_int_distribution<int> random(0, 1);
			int r = random(eng);
			int x = rand() % 512, y = rand() % 512;
			if (r == 0) /*p.drawLine(rand() % 512, rand() % 512, rand() % 512 - x, rand() % 512 - y)*/
			{};
			if (r == 1) /*p.drawRect(rand() % 512, rand() % 512, rand() % 512 - x, rand() % 512 - y)*/
			{};
			p.drawImage(x,y,QImage("C:/Users/Admin/Downloads/rainbow.png"));
		}
}

	void update() override {
		repaint();
	}

	~CosReadOnlyGUI() {
		cos.removeObserver(this);
	}


};


//class CosGui : public QWidget {
//private:
//	OfertaStore& ctr;
//
//	QListWidget* listCos = new QListWidget;
//	QPushButton* adaugaCos = new QPushButton{ "Adauga" };
//	QPushButton* genereazaCos = new QPushButton{ "Genereaza" };
//	QPushButton* golesteCos = new QPushButton{ "Goleste" };
//	QPushButton* exportCos = new QPushButton{ "Export" };
//	QPushButton* exit = new QPushButton{ "Exit" };
//	QPushButton* refresh = new QPushButton{ "Refresh" };
//
//	QLineEdit* editAdauga = new QLineEdit;
//	QLineEdit* editGenereaza = new QLineEdit;
//	QLineEdit* editExport = new QLineEdit;
//	QLineEdit* editNumarActiv = new QLineEdit;
//
//	void createUICos();
//	void reloadListCos(const vector<Oferta>& oferte);
//	void initListenersCos();
//
//public:
//	CosGui(OfertaStore& ctr) : ctr{ ctr } {
//		createUICos();
//		reloadListCos(ctr.getCos());
//		initListenersCos();
//	}
//	void adauga_cos();
//	void genereaza_cos();
//	void exporta_cos();
//};



class ConsolUI : public QWidget
{
private:
	OfertaStore& ctr;
	OferteTableModel* model;
	//QWidget* window = new QWidget;
	QListWidget* listOferte = new QListWidget;
	//QTableWidget* tabel = new QTableWidget{ 0,1 };
	QTableView* tabel = new QTableView();
	QPushButton* adauga = new QPushButton("Adauga oferta");
	QPushButton* sterge = new QPushButton("Sterge oferta");
	QPushButton* modifica = new QPushButton("Modifica oferta");
	QPushButton* cauta = new QPushButton("Cauta oferta");
	QPushButton* filtrarePretMaiMic = new QPushButton("Filtrare dupa pret minim");
	QPushButton* filtrareDestinatie = new QPushButton("Filtrare dupa destinatie");
	QPushButton* sortareDenumire = new QPushButton("Sortare dupa denumire");
	QPushButton* sortareDestinatie = new QPushButton("Sortare dupa destinatie");
	QPushButton* sortareTipPret = new QPushButton("Sortare dupa tip+pret");

	//CosGui* COS = new CosGui{ ctr };
	QPushButton* adaugaCos = new QPushButton("Adauga in Cos");
	QPushButton* raport = new QPushButton("Raport");
	QPushButton* golesteCos = new QPushButton("Goleste Cos");
	QPushButton* genereazaCos = new QPushButton("Genereaza Cos");
	QLineEdit* genereazaBox = new QLineEdit;
	QPushButton* exportCos = new QPushButton("Exporta cos in fisier HTML");
	QPushButton* vizualizareCosGUI = new QPushButton("Cos CRUD GUI");
	QPushButton* vizualizareCosReadOnly = new QPushButton("Cos Read-Only GUI");
	QLineEdit* exportBox = new QLineEdit;

	QPushButton* undo = new QPushButton("Undo");
	QPushButton* exit = new QPushButton("Exit");
	QPushButton* refresh = new QPushButton("Refresh");

	QLineEdit* lineEditDenumire = new QLineEdit;
	QLineEdit* lineEditDestinatie = new QLineEdit;
	QLineEdit* lineEditPret = new QLineEdit;
	QLineEdit* lineEditTip = new QLineEdit;
	QLineEdit* lineEditDenumire1 = new QLineEdit;

	QLineEdit* findBox = new QLineEdit;
	QLineEdit* filterPretMaiMicBox = new QLineEdit;
	QLineEdit* filterPretBox = new QLineEdit;
	QLineEdit* filterDestinatieBox = new QLineEdit;
	QTableWidget* tabel_raport = new QTableWidget{ 0,2 };
	QWidget* raportA = new QWidget;

	QSlider* sliderGen = new QSlider(Qt::Orientation::Horizontal);
	QSpinBox* spinPret = new QSpinBox;
	QSpinBox* spinPretMin = new QSpinBox;
	QLabel* labelGen = new QLabel;
	void createUI();
	void reloadList(const vector<Oferta>& oferte);
	//void reloadListTable(const vector<Oferta>& oferte);
	void initListeners();

public:
	ConsolUI(OfertaStore& ctr) :ctr{ ctr } {
		createUI();
		model = new OferteTableModel{ctr.getAll()};
		reloadList(ctr.getAll());
		//reloadListTable(ctr.getAll());
		initListeners();
	}
	void startUI();

	void adaugaUI();

	void deleteUI();

	void updateUI();

	void undoUI();

	void cautaUI();

	void filterPretMaiMic();

	void filterDestinatie();
	
	void raportOferte();
	
	void filtrareDestinatieColorare();

	void clearFields();

	void adaugaInCos();

	void vizualizareOferteCosGUI();

	void vizualizareCosOferteReadOnly();

	void golireCos();

	void generareCos();

	void exportHTML();
};


//class ConsolUI {
	//OfertaStore& ctr;
	/*
	Citeste datele de la tastatura si adauga Oferta
	arunca exceptie daca: nu se poate salva, nu e valida
	*/
	//void adaugaUI();
	/*
	Tipareste o lista de oferte la consola
	*/
	//void tipareste(const vector<Oferta>& oferte);
	/*functie pentru interfata utilizator care sterge o oferta pentru care se da denumirea
	*daca oferta nu se afla in lista ridica exceptie
	*/
	//void deleteUI();
	/*functie pentru interfata utilizator care actualizeaza o oferta pentru care se da denumirea cu noul pret, noul tip si noua destinatie
	daca datele nu sunt valide se ridica exceptie
	*/
	//void updateUI();
	/*functie de cautare a unei oferte pentru interfata utilizator
	* se cauta o oferta dupa denumire(identificator unic)
	*/
	//void cautaUI();

	//void raportUI();
	//void exportHTMLUI();
	//void undoUI();
//public:
	//ConsolUI(OfertaStore& ctr) :ctr{ ctr } {
	//}
	//nu permitem copierea obiectelor
	//ConsolUI(const ConsolUI& ot) = delete;

	//void start();
//};
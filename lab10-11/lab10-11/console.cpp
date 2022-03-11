#include "oferta.h"
#include "console.h"
#include <iostream>
#include <string>
#include "VectorDinamic.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>

#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets\qformlayout.h>
#include <QtWidgets\qgridlayout.h>
#include <qtextedit.h>
#include <QMainWindow>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include <qbrush.h>
#include <vector>
#include <string>

using std::vector;
using std::cout;
using std::cin;

void ConsolUI::createUI() {
	QHBoxLayout* horizontal = new QHBoxLayout;
	setLayout(horizontal);

	QWidget* details = new QWidget;
	QFormLayout* fL = new QFormLayout;
	details->setLayout(fL);
	QLabel* titluLabel = new QLabel("Denumire");
	fL->addRow(titluLabel, lineEditDenumire);
	QLabel* descriereLabel = new QLabel("Destinatie");
	fL->addRow(descriereLabel, lineEditDestinatie);
	QLabel* typeLabel = new QLabel("Pret");
	fL->addRow(typeLabel, spinPret);
	QLabel* durataLabel = new QLabel("Tip");
	fL->addRow(durataLabel, lineEditTip);

	QWidget* formButton = new QWidget;
	QVBoxLayout* vertical = new QVBoxLayout;
	formButton->setLayout(vertical);

	QWidget* butoaneCrud = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout();
	butoaneCrud->setLayout(layout);
	layout->addWidget(adauga);
	layout->addWidget(modifica);
	layout->addWidget(sterge);

	QWidget* butoaneFiltrare = new QWidget;
	QFormLayout* layout2 = new QFormLayout();
	butoaneFiltrare->setLayout(layout2);
	layout2->addRow(cauta, findBox);
	layout2->addRow(filtrarePretMaiMic, spinPretMin);
	layout2->addRow(filtrareDestinatie, filterDestinatieBox);

	QWidget* butoaneSortare = new QWidget;
	QHBoxLayout* layout3 = new QHBoxLayout();
	butoaneSortare->setLayout(layout3);
	layout3->addWidget(sortareDenumire);
	layout3->addWidget(sortareDestinatie);
	layout3->addWidget(sortareTipPret);

	//QTableWidgetItem* itemT = new QTableWidgetItem{ QString::fromStdString("denumire") };
	//tabel->setHorizontalHeaderItem(0, itemT);

	//tabel->setModel(model);
	//horizontal->addWidget(tabel);

	QWidget* butoaneCosRaport = new QWidget;
	QFormLayout* layout5 = new QFormLayout();
	butoaneCosRaport->setLayout(layout5);
	//layout5->addRow(cos);
	layout5->addRow(raport);

	vertical->addWidget(details);
	vertical->addWidget(butoaneCrud);
	vertical->addWidget(butoaneSortare);
	vertical->addWidget(butoaneFiltrare);
	vertical->addWidget(butoaneCosRaport);

	vertical->setAlignment(Qt::AlignTop);

	QWidget* lstButton = new QWidget;
	QVBoxLayout* vertical2 = new QVBoxLayout;
	lstButton->setLayout(vertical2);

	QWidget* butoaneUndoExit = new QWidget;
	QHBoxLayout* layout4 = new QHBoxLayout();
	butoaneUndoExit->setLayout(layout4);
	layout4->addWidget(undo);
	layout4->addWidget(exit);
	layout4->addWidget(refresh);

	vertical2->addWidget(listOferte);
	vertical2->addWidget(butoaneUndoExit);

	horizontal->addWidget(formButton);
	horizontal->addWidget(lstButton);

	//fereastra raport
	int x = raportA->width() * 0.5;
	int y = raportA->height() * 0.8;
	raportA->setFixedSize(x, y);
	QVBoxLayout* raport_ly = new QVBoxLayout;
	raportA->setLayout(raport_ly);
	raport_ly->addWidget(tabel_raport);
	tabel_raport->setHorizontalHeaderItem(0, new QTableWidgetItem("Destinatie"));
	tabel_raport->setHorizontalHeaderItem(1, new QTableWidgetItem("Nr oferte"));

	QFormLayout* layout6 = new QFormLayout();

	QWidget* butoaneCos = new QWidget;
	QVBoxLayout* vertical3 = new QVBoxLayout;
	butoaneCos->setLayout(vertical3);
	layout6->addRow(adaugaCos,lineEditDenumire1);
	vertical3->addLayout(layout6);
	vertical3->addWidget(golesteCos);

	QWidget* butoaneC = new QWidget;
	QFormLayout* layoutC = new QFormLayout();
	butoaneC->setLayout(layoutC);
	layoutC->addRow(genereazaCos, sliderGen);
	layoutC->addRow("Valoare slider: ", labelGen);
	labelGen->setText("1");
	layoutC->addRow(exportCos, exportBox);

	QWidget* cosButoane = new QWidget;
	QVBoxLayout* vertical4 = new QVBoxLayout;
	cosButoane->setLayout(vertical4);
	vertical4->addWidget(vizualizareCosGUI);
	vertical4->addWidget(vizualizareCosReadOnly);

	vertical3->addWidget(butoaneC);
	vertical3->addWidget(cosButoane);
	vertical3->setAlignment(Qt::AlignTop);
	vertical->addWidget(butoaneCos);

	sliderGen->setMinimum(1);
	sliderGen->setMaximum(30);
	sliderGen->setValue(1);

	spinPretMin->setMaximum(100000000);
	spinPret->setMaximum(100000000);
}

void ConsolUI::reloadList(const vector<Oferta>& oferte) {
	listOferte->clear();
	//tabel->clear();
	//tabel->setRowCount(0);
	for (const auto& of : oferte) {
		auto denumire = of.getDenumire();
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(of.getDenumire()));
		item->setData(Qt::UserRole, QString::fromStdString(denumire));
		listOferte->addItem(item);
	//	//pentru tabel
	//	QTableWidgetItem* itemT = new QTableWidgetItem{ QString::fromStdString(denumire) };
	//	tabel->insertRow(tabel->rowCount());
	//	tabel->setItem(tabel->rowCount() - 1, 0, itemT);
	}
	model->setOferte(oferte);

}

void ConsolUI::startUI() {
	int x = width() * 2;
	int y = height() * 1.4;
	setFixedSize(x, y);
	QPalette p(palette());
	p.setColor(QPalette::Window, QColor::QColor("#16A085"));
	p.setColor(QPalette::Base, QColor::QColor("#ABEBC6"));
	p.setColor(QPalette::WindowText, QColor::QColor("#0B1D4D"));
	setPalette(p);

	show();
}

void ConsolUI::initListeners() {

	QObject::connect(exit, &QPushButton::clicked, [&]() {
		QMessageBox::information(nullptr, "Info", "Apasati <<OK>> pentru a iesi din aplicatie");
		close();
		});

	QObject::connect(adauga, &QPushButton::clicked, [&]() {adaugaUI(); });

	QObject::connect(modifica, &QPushButton::clicked, this, &ConsolUI::updateUI);
	QObject::connect(sliderGen, &QSlider::valueChanged, [this]() {
		labelGen->setText(QString::number(sliderGen->value()));
		});
	//QObject::connect(tabel, &QTableWidget::itemSelectionChanged, [&]() {
	//	//returneaza un tabel cu elementele selectate
	//	auto selectia = tabel->selectedItems();
	//	if (selectia.isEmpty())
	//	{
	//		lineEditDenumire->setText("");
	//		lineEditDestinatie->setText("");
	//		lineEditPret->setText("");
	//		lineEditTip->setText("");
	//	}
	//	else {
	//		auto selectItem = selectia.at(0);
	//		auto denumire = selectItem->text();
	//		lineEditDenumire->setText(denumire);
	//		//auto id = selectItem->data(Qt::UserRole);
	//		auto of = ctr.cauta(denumire.toStdString());
	//		lineEditDestinatie->setText(QString::fromStdString(of.getDestinatie()));
	//		spinPret->setValue((of.getPret()));
	//		lineEditTip->setText(QString::fromStdString(of.getTip()));
	//	}
	//	});
	QObject::connect(tabel->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tabel->selectionModel()->selectedIndexes().isEmpty()) {
			lineEditDenumire->setText("");
			lineEditDestinatie->setText("");
			lineEditPret->setText("");
			lineEditTip->setText("");
			return;
		}
		int selRow = tabel->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = tabel->model()->index(selRow, 0);
		//auto cel1Index = tabel->model()->index(selRow, 1);
		auto cellValue = tabel->model()->data(cel0Index, Qt::DisplayRole).toString();
		lineEditDenumire->setText(cellValue);
		auto of = ctr.cauta(cellValue.toStdString());
		lineEditDestinatie->setText(QString::fromStdString(of.getDestinatie()));
		lineEditDestinatie->setText(QString::fromStdString(of.getDestinatie()));
		spinPret->setValue((of.getPret()));
		lineEditTip->setText(QString::fromStdString(of.getTip()));
		});
	QObject::connect(sterge, &QPushButton::clicked, this, &ConsolUI::deleteUI);

	QObject::connect(sortareDenumire, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortByDenumire());
		});

	QObject::connect(sortareDestinatie, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortByDestinatie());
		});

	QObject::connect(sortareTipPret, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortByTypePrice());
		});

	QObject::connect(filtrarePretMaiMic, &QPushButton::clicked, this, &ConsolUI::filterPretMaiMic);

	QObject::connect(filtrareDestinatie, &QPushButton::clicked, this, &ConsolUI::filtrareDestinatieColorare);

	QObject::connect(undo, &QPushButton::clicked, this, &ConsolUI::undoUI);

	QObject::connect(cauta, &QPushButton::clicked, this, &ConsolUI::cautaUI);

	QObject::connect(raport, &QPushButton::clicked, this, &ConsolUI::raportOferte);

	/*QObject::connect(cos, &QPushButton::clicked, this, [&]() {
		COS->show();
		});*/


	QObject::connect(listOferte, &QListWidget::itemSelectionChanged, [&]() {
		//returneaza o lista cu elementele selectata
		auto selectia = listOferte->selectedItems();
		if (selectia.isEmpty())
		{
			lineEditDenumire->setText("");
			lineEditDestinatie->setText("");
			lineEditPret->setText("");
			lineEditTip->setText("");
		}
		else {
			auto selectItem = selectia.at(0);
			auto denumire = selectItem->text();
			lineEditDenumire->setText(denumire);
			//auto id = selectItem->data(Qt::UserRole);
			auto of = ctr.cauta(denumire.toStdString());
			lineEditDestinatie->setText(QString::fromStdString(of.getDestinatie()));
			spinPret->setValue((of.getPret()));
			lineEditTip->setText(QString::fromStdString(of.getTip()));
		}
		});

	QObject::connect(refresh, &QPushButton::clicked, [=]() {reloadList(ctr.getAll()); });
	QObject::connect(adaugaCos, &QPushButton::clicked, [&]() {adaugaInCos(); });

	QObject::connect(vizualizareCosGUI, &QPushButton::clicked, [&]() {vizualizareOferteCosGUI(); });

	QObject::connect(vizualizareCosReadOnly, &QPushButton::clicked, [&]() {vizualizareCosOferteReadOnly(); });

	QObject::connect(golesteCos, &QPushButton::clicked, [&]() {golireCos(); });

	QObject::connect(genereazaCos, &QPushButton::clicked, [&]() {generareCos(); });

	QObject::connect(exportCos, &QPushButton::clicked, [&]() {exportHTML(); });
}

void ConsolUI::adaugaUI() {

	auto denumire = lineEditDenumire->text();
	auto destinatie = lineEditDestinatie->text();
	auto pret = spinPret->value();
	auto tip = lineEditTip->text();
	try {
		ctr.addOferta( denumire.toStdString(), destinatie.toStdString(), tip.toStdString(), pret);
		reloadList(ctr.getAll());
	}
	catch (const OfertaRepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
	catch (ValidateException& ex) {
		for (auto error : ex.getMessage())
			QMessageBox::warning(this, "Warning", QString::fromStdString(error));
	}
	cout << "add press";
}

void ConsolUI::deleteUI() {
	auto denumire = lineEditDenumire->text();
	try {
		ctr.deleteOfertaStore(denumire.toStdString());
		reloadList(ctr.getAll());
	}
	catch (const OfertaRepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void ConsolUI::updateUI() {
	auto denumire = lineEditDenumire->text();
	auto destinatie = lineEditDestinatie->text();
	auto pret = spinPret->value();
	auto tip = lineEditTip->text();

	try {
		ctr.updateOfertaStore( denumire.toStdString(), destinatie.toStdString(), tip.toStdString(), pret);
		reloadList(ctr.getAll());
	}
	catch (const OfertaRepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
	catch (ValidateException& ex) {
		for (auto error : ex.getMessage())
			QMessageBox::warning(this, "Warning", QString::fromStdString(error));
	}
}

void ConsolUI::undoUI() {
	try {
		ctr.undo();
		reloadList(ctr.getAll());
	}
	catch (const OfertaRepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}

}

void ConsolUI::filterDestinatie() {
	auto destinatie = filterDestinatieBox->text();
	if (filterDestinatieBox->text().toStdString() == "")
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Campul dupa care doriti sa filtrati este vid"));
	else {
		reloadList(ctr.filtrareDestinatie(destinatie.toStdString()));
	}
}
void ConsolUI::filterPretMaiMic() {
	int pret = spinPretMin->value();
	if (filterPretMaiMicBox->text().toInt() < 0)
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Campul dupa care doriti sa filtrati este negativ"));
	else {
		reloadList(ctr.filtrarePretMaiMic(pret));
	}
}

void ConsolUI::cautaUI() {
	auto denumire = findBox->text();
	try {
		Oferta of = ctr.cauta(denumire.toStdString());
		lineEditDenumire->setText(QString::fromStdString(of.getDenumire()));
		lineEditDestinatie->setText(QString::fromStdString(of.getDestinatie()));
		spinPret->setValue(of.getPret());
		lineEditTip->setText(QString::fromStdString(of.getTip()));
	}
	catch (const OfertaRepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void ConsolUI::raportOferte() {
	auto dict = ctr.numarOferteDestinatie();
	tabel_raport->setRowCount(0);
	for (const auto& pair : dict)
	{
		auto dest = pair.first;
		auto nr_of = pair.second.get_nr_oferte();
		QTableWidgetItem* titem1 = new QTableWidgetItem{ QString::fromStdString(dest) };
		QTableWidgetItem* titem2 = new QTableWidgetItem{ QString::number(nr_of) };
		tabel_raport->insertRow(tabel_raport->rowCount());
		tabel_raport->setItem(tabel_raport->rowCount() - 1, 0, titem1);
		tabel_raport->setItem(tabel_raport->rowCount() - 1, 1, titem2);
	}
	raportA->show();
}

void ConsolUI::filtrareDestinatieColorare() {
	auto destinatie = filterDestinatieBox->text();
	if (filterDestinatieBox->text().toStdString() == "")
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Campul dupa care doriti sa filtrati este vid"));
	else {
		reloadList(ctr.getAll());
		auto lista_oferte = ctr.filtrareDestinatie(destinatie.toStdString());
		for (const auto& of : lista_oferte) {
			auto items = listOferte->findItems(QString::fromStdString(of.getDenumire()), Qt::MatchExactly);
			items[0]->setBackground(QColor("green"));
		}
	}
}

//cos
//void CosGui::createUICos() {
//	QHBoxLayout* horizontal = new QHBoxLayout;
//	setLayout(horizontal);
//
//	QWidget* details = new QWidget;
//	QFormLayout* fL = new QFormLayout;
//	details->setLayout(fL);
//
//	QWidget* formButton = new QWidget;
//	QVBoxLayout* vertical = new QVBoxLayout;
//	formButton->setLayout(vertical);
//
//	QWidget* butoaneCrud = new QWidget;
//	QFormLayout* layout = new QFormLayout();
//	butoaneCrud->setLayout(layout);
//	layout->addRow(adaugaCos, editAdauga);
//	layout->addRow(genereazaCos, editGenereaza);
//	layout->addRow(exportCos, editExport);
//
//	vertical->addWidget(butoaneCrud);
//	vertical->setAlignment(Qt::AlignTop);
//
//	QWidget* lstButton = new QWidget;
//	QVBoxLayout* vertical2 = new QVBoxLayout;
//	lstButton->setLayout(vertical2);
//
//	QWidget* butoaneExitRefreshGoleste = new QWidget;
//	QHBoxLayout* layout4 = new QHBoxLayout();
//	butoaneExitRefreshGoleste->setLayout(layout4);
//	layout4->addWidget(golesteCos);
//	layout4->addWidget(exit);
//	layout4->addWidget(refresh);
//
//	vertical2->addWidget(listCos);
//	vertical2->addWidget(butoaneExitRefreshGoleste);
//
//	horizontal->addWidget(formButton);
//	horizontal->addWidget(lstButton);
//}
//
//void CosGui::reloadListCos(const vector<Oferta>& oferte)
//{
//	listCos->clear();
//	for (const auto& of : oferte) {
//		auto denumire = of.getDenumire();
//		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(of.getDenumire()));
//		item->setData(Qt::UserRole, QString::fromStdString(denumire));
//		listCos->addItem(item);
//	}
//}
//
//void CosGui::initListenersCos()
//{
//	QObject::connect(exit, &QPushButton::clicked, this, [=]() {
//		QMessageBox::information(this, "Info", "Apasati <<OK>> pentru a reveni la meniul principal");
//		close();
//		});
//	QObject::connect(golesteCos, &QPushButton::clicked, this, [=]() {
//		ctr.golesteCos();
//		reloadListCos(ctr.getCos());
//		});
//	QObject::connect(adaugaCos, &QPushButton::clicked, this, &CosGui::adauga_cos);
//	QObject::connect(genereazaCos, &QPushButton::clicked, this, &CosGui::genereaza_cos);
//	QObject::connect(exportCos, &QPushButton::clicked, this, &CosGui::exporta_cos);
//	QObject::connect(refresh, &QPushButton::clicked, this, [=]() {
//		editAdauga->setText("");
//		editExport->setText("");
//		editGenereaza->setText("");
//		});
//}

void ConsolUI::adaugaInCos()
{
	auto denumire = lineEditDenumire1->text().toStdString();
	if (denumire == "")
		QMessageBox::warning(this, "Eroare", "Camp titlu vid!");
	else {
		try
		{
			ctr.addCos(denumire);
			//reloadListCos(ctr.getCos());
		}
		catch (const OfertaCosException& ex)
		{
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMessage()));
		}
		catch (const OfertaRepoException& ex)
		{
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMessage()));
		}
	}
}

void ConsolUI::generareCos()
{
	//bool ok;
	auto nr = sliderGen->value();
	/*if (ok == false)
	{
		QMessageBox::warning(this, "Eroare", "Numar invalid!");
	}*/
	/*else*/
	{
		try {
			ctr.genereazaCos(nr);
			//reloadListCos(ctr.getCos());
		}
		catch (const OfertaCosException& ex)
		{
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMessage()));
		}
		catch (const OfertaRepoException& ex)
		{
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMessage()));
		}
	}
}

void ConsolUI::exportHTML()
{
	auto numefisier = exportBox->text().toStdString();
	if (numefisier == "")
		QMessageBox::warning(this, "Eroare", "Camp vid! Introdu un nume de fisier!");
	else
		ctr.exportHTML(numefisier);
}

void CosOferteCrudGUI::createCos()
{
	QVBoxLayout* vertical = new QVBoxLayout;
	setLayout(vertical);
	vertical->addWidget(listActivitatiCos);

	sliderGen1->setMinimum(1);
	sliderGen1->setMaximum(30);
	sliderGen1->setValue(1);

	QWidget* generareWidget = new QWidget;
	QFormLayout* layoutC = new QFormLayout();
	generareWidget->setLayout(layoutC);
	layoutC->addRow(generare, sliderGen1);
	layoutC->addRow("Valoare slider: ", labelGen);
	labelGen->setText("1");
	QWidget* butoane = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout();
	butoane->setLayout(layout);

	layout->addWidget(golire);

	vertical->addWidget(butoane);
	vertical->addWidget(generareWidget);
}

void CosOferteCrudGUI::reloadListaCos(const vector<Oferta>& oferte)
{
	listActivitatiCos->clear();
	for (const auto& of : oferte) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(of.getDenumire() + " " + of.getDestinatie() + " " + of.getTip() + " " + std::to_string(int(of.getPret()))));
		listActivitatiCos->addItem(item);

	}
}

void CosOferteCrudGUI::initListeners()
{
	QObject::connect(golire, &QPushButton::clicked, [&]() {
		cos.golesteCos();
		reloadListaCos(cos.getCos());
		});

	QObject::connect(generare, &QPushButton::clicked, [&]() {
		int nr = sliderGen1->value();
		try {
			cos.genereazaCos(nr);
		}
		catch (const OfertaCosException& ex)
		{
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMessage()));
		}
		catch (const OfertaRepoException& ex)
		{
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.getMessage()));
		}
		});
	QObject::connect(sliderGen1, &QSlider::valueChanged, [this]() {
		labelGen->setText(QString::number(sliderGen1->value()));
		});
}

void ConsolUI::vizualizareOferteCosGUI()
{
	auto listaCos = new CosOferteCrudGUI(ctr.getCosCurent());
	listaCos->show();
}

void ConsolUI::vizualizareCosOferteReadOnly()
{
	auto readOnlyGUI = new CosReadOnlyGUI(ctr.getCosCurent());
	readOnlyGUI->show();
}

void ConsolUI::golireCos()
{
	ctr.getCosCurent().golesteCos();
}
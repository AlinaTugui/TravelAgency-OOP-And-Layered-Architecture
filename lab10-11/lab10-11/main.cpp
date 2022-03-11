#include "lab1011.h"
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
#include "ofertaRepo.h"
#include "ofertaStore.h"
#include "console.h"
#include "teste.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	//OfertaRepo rep;
	OfertaRepoFile rep{ "oferte.txt" };
	//OfertaRepoMap rep{ 0.5 };
	OfertaValidator val;
	Cos cos{ rep };
	//testAll();
	OfertaStore ctr{ rep,val,cos };
	//adaugaCateva(ctr);//adaug cateva oferte
	ConsolUI ui{ ctr };
	ui.startUI();
    return a.exec();
}

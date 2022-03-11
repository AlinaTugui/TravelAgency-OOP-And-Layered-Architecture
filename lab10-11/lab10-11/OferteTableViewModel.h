#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qlistview.h>
#include <QtWidgets/qtreeview.h>
#include <QtWidgets/qboxlayout.h>
#include <QAbstractTableModel>
#include <qfilesystemmodel.h>
#include <qdebug.h>
#include <vector>
#include "oferta.h"
using std::vector;
class OferteTableModel :public QAbstractTableModel {
	std::vector<Oferta> oferte;
public:
	OferteTableModel(const std::vector<Oferta>& oferte) :oferte{ oferte } {
	}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		parent;
		return static_cast<int>(oferte.size());
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		parent;
		return 1;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Oferta of = oferte[index.row()];
			//qDebug() << "row:" << index.row() << " col:" << index.column();
			if (index.column() == 0) {
				return QString::fromStdString(of.getDenumire());
			}
		}
		return QVariant{};
	}

	void setOferte(const vector<Oferta> oferta) {
		this->oferte = oferta;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}
};

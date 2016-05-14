#ifndef COINSCATALOG_H
#define COINSCATALOG_H

#include <QApplication>
#include <QScrollArea>
#include <QMainWindow>
#include <QTextCodec>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QSignalMapper>
#include <QPushButton>
#include <iostream>
#include <map>
#include <string>
#include "coin.h"
#include "coinwindow.h"
#include "roundcoin.h"
#include "squarecoin.h"
#include "coinsmanager.h"
#include "coinwindowmanager.h"
#include "removecoinwindow.h"

class CoinsCatalog : public QMainWindow
{
	Q_OBJECT
private:
	CoinsManager *coinsmanager;
	QLabel* title, *foot;
	QScrollArea* scrollArea;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	QWidget* widget;
	QWidget *menuWidget;
	QHBoxLayout *menuLayout;
	QWidget *coinsListWidget;
	QVBoxLayout *coinsListLayout;
	QPushButton *addRoundCoinButton;
	QPushButton *addSquareCoinButton;
	QPushButton *refreshButton;

public:
	CoinsCatalog();

public slots:
	void loadCoinsList();
	void removeCoin(int);
	void whetherRemoveCoin(int);
};

#endif // COINSCATALOG_H

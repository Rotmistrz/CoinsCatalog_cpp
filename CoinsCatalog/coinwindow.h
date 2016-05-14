#pragma once
#include <QMainWindow>
#include <QTextCodec>
#include <QHBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QDialog>
#include <QPlainTextEdit>
#include <QWindow>
#include <QPushButton>
#include <QMessageBox>
#include <string>
#include "functions.h"
#include "coin.h"
#include "roundcoin.h"
#include "squarecoin.h"
#include "coinsmanager.h"

class CoinWindow : public QDialog
{
	Q_OBJECT

private:
	Coin* coin;
	CoinsManager* coinsmanager;
	QWidget *form;
	QFormLayout *formLayout;
	QWidget *dimensions;
	QHBoxLayout *dimensionsLayout;

	QLineEdit *faceValue;
	QLineEdit *name;
	QLineEdit *year;
	QLineEdit *weight;
	QLineEdit *diameter;
	QLineEdit *width;
	QLineEdit *height;
	QLineEdit *edge;
	QLineEdit *comment;

	QPushButton *button;

public:
	CoinWindow(Coin*, CoinsManager*);

private slots:
	bool save();

signals:
	void changed();
};

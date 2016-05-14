#pragma once
#include <QTextCodec>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <string>

class RemoveCoinWindow : public QDialog
{
Q_OBJECT

private:
	std::string title;
	QWidget* mainWidget;
	QVBoxLayout* mainLayout;
	QHBoxLayout* buttons;
	QLabel* question;
	QPushButton* yes;
	QPushButton* no;

public:
	RemoveCoinWindow(std::string);
	~RemoveCoinWindow();

public slots:
	void accepted();

signals:
	void remove();
};


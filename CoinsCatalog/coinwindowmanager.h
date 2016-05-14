#pragma once
#include <QObject>
#include <QAction>
#include "coin.h"
#include "coinwindow.h"
#include "coinsmanager.h"

class CoinWindowManager : public QObject
{
Q_OBJECT

private:
	Coin* coin;
	CoinsManager* coinsmanager;
	CoinWindow* coinwindow;

public:
	CoinWindowManager(Coin*, CoinsManager*);
	~CoinWindowManager();

public slots:
	void showWindow();
	void emitSignal();

signals:
	void changed();
};


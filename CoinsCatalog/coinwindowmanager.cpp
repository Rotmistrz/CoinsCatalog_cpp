#include "coinwindowmanager.h"


CoinWindowManager::CoinWindowManager(Coin* coin, CoinsManager* coinsmanager) : coin(coin), coinsmanager(coinsmanager)
{

}


CoinWindowManager::~CoinWindowManager()
{
}

void CoinWindowManager::showWindow() {
	coinwindow = new CoinWindow(coin, coinsmanager);
	coinwindow->show();

	connect(coinwindow, SIGNAL(changed()), this, SLOT(emitSignal()));
}

void CoinWindowManager::emitSignal() {
	emit changed();
}
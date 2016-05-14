#include "coinscatalog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setStyleSheet("QWidget { font-family: Verdana, sans-serif; font-size: 11px; } #foot { font-size: 10px; } #catalogTitle { font-size: 22px; font-family: 'Times New Roman'; } #coinBox { border: 1px solid #aaa; padding: 10px } #controlButton { padding: 2px; font-size: 9px; } QScrollArea { border: 0; border-top: 1px solid #aaa; border-bottom: 1px solid #aaa; } #coinTitle { font-size: 14px; margin: 0; padding: 0; } ");
	CoinsCatalog w;
	w.show();
	return app.exec();
}

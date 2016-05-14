#include "coinscatalog.h"

CoinsCatalog::CoinsCatalog() {
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

	scrollArea = new QScrollArea();

	mainWidget = new QWidget();
	mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	mainLayout = new QVBoxLayout();
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);

	title = new QLabel(tr("Katalog Monet"));
	title->setObjectName("catalogTitle");
	mainLayout->addWidget(title);
	mainLayout->addSpacerItem(new QSpacerItem(10, 10));

	menuLayout = new QHBoxLayout();

	mainWidget->setLayout(mainLayout);

	try {
		coinsmanager = new CoinsManager("coins.txt");
	}
	catch (std::string& e) {
		QMessageBox* msg = new QMessageBox();
		msg->setText(tr(e.c_str()));
		msg->show();
		return;
	}

	addRoundCoinButton = new QPushButton(tr("Dodaj monetę okrągłą"));
	addSquareCoinButton = new QPushButton(tr("Dodaj monetę prostokątną"));

	menuLayout->addWidget(addRoundCoinButton);
	menuLayout->addWidget(addSquareCoinButton);
	mainLayout->addLayout(menuLayout);

	coinsListWidget = new QWidget();
	coinsListLayout = new QVBoxLayout();
	coinsListLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addWidget(coinsListWidget);
	coinsListWidget->setLayout(coinsListLayout);
	mainLayout->addWidget(scrollArea);

	loadCoinsList();
	scrollArea->setWidget(coinsListWidget);
	scrollArea->setMinimumSize(450, 450);
	scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setCentralWidget(mainWidget);

	foot = new QLabel(tr("Copyright 2016 by Filip Markiewicz (www.filipmarkiewicz.pl)"));
	foot->setObjectName("foot");
	foot->setAlignment(Qt::AlignHCenter);

	mainLayout->addSpacerItem(new QSpacerItem(10, 5));
	mainLayout->addWidget(foot);

	RoundCoin* roundcoin = new RoundCoin(0, std::string(), std::string(), 0, 0, 0, std::string(), std::string());
	SquareCoin* squarecoin = new SquareCoin(0, std::string(), std::string(), 0, 0, Dimensions(0, 0), std::string(), std::string());

	CoinWindowManager* roundcoinmanager = new CoinWindowManager(roundcoin, coinsmanager);
	CoinWindowManager* squarecoinmanager = new CoinWindowManager(squarecoin, coinsmanager);

	connect(addRoundCoinButton, SIGNAL(clicked()), roundcoinmanager, SLOT(showWindow()));
	connect(addSquareCoinButton, SIGNAL(clicked()), squarecoinmanager, SLOT(showWindow()));
	connect(roundcoinmanager, SIGNAL(changed()), this, SLOT(loadCoinsList()));
	connect(squarecoinmanager, SIGNAL(changed()), this, SLOT(loadCoinsList()));
}

void CoinsCatalog::whetherRemoveCoin(int id) {
	RemoveCoinWindow* window = new RemoveCoinWindow("Czy na pewno chcesz usunąć tę monetę?");
	window->show();

	QSignalMapper* signalMapper = new QSignalMapper(this);
	connect(window, SIGNAL(remove()), signalMapper, SLOT(map()));
	signalMapper->setMapping(window, id);

	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(removeCoin(int)));
}

void CoinsCatalog::removeCoin(int id) {
	QMessageBox* msgBox = new QMessageBox();

	if (!coinsmanager->removeCoin(id)) {
		msgBox->setText(tr("Wystąpiły problemy podczas usuwania monety. Spróbuj ponownie później."));
	}
	try {
		coinsmanager->save();
	}
	catch (std::string& e) {
		msgBox->setText(e.c_str());
	}

	loadCoinsList();
}

void CoinsCatalog::loadCoinsList() {
	QLayoutItem *child;
	while ((child = coinsListLayout->takeAt(0)) != 0) {
		delete child->widget();
		delete child;
	}

	std::map<int, Coin*> coins = coinsmanager->getCoinsList();

	QSignalMapper* signalMapper = new QSignalMapper(this);

	for (std::map<int, Coin*>::reverse_iterator i = coins.rbegin(); i != coins.rend(); i++) {
		Coin* coin = i->second;
		QWidget* coinWidget = new QWidget();
		coinWidget->setObjectName("coinBox");
		QVBoxLayout* mainCoinLayout = new QVBoxLayout();

		CoinWindowManager* currentcoinmanager = new CoinWindowManager(coin, coinsmanager);

		QHBoxLayout* bar = new QHBoxLayout();
		
		QSpacerItem* spacer = new QSpacerItem(250, 10);
		QPushButton* editButton = new QPushButton(tr("Edytuj"));
		editButton->setObjectName("controlButton");
		QPushButton* removeButton = new QPushButton(tr("Usuń"));
		removeButton->setObjectName("controlButton");

		bar->addSpacerItem(spacer);
		bar->addWidget(editButton);
		bar->addWidget(removeButton);
		int id = coin->getId();

		connect(removeButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(removeButton, id);

		connect(editButton, SIGNAL(clicked()), currentcoinmanager, SLOT(showWindow()));
		connect(currentcoinmanager, SIGNAL(changed()), this, SLOT(loadCoinsList()));

		QVBoxLayout* coinLayout = new QVBoxLayout();
		
		coinWidget->setMinimumWidth(400);

		int _year = coin->getYear();

		std::string edge = "Rant: ";
		std::string comment = "Komentarz: ";
		std::string dimensions = (coin->isRound()) ? "Średnica: " : "Wymiary: ";
		std::string weight = "Masa: ";

		std::string _title = coin->getFaceValue();
		std::string _name = coin->getName();

		if (!_name.empty()) {
			if (!_title.empty()) _title += " - ";
			_title += to_string(_name);
		}

		if (_year != 0) {
			std::string s_year = to_string(abs(_year)) + "r.";
			if (_year < 0) s_year += " p.n.e.";
			
			_title += (!_title.empty()) ? " (" + s_year + ")" : s_year;
		}

		edge += (!(coin->getEdge()).empty()) ? coin->getEdge() : "-";
		comment += (!(coin->getComment()).empty()) ? coin->getComment() : "-";
		dimensions += (!(coin->getDimensionsAsString()).empty()) ? coin->getDimensionsAsString() + "mm" : "-";
		weight += (coin->getWeight() != 0) ? to_string(coin->getWeight()) + "g" : "-";

		if (!_title.empty()) {
			QLabel* title = new QLabel(tr(_title.c_str()));
			title->setObjectName("coinTitle");
			title->setAlignment(Qt::AlignHCenter);
			coinLayout->addWidget(title);
		}

		coinLayout->addWidget(new QLabel(tr(dimensions.c_str())));
		coinLayout->addWidget(new QLabel(tr(weight.c_str())));
		coinLayout->addWidget(new QLabel(tr(edge.c_str())));
		coinLayout->addWidget(new QLabel(tr(comment.c_str())));

		mainCoinLayout->addLayout(bar);
		mainCoinLayout->addLayout(coinLayout);
		coinWidget->setLayout(mainCoinLayout);

		coinsListLayout->addWidget(coinWidget);
	}

	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(whetherRemoveCoin(int)));
}
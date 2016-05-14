#include "coinwindow.h"

CoinWindow::CoinWindow(Coin* coin, CoinsManager* coinsmanager) : coin(coin), coinsmanager(coinsmanager)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

	QString title = QString();
	
	if (coin->getId() > 0) {
		title = "Edytuj monetę";
	}
	else {
		title = "Dodaj nową monetę";
	}

	setWindowTitle(title);
	setAttribute(Qt::WA_DeleteOnClose);

	setMinimumSize(320, 300);
	setMaximumSize(320, 300);

	form = new QWidget(this);
	form->setGeometry(10, 30, 300, 270);
	formLayout = new QFormLayout();

	faceValue = new QLineEdit(tr(coin->getFaceValue().c_str()));
	name = new QLineEdit(tr(coin->getName().c_str()));
	year = new QLineEdit();

	if (coin->getYear() != 0) {
		year->setText(tr(to_string(coin->getYear()).c_str()));
	}

	weight = new QLineEdit();

	if (coin->getWeight() != 0) {
		weight->setText(tr(to_string(coin->getWeight()).c_str()));
	}

	edge = new QLineEdit(tr(coin->getEdge().c_str()));
	comment = new QLineEdit(tr(coin->getComment().c_str()));
	button = new QPushButton(tr("Akceptuj"));

	formLayout->addRow(tr("Nominał: "), faceValue);
	formLayout->addRow(tr("Nazwa: "), name);
	formLayout->addRow(tr("Rok: "), year);
	formLayout->addRow(tr("Masa: "), weight);

	dimensions = new QWidget();
	dimensionsLayout = new QHBoxLayout();
	dimensions->setLayout(dimensionsLayout);

	if (coin->isRound()) {
		RoundCoin* roundcoin;
		roundcoin = dynamic_cast<RoundCoin *>(coin);
		diameter = new QLineEdit();

		if (roundcoin->getDiameter() != 0) {
			diameter->setText(tr(to_string(roundcoin->getDiameter()).c_str()));
		}

		dimensionsLayout->addWidget(diameter);
		dimensionsLayout->addWidget(new QLabel("mm"));

		formLayout->addRow(tr("Średnica: "), dimensions);
	}
	else {
		SquareCoin* squarecoin;
		squarecoin = dynamic_cast<SquareCoin *>(coin);

		width = new QLineEdit();
		height = new QLineEdit();

		float w = squarecoin->getDimensions().getWidth();
		float h = squarecoin->getDimensions().getHeight();

		if (w > 0 && h > 0) {
			width->setText(tr(to_string(w).c_str()));
			height->setText(tr(to_string(h).c_str()));
		}

		dimensionsLayout->addWidget(width);
		dimensionsLayout->addWidget(new QLabel("x"));
		dimensionsLayout->addWidget(height);
		dimensionsLayout->addWidget(new QLabel("mm"));

		
		formLayout->addRow(tr("Wymiary: "), dimensions);
	}

	formLayout->addRow(tr("Rant: "), edge);
	formLayout->addRow(tr("Komentarz: "), comment);
	formLayout->addWidget(button);

	form->setLayout(formLayout);

	connect(button, SIGNAL(clicked()), this, SLOT(save()));
}

bool CoinWindow::save() {
	Coin* mycoin;
	QMessageBox* msgBox = new QMessageBox();
	QString message;
	int _id;

	if (coin->getId() > 0) {
		_id = coin->getId();
		message = "Poprawnie edytowano monetę.";
	}
	else {
		_id = coinsmanager->getNextIndex();
		message = "Poprawnie dodano monetę do spisu.";
	}

	std::string _facevalue = trim(faceValue->text().toStdString());
	std::string _name = trim(name->text().toStdString());
	std::string s_year = trim(year->text().toStdString());
	std::string s_weight = trim(weight->text().toStdString());
	std::string _edge = trim(edge->text().toStdString());
	std::string _comment = trim(comment->text().toStdString());

	std::string main_regular_expression = "(.)*[\|]+(.)*";

	if (std::regex_match(_facevalue, std::regex(main_regular_expression))
		|| std::regex_match(_name, std::regex(main_regular_expression))
		|| std::regex_match(_edge, std::regex(main_regular_expression))
		|| std::regex_match(_comment, std::regex(main_regular_expression))) {
		message = "Proszę usunąc znaki: |.";
		msgBox->setText(message);
		msgBox->exec();

		return false;
	}

	if (!isInt(s_year)) {
		message = "Rok emisji musi być liczbą całkowitą.";
		msgBox->setText(message);
		msgBox->exec();

		return false;
	}

	if (!isFloat(s_weight)) {
		message = "Masa musi być liczbą.";
		msgBox->setText(message);
		msgBox->exec();

		return false;
	}

	int _year = (s_year.empty()) ? 0 : str2int(s_year);
	float _weight = str2float(s_weight);

	if (coin->isRound()) {
		std::string s_diameter = trim(diameter->text().toStdString());

		if (!isFloat(s_diameter)) {
			message = "Średnica musi być liczbą.";
			msgBox->setText(message);
			msgBox->exec();

			return false;
		}

		float _diameter = str2float(s_diameter);

		mycoin = new RoundCoin(_id, _facevalue, _name, _year, _weight, _diameter, _edge, _comment);
	}
	else {
		std::string s_width = trim(width->text().toStdString());
		std::string s_height = trim(height->text().toStdString());

		if (!isFloat(s_width) || !isFloat(s_height)) {
			message = "Rozmiar monety musi być liczbą.";
			msgBox->setText(message);
			msgBox->exec();

			return false;
		}

		float _width = str2float(s_width);
		float _height = str2float(s_height);

		Dimensions _dimensions = Dimensions(_width, _height);

		mycoin = new SquareCoin(_id, _facevalue, _name, _year, _weight, _dimensions, _edge, _comment);
	}

	coin = mycoin;
	coinsmanager->addCoin(coin);
	
	if (coinsmanager->save()) {
		emit changed();

		close();
		msgBox->setText(message);
		msgBox->exec();

		return true;
	}
	else {
		close();
		msgBox->setText("Wystąpiły problemu podczas dodawania monety do katalogu. Spróbuj ponownie później.");
		msgBox->exec();
		return false;
	}
}

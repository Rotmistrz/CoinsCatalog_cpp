#include "removecoinwindow.h"


RemoveCoinWindow::RemoveCoinWindow(std::string title) : title(title)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

	setWindowTitle(tr("Czy na pewno chcesz usunac?"));
	setAttribute(Qt::WA_DeleteOnClose);
	setMinimumSize(400, 100);
	setMaximumSize(400, 100);
	setWindowFlags(Qt::WindowStaysOnTopHint);

	mainWidget = new QWidget(this);
	mainLayout = new QVBoxLayout();

	question = new QLabel(tr(title.c_str()));
	mainLayout->addWidget(question);
	mainLayout->addSpacerItem(new QSpacerItem(10, 20));
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);

	yes = new QPushButton(tr("Tak"));
	no = new QPushButton(tr("Nie"));

	buttons = new QHBoxLayout();
	buttons->setSizeConstraint(QLayout::SetFixedSize);
	buttons->addSpacerItem(new QSpacerItem(150, 20));
	buttons->addWidget(yes);
	buttons->addWidget(no);
	mainLayout->addLayout(buttons);

	mainWidget->setLayout(mainLayout);

	connect(yes, SIGNAL(clicked()), this, SLOT(accepted()));
	connect(no, SIGNAL(clicked()), this, SLOT(close()));
}

void RemoveCoinWindow::accepted() {
	emit remove();
	close();
}

RemoveCoinWindow::~RemoveCoinWindow()
{
}

/********************************************************************************
** Form generated from reading UI file 'coinscatalog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COINSCATALOG_H
#define UI_COINSCATALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CoinsCatalogClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CoinsCatalogClass)
    {
        if (CoinsCatalogClass->objectName().isEmpty())
            CoinsCatalogClass->setObjectName(QStringLiteral("CoinsCatalogClass"));
        CoinsCatalogClass->resize(600, 400);
        menuBar = new QMenuBar(CoinsCatalogClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CoinsCatalogClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CoinsCatalogClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CoinsCatalogClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CoinsCatalogClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CoinsCatalogClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CoinsCatalogClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CoinsCatalogClass->setStatusBar(statusBar);

        retranslateUi(CoinsCatalogClass);

        QMetaObject::connectSlotsByName(CoinsCatalogClass);
    } // setupUi

    void retranslateUi(QMainWindow *CoinsCatalogClass)
    {
        CoinsCatalogClass->setWindowTitle(QApplication::translate("CoinsCatalogClass", "CoinsCatalog", 0));
    } // retranslateUi

};

namespace Ui {
    class CoinsCatalogClass: public Ui_CoinsCatalogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COINSCATALOG_H

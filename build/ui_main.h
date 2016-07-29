#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'main.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionFields;
    QAction *actionAbout;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *refreshButton;
    QSpacerItem *horizontalSpacer;
    QTabWidget *tabWidget;
    QWidget *disks;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *itemSource;
    QTableView *diskList;
    QWidget *raid;
    QHBoxLayout *horizontalLayout_3;
    QTableView *raidList;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_4;
    QTableView *mtabList;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuSss;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(846, 648);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionFields = new QAction(MainWindow);
        actionFields->setObjectName(QStringLiteral("actionFields"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAbout->setMenuRole(QAction::AboutRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        refreshButton = new QPushButton(centralwidget);
        refreshButton->setObjectName(QStringLiteral("refreshButton"));

        horizontalLayout->addWidget(refreshButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        disks = new QWidget();
        disks->setObjectName(QStringLiteral("disks"));
        sizePolicy2.setHeightForWidth(disks->sizePolicy().hasHeightForWidth());
        disks->setSizePolicy(sizePolicy2);
        horizontalLayout_2 = new QHBoxLayout(disks);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        itemSource = new QComboBox(disks);
        itemSource->setObjectName(QStringLiteral("itemSource"));

        verticalLayout_2->addWidget(itemSource);

        diskList = new QTableView(disks);
        diskList->setObjectName(QStringLiteral("diskList"));

        verticalLayout_2->addWidget(diskList);


        horizontalLayout_2->addLayout(verticalLayout_2);

        tabWidget->addTab(disks, QString());
        raid = new QWidget();
        raid->setObjectName(QStringLiteral("raid"));
        sizePolicy2.setHeightForWidth(raid->sizePolicy().hasHeightForWidth());
        raid->setSizePolicy(sizePolicy2);
        raid->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_3 = new QHBoxLayout(raid);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        raidList = new QTableView(raid);
        raidList->setObjectName(QStringLiteral("raidList"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(raidList->sizePolicy().hasHeightForWidth());
        raidList->setSizePolicy(sizePolicy3);
        raidList->setMaximumSize(QSize(16777215, 16777215));
        raidList->horizontalHeader()->setStretchLastSection(false);
        raidList->verticalHeader()->setStretchLastSection(false);

        horizontalLayout_3->addWidget(raidList);

        tabWidget->addTab(raid, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout_4 = new QHBoxLayout(tab);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        mtabList = new QTableView(tab);
        mtabList->setObjectName(QStringLiteral("mtabList"));

        horizontalLayout_4->addWidget(mtabList);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 846, 29));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSss = new QMenu(menubar);
        menuSss->setObjectName(QStringLiteral("menuSss"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSss->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionQuit);
        menuSss->addAction(actionFields);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(tr2i18n("MainWindow", 0));
        actionQuit->setText(tr2i18n("&Quit", 0));
        actionFields->setText(tr2i18n("&Fields", 0));
        actionAbout->setText(tr2i18n("&About", 0));
        refreshButton->setText(tr2i18n("Refresh", 0));
        tabWidget->setTabText(tabWidget->indexOf(disks), tr2i18n("Disks", 0));
        tabWidget->setTabText(tabWidget->indexOf(raid), tr2i18n("Raid", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), tr2i18n("MTab", 0));
        menuFile->setTitle(tr2i18n("Fi&le", 0));
        menuSss->setTitle(tr2i18n("Setti&ngs", 0));
        menuHelp->setTitle(tr2i18n("Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAIN_H


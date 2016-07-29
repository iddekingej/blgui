#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'parinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARINFO_H
#define UI_PARINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_parinfo
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *sizeLabel;
    QLabel *typeLabel;
    QLabel *labelLabel;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *nameDevice;
    QLabel *label_3;
    QLabel *parName;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_10;
    QLabel *noAliasesLabel;
    QTableView *deviceAliases;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_9;
    QLabel *noMountPointsLabel;
    QTableView *mountPoints;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnClose;

    void setupUi(QDialog *parinfo)
    {
        if (parinfo->objectName().isEmpty())
            parinfo->setObjectName(QStringLiteral("parinfo"));
        parinfo->resize(630, 656);
        verticalLayout = new QVBoxLayout(parinfo);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label = new QLabel(parinfo);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 0));
        label->setMaximumSize(QSize(281, 16777215));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(parinfo);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        sizeLabel = new QLabel(parinfo);
        sizeLabel->setObjectName(QStringLiteral("sizeLabel"));

        gridLayout->addWidget(sizeLabel, 4, 1, 1, 1);

        typeLabel = new QLabel(parinfo);
        typeLabel->setObjectName(QStringLiteral("typeLabel"));

        gridLayout->addWidget(typeLabel, 3, 1, 1, 1);

        labelLabel = new QLabel(parinfo);
        labelLabel->setObjectName(QStringLiteral("labelLabel"));

        gridLayout->addWidget(labelLabel, 2, 1, 1, 1);

        label_8 = new QLabel(parinfo);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);

        gridLayout->addWidget(label_8, 3, 0, 1, 1);

        label_7 = new QLabel(parinfo);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(0, 0));
        label_7->setMaximumSize(QSize(281, 16777215));
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        nameDevice = new QLabel(parinfo);
        nameDevice->setObjectName(QStringLiteral("nameDevice"));

        gridLayout->addWidget(nameDevice, 0, 1, 1, 1);

        label_3 = new QLabel(parinfo);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        parName = new QLabel(parinfo);
        parName->setObjectName(QStringLiteral("parName"));

        gridLayout->addWidget(parName, 1, 1, 1, 1);

        gridLayout->setColumnStretch(1, 1);

        horizontalLayout->addLayout(gridLayout);


        verticalLayout->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(parinfo);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_10 = new QLabel(tab);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font);

        verticalLayout_3->addWidget(label_10);

        noAliasesLabel = new QLabel(tab);
        noAliasesLabel->setObjectName(QStringLiteral("noAliasesLabel"));

        verticalLayout_3->addWidget(noAliasesLabel);

        deviceAliases = new QTableView(tab);
        deviceAliases->setObjectName(QStringLiteral("deviceAliases"));

        verticalLayout_3->addWidget(deviceAliases);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font);

        verticalLayout_4->addWidget(label_9, 0, Qt::AlignTop);

        noMountPointsLabel = new QLabel(tab_2);
        noMountPointsLabel->setObjectName(QStringLiteral("noMountPointsLabel"));

        verticalLayout_4->addWidget(noMountPointsLabel, 0, Qt::AlignTop);

        mountPoints = new QTableView(tab_2);
        mountPoints->setObjectName(QStringLiteral("mountPoints"));

        verticalLayout_4->addWidget(mountPoints);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 0, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnClose = new QPushButton(parinfo);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setMaximumSize(QSize(128, 16777215));

        horizontalLayout_2->addWidget(btnClose);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(verticalLayout_2);


        retranslateUi(parinfo);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(parinfo);
    } // setupUi

    void retranslateUi(QDialog *parinfo)
    {
        parinfo->setWindowTitle(tr2i18n("Partition information", 0));
        label->setText(tr2i18n("Device name:", 0));
        label_2->setText(tr2i18n("Size:", 0));
        sizeLabel->setText(tr2i18n("None", 0));
        typeLabel->setText(tr2i18n("none", 0));
        labelLabel->setText(tr2i18n("None", 0));
        label_8->setText(tr2i18n("Type:", 0));
        label_7->setText(tr2i18n("Label:", 0));
        nameDevice->setText(tr2i18n("none", 0));
        label_3->setText(tr2i18n("Paritition name:", 0));
        parName->setText(tr2i18n("None", 0));
        label_10->setText(tr2i18n("Device aliases", 0));
        noAliasesLabel->setText(tr2i18n("Device has no aliasses", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), tr2i18n("Aliasses", 0));
        label_9->setText(tr2i18n("Mount points", 0));
        noMountPointsLabel->setText(tr2i18n("This partition is not mounted", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), tr2i18n("Mountpoints", 0));
        btnClose->setText(tr2i18n("Close", 0));
    } // retranslateUi

};

namespace Ui {
    class parinfo: public Ui_parinfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PARINFO_H


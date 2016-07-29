#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'devinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVINFO_H
#define UI_DEVINFO_H

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

class Ui_devinfo
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *nameDevice;
    QLabel *label_2;
    QLabel *sizeLabel;
    QLabel *label_3;
    QLabel *modelLabel;
    QLabel *label_4;
    QLabel *removeableLabel;
    QLabel *label_5;
    QLabel *readonlyLabel;
    QLabel *labelLabel;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *typeLabel;
    QLabel *labLoopbackFile;
    QLabel *valLoopbackFile;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_10;
    QLabel *noAliasesLabel;
    QTableView *deviceAliases;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_6;
    QTableView *partInfo;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_9;
    QLabel *noMountPointsLabel;
    QTableView *mountPoints;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_11;
    QLabel *noSlaveLabel;
    QTableView *slaveList;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnClose;

    void setupUi(QDialog *devinfo)
    {
        if (devinfo->objectName().isEmpty())
            devinfo->setObjectName(QStringLiteral("devinfo"));
        devinfo->resize(630, 656);
        verticalLayout = new QVBoxLayout(devinfo);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label = new QLabel(devinfo);
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

        nameDevice = new QLabel(devinfo);
        nameDevice->setObjectName(QStringLiteral("nameDevice"));

        gridLayout->addWidget(nameDevice, 0, 1, 1, 1);

        label_2 = new QLabel(devinfo);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        sizeLabel = new QLabel(devinfo);
        sizeLabel->setObjectName(QStringLiteral("sizeLabel"));

        gridLayout->addWidget(sizeLabel, 4, 1, 1, 1);

        label_3 = new QLabel(devinfo);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(0, 0));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        modelLabel = new QLabel(devinfo);
        modelLabel->setObjectName(QStringLiteral("modelLabel"));

        gridLayout->addWidget(modelLabel, 5, 1, 1, 1);

        label_4 = new QLabel(devinfo);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(0, 0));
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 6, 0, 1, 1);

        removeableLabel = new QLabel(devinfo);
        removeableLabel->setObjectName(QStringLiteral("removeableLabel"));

        gridLayout->addWidget(removeableLabel, 6, 1, 1, 1);

        label_5 = new QLabel(devinfo);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMaximumSize(QSize(281, 16777215));
        label_5->setFont(font);

        gridLayout->addWidget(label_5, 7, 0, 1, 1);

        readonlyLabel = new QLabel(devinfo);
        readonlyLabel->setObjectName(QStringLiteral("readonlyLabel"));

        gridLayout->addWidget(readonlyLabel, 7, 1, 1, 1);

        labelLabel = new QLabel(devinfo);
        labelLabel->setObjectName(QStringLiteral("labelLabel"));

        gridLayout->addWidget(labelLabel, 2, 1, 1, 1);

        label_7 = new QLabel(devinfo);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(0, 0));
        label_7->setMaximumSize(QSize(281, 16777215));
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        label_8 = new QLabel(devinfo);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);

        gridLayout->addWidget(label_8, 3, 0, 1, 1);

        typeLabel = new QLabel(devinfo);
        typeLabel->setObjectName(QStringLiteral("typeLabel"));

        gridLayout->addWidget(typeLabel, 3, 1, 1, 1);

        labLoopbackFile = new QLabel(devinfo);
        labLoopbackFile->setObjectName(QStringLiteral("labLoopbackFile"));
        sizePolicy.setHeightForWidth(labLoopbackFile->sizePolicy().hasHeightForWidth());
        labLoopbackFile->setSizePolicy(sizePolicy);
        labLoopbackFile->setFont(font);

        gridLayout->addWidget(labLoopbackFile, 1, 0, 1, 1);

        valLoopbackFile = new QLabel(devinfo);
        valLoopbackFile->setObjectName(QStringLiteral("valLoopbackFile"));

        gridLayout->addWidget(valLoopbackFile, 1, 1, 1, 1);

        gridLayout->setColumnStretch(1, 1);

        horizontalLayout->addLayout(gridLayout);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 0, -1, -1);
        tabWidget = new QTabWidget(devinfo);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_5 = new QVBoxLayout(tab);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_10 = new QLabel(tab);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font);

        verticalLayout_5->addWidget(label_10, 0, Qt::AlignTop);

        noAliasesLabel = new QLabel(tab);
        noAliasesLabel->setObjectName(QStringLiteral("noAliasesLabel"));

        verticalLayout_5->addWidget(noAliasesLabel, 0, Qt::AlignTop);

        deviceAliases = new QTableView(tab);
        deviceAliases->setObjectName(QStringLiteral("deviceAliases"));

        verticalLayout_5->addWidget(deviceAliases);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        verticalLayout_4->addWidget(label_6);

        partInfo = new QTableView(tab_2);
        partInfo->setObjectName(QStringLiteral("partInfo"));

        verticalLayout_4->addWidget(partInfo);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_6 = new QVBoxLayout(tab_3);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(-1, 5, -1, -1);
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(0, 17));
        label_9->setFont(font);

        verticalLayout_7->addWidget(label_9, 0, Qt::AlignTop);

        noMountPointsLabel = new QLabel(tab_3);
        noMountPointsLabel->setObjectName(QStringLiteral("noMountPointsLabel"));

        verticalLayout_7->addWidget(noMountPointsLabel, 0, Qt::AlignTop);


        verticalLayout_6->addLayout(verticalLayout_7);

        mountPoints = new QTableView(tab_3);
        mountPoints->setObjectName(QStringLiteral("mountPoints"));

        verticalLayout_6->addWidget(mountPoints);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        verticalLayout_3 = new QVBoxLayout(tab_4);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_11 = new QLabel(tab_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setEnabled(true);
        label_11->setFont(font);

        verticalLayout_3->addWidget(label_11, 0, Qt::AlignTop);

        noSlaveLabel = new QLabel(tab_4);
        noSlaveLabel->setObjectName(QStringLiteral("noSlaveLabel"));

        verticalLayout_3->addWidget(noSlaveLabel, 0, Qt::AlignTop);

        slaveList = new QTableView(tab_4);
        slaveList->setObjectName(QStringLiteral("slaveList"));

        verticalLayout_3->addWidget(slaveList);

        tabWidget->addTab(tab_4, QString());

        verticalLayout_2->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 20, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnClose = new QPushButton(devinfo);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout_2->addWidget(btnClose);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(verticalLayout_2);


        retranslateUi(devinfo);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(devinfo);
    } // setupUi

    void retranslateUi(QDialog *devinfo)
    {
        devinfo->setWindowTitle(tr2i18n("Device information", 0));
        label->setText(tr2i18n("Device name:", 0));
        nameDevice->setText(tr2i18n("none", 0));
        label_2->setText(tr2i18n("Size:", 0));
        sizeLabel->setText(tr2i18n("None", 0));
        label_3->setText(tr2i18n("Model:", 0));
        modelLabel->setText(tr2i18n("None", 0));
        label_4->setText(tr2i18n("Removable:", 0));
        removeableLabel->setText(tr2i18n("none", 0));
        label_5->setText(tr2i18n("Readonly:", 0));
        readonlyLabel->setText(tr2i18n("TextLabel", 0));
        labelLabel->setText(tr2i18n("None", 0));
        label_7->setText(tr2i18n("Label", 0));
        label_8->setText(tr2i18n("Type", 0));
        typeLabel->setText(tr2i18n("none", 0));
        labLoopbackFile->setText(tr2i18n("Loopback file", 0));
        valLoopbackFile->setText(tr2i18n("None", 0));
        label_10->setText(tr2i18n("Device aliases", 0));
        noAliasesLabel->setText(tr2i18n("Device has no aliasses", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), tr2i18n("Aliases", 0));
        label_6->setText(tr2i18n("Paritions", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), tr2i18n("Partitions", 0));
        label_9->setText(tr2i18n("Mount points", 0));
        noMountPointsLabel->setText(tr2i18n("This devices or it's partitions are not mounted", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), tr2i18n("Mountpoints", 0));
        label_11->setText(tr2i18n("Slaves", 0));
        noSlaveLabel->setText(tr2i18n("No slave found", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), tr2i18n("Slaves", 0));
        btnClose->setText(tr2i18n("Close", 0));
    } // retranslateUi

};

namespace Ui {
    class devinfo: public Ui_devinfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DEVINFO_H


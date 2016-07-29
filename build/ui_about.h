#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_about
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *closeButton;

    void setupUi(QDialog *about)
    {
        if (about->objectName().isEmpty())
            about->setObjectName(QStringLiteral("about"));
        about->resize(405, 120);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(about->sizePolicy().hasHeightForWidth());
        about->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(about);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(about);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter|Qt::AlignTop);

        label_2 = new QLabel(about);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2, 0, Qt::AlignTop);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_3 = new QLabel(about);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        closeButton = new QPushButton(about);
        closeButton->setObjectName(QStringLiteral("closeButton"));

        horizontalLayout->addWidget(closeButton, 0, Qt::AlignBottom);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(about);

        QMetaObject::connectSlotsByName(about);
    } // setupUi

    void retranslateUi(QDialog *about)
    {
        about->setWindowTitle(tr2i18n("About", 0));
        label->setText(tr2i18n("Disk information GUI", 0));
        label_2->setText(tr2i18n("(C) 2016 Jeroen van Iddekinge", 0));
        label_3->setText(tr2i18n("License: Gpl v2", 0));
        closeButton->setText(tr2i18n("Close", 0));
    } // retranslateUi

};

namespace Ui {
    class about: public Ui_about {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ABOUT_H


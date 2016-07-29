#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'fields.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIELDS_H
#define UI_FIELDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FieldsConfig
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QListView *fieldsAvailable;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *moveUp;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *removeField;
    QPushButton *addLabel;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *moveDown;
    QListView *fieldsSelected;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FieldsConfig)
    {
        if (FieldsConfig->objectName().isEmpty())
            FieldsConfig->setObjectName(QStringLiteral("FieldsConfig"));
        FieldsConfig->resize(512, 353);
        verticalLayoutWidget = new QWidget(FieldsConfig);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 501, 351));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        fieldsAvailable = new QListView(verticalLayoutWidget);
        fieldsAvailable->setObjectName(QStringLiteral("fieldsAvailable"));

        horizontalLayout->addWidget(fieldsAvailable);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, 10, -1, -1);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        moveUp = new QPushButton(verticalLayoutWidget);
        moveUp->setObjectName(QStringLiteral("moveUp"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(moveUp->sizePolicy().hasHeightForWidth());
        moveUp->setSizePolicy(sizePolicy);
        moveUp->setMinimumSize(QSize(33, 33));
        moveUp->setMaximumSize(QSize(33, 33));
        moveUp->setBaseSize(QSize(33, 0));

        horizontalLayout_6->addWidget(moveUp, 0, Qt::AlignRight);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        removeField = new QPushButton(verticalLayoutWidget);
        removeField->setObjectName(QStringLiteral("removeField"));
        removeField->setEnabled(false);
        removeField->setMinimumSize(QSize(33, 33));
        removeField->setMaximumSize(QSize(84, 33));

        horizontalLayout_2->addWidget(removeField);

        addLabel = new QPushButton(verticalLayoutWidget);
        addLabel->setObjectName(QStringLiteral("addLabel"));
        addLabel->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(addLabel->sizePolicy().hasHeightForWidth());
        addLabel->setSizePolicy(sizePolicy1);
        addLabel->setMinimumSize(QSize(33, 33));
        addLabel->setMaximumSize(QSize(84, 33));

        horizontalLayout_2->addWidget(addLabel);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        moveDown = new QPushButton(verticalLayoutWidget);
        moveDown->setObjectName(QStringLiteral("moveDown"));
        sizePolicy.setHeightForWidth(moveDown->sizePolicy().hasHeightForWidth());
        moveDown->setSizePolicy(sizePolicy);
        moveDown->setMinimumSize(QSize(45, 33));
        moveDown->setMaximumSize(QSize(45, 33));
        moveDown->setBaseSize(QSize(33, 0));

        horizontalLayout_7->addWidget(moveDown, 0, Qt::AlignRight);


        verticalLayout_3->addLayout(horizontalLayout_7);


        horizontalLayout->addLayout(verticalLayout_3);

        fieldsSelected = new QListView(verticalLayoutWidget);
        fieldsSelected->setObjectName(QStringLiteral("fieldsSelected"));

        horizontalLayout->addWidget(fieldsSelected);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setMinimumSize(QSize(0, 0));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(FieldsConfig);

        QMetaObject::connectSlotsByName(FieldsConfig);
    } // setupUi

    void retranslateUi(QDialog *FieldsConfig)
    {
        FieldsConfig->setWindowTitle(tr2i18n("Fields configuration", 0));
        moveUp->setText(tr2i18n("Up", 0));
        removeField->setText(tr2i18n("<", 0));
        addLabel->setText(tr2i18n(">", 0));
        moveDown->setText(tr2i18n("Down", 0));
    } // retranslateUi

};

namespace Ui {
    class FieldsConfig: public Ui_FieldsConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FIELDS_H


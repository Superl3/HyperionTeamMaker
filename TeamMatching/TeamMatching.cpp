#include "TeamMatching.h"
#include "ConfigureMember.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QSizePolicy>

TeamMatching::TeamMatching(QWidget *parent) : QMainWindow(parent)
{
	auto pMainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	setLayout(pMainLayout);

	auto pConfigMemberBtn = new QPushButton(QString::fromLocal8Bit("¸â¹ö ÆíÁý"), this);
	//pConfigMemberBtn->setSizePolicy();
	QObject::connect(pConfigMemberBtn, &QPushButton::clicked, this, &TeamMatching::slotOpenConfigureDialog);
	pMainLayout->addWidget(pConfigMemberBtn);

// 	auto pCreateTeamBtn = new QPushButton("B", this);
// 	QObject::connect(pCreateTeamBtn, &QPushButton::clicked, this, &TeamMatching::slotOpenCreateTeamDialog);
// 	pMainLayout->addWidget(pCreateTeamBtn);

	setGeometry(0, 0, 600, 480);
	//ui.setupUi(this);
}

void TeamMatching::slotOpenConfigureDialog()
{
	auto dialog = new ConfigureMember();
	dialog->exec();

	//delete dialog;
}

void TeamMatching::slotOpenCreateTeamDialog()
{

}

#include "TeamMatching.h"
#include "ConfigureMember.h"
#include "CreateTeamDialog.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QSizePolicy>

TeamMatching::TeamMatching(QWidget *parent) : QMainWindow(parent)
{
	auto pMainWidget = new QWidget(this);
	setCentralWidget(pMainWidget);

	auto pMainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	pMainWidget->setLayout(pMainLayout);

	auto pConfigMemberBtn = new QPushButton(QString::fromLocal8Bit("¸â¹ö ÆíÁý"), this);
	pConfigMemberBtn->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	QObject::connect(pConfigMemberBtn, &QPushButton::clicked, this, &TeamMatching::slotOpenConfigureDialog);
	pMainLayout->addWidget(pConfigMemberBtn);

 	auto pCreateTeamBtn = new QPushButton(QString::fromLocal8Bit("ÆÀ ÀÛ¼º"), this);
	pCreateTeamBtn->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
 	QObject::connect(pCreateTeamBtn, &QPushButton::clicked, this, &TeamMatching::slotOpenCreateTeamDialog);
 	pMainLayout->addWidget(pCreateTeamBtn);

	setGeometry(0, 0, 600, 480);
}

void TeamMatching::slotOpenConfigureDialog()
{
	auto dialog = new ConfigureMember();
	dialog->exec();

	delete dialog;
}

void TeamMatching::slotOpenCreateTeamDialog()
{
	auto dialog = new CreateTeamDialog();
	dialog->exec();

	delete dialog;
}

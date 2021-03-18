#include "CreateTeam.h"

#include "defines.h"

#include <QFile>
#include <QTimer>
#include <QLineEdit>
#include <QComboBox>
#include <QBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
#include <QTextStream>

#include "Member.h"

CreateTeam::CreateTeam()
{
	auto pMainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	setLayout(pMainLayout);

	auto pSearchEdit = new QLineEdit();
	QObject::connect(pSearchEdit, &QLineEdit::textChanged, this, &CreateTeam::slotTextChanged);
	pMainLayout->addWidget(pSearchEdit);

	searchTimer = new QTimer();
	searchTimer->setSingleShot(true);
	searchTimer->setInterval(500);
	searchTimer->callOnTimeout([this] {filter(); });

	totalMemberList = new QListWidget();
	pMainLayout->addWidget(totalMemberList);

	auto pEditBtnLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	pMainLayout->addLayout(pEditBtnLayout);

	auto pBtnUp = new QPushButton(QString::fromLocal8Bit("↑"));
	QObject::connect(pBtnUp, &QPushButton::clicked, this, &CreateTeam::slotGoUp);
	pEditBtnLayout->addWidget(pBtnUp);

	auto pBtnDown = new QPushButton(QString::fromLocal8Bit("↓"));
	QObject::connect(pBtnDown, &QPushButton::clicked, this, &CreateTeam::slotGoDown);
	pEditBtnLayout->addWidget(pBtnDown);

	auto pBtnReset = new QPushButton(QString::fromLocal8Bit("초기화"));
	QObject::connect(pBtnReset, &QPushButton::clicked, this, &CreateTeam::slotReset);
	pEditBtnLayout->addWidget(pBtnReset);

	gameMemberList = new QListWidget();
	pMainLayout->addWidget(gameMemberList);

	auto pMainBtnLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	pMainLayout->addLayout(pMainBtnLayout);

	roundComboBox = new QComboBox();
	roundComboBox->addItems({ "1","2","3","4","5","inf" });
	pMainBtnLayout->addWidget(roundComboBox);

	auto pBtnCreateTeam = new QPushButton(QString::fromLocal8Bit("생성"));
	QObject::connect(pBtnCreateTeam, &QPushButton::clicked, this, &CreateTeam::slotCreateTeam);
	pMainBtnLayout->addWidget(pBtnCreateTeam);

	auto pBtnCancel = new QPushButton(QString::fromLocal8Bit("취소"));
	QObject::connect(pBtnCancel, &QPushButton::clicked, this, &CreateTeam::slotCancel);
	pMainBtnLayout->addWidget(pBtnCancel);

	load();
}

CreateTeam::~CreateTeam()
{

}

void CreateTeam::slotGoUp()
{

}

void CreateTeam::slotGoDown()
{

}

void CreateTeam::slotReset()
{

}

void CreateTeam::slotCreateTeam()
{
	accepted();
	close();
}

void CreateTeam::slotCancel()
{
	rejected();
	close();
}

void CreateTeam::slotTextChanged()
{
	searchTimer->stop();
	searchTimer->start();
}

void CreateTeam::load()
{
	do {
		QFile memberFile{ memberPath };
		if (!memberFile.exists()) break;

		if (!memberFile.open(QFile::ReadOnly)) break;
		QTextStream in(&memberFile);

		while (!in.atEnd()) {
			QString line = in.readLine();
			auto member = Member::fromString(line);
			if (!members.contains(member->getName()))
				members.insert(member->getName(), member);
		}

		memberFile.close();

	} while (false);
}

void CreateTeam::filter()
{

}

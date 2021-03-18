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
	initUI();
	load();
	filter();
}

CreateTeam::~CreateTeam()
{

}

void CreateTeam::slotGoUp()
{
	auto items = gameMemberList->selectedItems();
	gameMemberList->setSelectionMode(QAbstractItemView::NoSelection);
	gameMemberList->setSelectionMode(QAbstractItemView::MultiSelection);
	for (const auto &item : items) {
		auto member = dynamic_cast<Member*>(item);
		if (!member) continue;

		gameMemberList->takeItem(gameMemberList->row(member));
		if (totalMembers.contains(member->getName())) continue;

		totalMembers.insert(member->getName(), member);
		totalMemberList->addItem(member);
	}
	totalMemberList->sortItems();
}

void CreateTeam::slotGoDown()
{
	auto items = totalMemberList->selectedItems();

	totalMemberList->setSelectionMode(QAbstractItemView::NoSelection);
	totalMemberList->setSelectionMode(QAbstractItemView::MultiSelection);

	for (const auto &item : items) {
		auto member = dynamic_cast<Member*>(item);
		if (!member) continue;

		totalMemberList->takeItem(totalMemberList->row(member));
		gameMemberList->addItem(member);
		if (!totalMembers.contains(member->getName())) continue;

		totalMembers.remove(member->getName());
	}
	gameMemberList->sortItems();
}

void CreateTeam::slotReset()
{
 	int count = gameMemberList->count();
	for (int i = 0; i < count; i++) {
		auto member = dynamic_cast<Member*>(gameMemberList->item(i));
		if (!member) continue;

		gameMemberList->takeItem(i);
		if (totalMembers.contains(member->getName())) continue;

		totalMembers.insert(member->getName(), member);
		totalMemberList->addItem(member);
	}
	totalMemberList->sortItems();
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
			if (!totalMembers.contains(member->getName()))
				totalMembers.insert(member->getName(), member);
		}

		memberFile.close();

	} while (false);
}

void CreateTeam::filter()
{
	int count = totalMemberList->count();
	for (int i = 0; i < count; i++) {
		auto member = dynamic_cast<Member*>(totalMemberList->item(i));
		if (!member) continue;

		totalMemberList->takeItem(i);
		i -= 1; count -= 1;
	}

	auto keyword = searchEdit->text();

	for (const auto &memberName : totalMembers.keys()) {
		auto member = totalMembers.value(memberName);
		if (keyword.length() != 0 && !member->getName().contains(keyword)) continue;

		totalMemberList->addItem(member);
	}
	totalMemberList->sortItems();
}

void CreateTeam::initUI()
{
	auto pMainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	setLayout(pMainLayout);

	searchEdit = new QLineEdit();
	QObject::connect(searchEdit, &QLineEdit::textChanged, this, &CreateTeam::slotTextChanged);
	pMainLayout->addWidget(searchEdit);

	searchTimer = new QTimer();
	searchTimer->setSingleShot(true);
	searchTimer->setInterval(500);
	searchTimer->callOnTimeout([this] {filter(); });

	totalMemberList = new QListWidget();
	totalMemberList->setSelectionMode(QAbstractItemView::MultiSelection);
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
	gameMemberList->setSelectionMode(QAbstractItemView::MultiSelection);
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
}

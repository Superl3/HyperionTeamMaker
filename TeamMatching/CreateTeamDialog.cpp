#include "CreateTeamDialog.h"

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

CreateTeamDialog::CreateTeamDialog()
{
	initUI();
	load();
	filter();
}

CreateTeamDialog::~CreateTeamDialog()
{

}

void CreateTeamDialog::slotGoUp()
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

	filter();
	totalMemberList->sortItems();
}

void CreateTeamDialog::slotGoDown()
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

void CreateTeamDialog::slotReset()
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



void CreateTeamDialog::slotCreateTeam()
{
	gameMembers.clear();
	int count = gameMemberList->count();
	for (int i = 0; i < count; i++) {
		auto member = dynamic_cast<Member*>(gameMemberList->item(i));
		if (!member) continue;

		gameMembers.insert(member->getName(), member);
	}

	start();
	if (gameMembers.count() < 12) {
		QMessageBox(QMessageBox::Icon::Critical, QString::fromLocal8Bit("오류"), QString::fromLocal8Bit("인원을 12명 이상으로 설정 해 주세요.")).exec();
		return;
	}
	else {
		accepted();
		close();
	}
}

void CreateTeamDialog::slotCancel()
{
	rejected();
	close();
}

void CreateTeamDialog::slotTextChanged()
{
	searchTimer->stop();
	searchTimer->start();
}

void CreateTeamDialog::load()
{
	do {
		QFile memberFile{ MemberPath };
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

void CreateTeamDialog::filter()
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

void CreateTeamDialog::initUI()
{
	auto pMainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	setLayout(pMainLayout);

	searchEdit = new QLineEdit();
	QObject::connect(searchEdit, &QLineEdit::textChanged, this, &CreateTeamDialog::slotTextChanged);
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
	QObject::connect(pBtnUp, &QPushButton::clicked, this, &CreateTeamDialog::slotGoUp);
	pEditBtnLayout->addWidget(pBtnUp);

	auto pBtnDown = new QPushButton(QString::fromLocal8Bit("↓"));
	QObject::connect(pBtnDown, &QPushButton::clicked, this, &CreateTeamDialog::slotGoDown);
	pEditBtnLayout->addWidget(pBtnDown);

	auto pBtnReset = new QPushButton(QString::fromLocal8Bit("초기화"));
	QObject::connect(pBtnReset, &QPushButton::clicked, this, &CreateTeamDialog::slotReset);
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
	QObject::connect(pBtnCreateTeam, &QPushButton::clicked, this, &CreateTeamDialog::slotCreateTeam);
	pMainBtnLayout->addWidget(pBtnCreateTeam);

	auto pBtnCancel = new QPushButton(QString::fromLocal8Bit("취소"));
	QObject::connect(pBtnCancel, &QPushButton::clicked, this, &CreateTeamDialog::slotCancel);
	pMainBtnLayout->addWidget(pBtnCancel);
}



void CreateTeamDialog::start()
{
	auto playerList = gameMembers.values();

	QList<Member*> teamA = playerList;
	QList<Member*> teamB;

	createTwoTeam(teamA, teamB);
	return;
}

void CreateTeamDialog::createTwoTeam(QList<Member *> teamA, QList<Member *> teamB)
{
	if (checkTwoTeamsCreated(teamA,teamB)) {
		pickFromTeamA(teamA, teamB);
		return;
	}
	for (const auto &member : teamA) {
		teamA.removeAll(member);
		teamB.push_back(member);
		createTwoTeam(teamA, teamB);
		teamA.push_back(member);
		teamB.removeAll(member);
	}
}

void CreateTeamDialog::pickFromTeamA(QList<Member *> teamA, QList<Member *> teamB)
{
	if (teamA.size() == PlayerCountInTeam) {
		pickFromTeamB(teamA, teamB);
		return;
	}
	for (const auto &member : teamA) {
		teamA.removeAll(member);
		pickFromTeamA(teamA, teamB);
		teamA.push_back(member);
	}
}

void CreateTeamDialog::pickFromTeamB(QList<Member *> teamA, QList<Member *> teamB)
{
	if (teamB.size() == PlayerCountInTeam) {
		pickPositionFromBothTeam(teamA, teamB, Position::DEALER);
		return;
	}
	for (const auto &member : teamB) {
		teamB.removeAll(member);
		pickFromTeamB(teamA, teamB);
		teamB.push_back(member);
	}
}

bool CreateTeamDialog::checkTeamBalance()
{
	return std::abs(A.getRanks() - B.getRanks()) <= RankDiffTotal;
}

void CreateTeamDialog::pickPositionFromBothTeam(QList<Member *> teamA, QList<Member *> teamB, Position::Types type)
{
	if (doesTeamMakingDone(teamA, teamB, type)) {
		if (checkTeamBalance())
			assert(false);
		return;
	}

	int aSize = teamA.size(), bSize = teamB.size();
	for (int a1 = 0; a1 < aSize; a1++) {
		if (teamA[a1]->getRank(type) == 0) continue;
		for (int a2 = a1 + 1; a2 < aSize; a2++) {
			if (teamA[a2]->getRank(type) == 0) continue;
			for (int b1 = 0; b1 < bSize; b1++) {
				if (teamB[b1]->getRank(type) == 0) continue;
				for (int b2 = b1 + 1; b2 < bSize; b2++) {
					if (teamB[a2]->getRank(type) == 0) continue;

					auto teamAPartner = { teamA[a1], teamA[a2] };
					auto teamBPartner = { teamB[b1], teamB[b2] };
					if (!checkPositionBalance(teamAPartner, teamBPartner, type)) continue;

					for (const auto player : teamAPartner)
						teamA.removeAll(player);
					for (const auto player : teamBPartner)
						teamB.removeAll(player);

					A.setPosition(teamAPartner, type);
					B.setPosition(teamBPartner, type);
					
					pickPositionFromBothTeam(teamA, teamB, Position::getNextType(type));

					for (const auto player : teamAPartner)
						teamA.push_back(player);
					for (const auto player : teamBPartner)
						teamB.push_back(player);
				}
			}
		}
	}
}

bool CreateTeamDialog::checkPositionBalance(QList<Member *> teamAPlayers, QList<Member *> teamBPlayers, Position::Types type)
{
	int teamARankSum = 0;
	for (const auto &player : teamAPlayers)
		teamARankSum += std::pow(player->getRank(type), RankPow);

	int teamBRankSum = 0;
	for (const auto &player : teamBPlayers)
		teamBRankSum += std::pow(player->getRank(type), RankPow);

	return std::abs(teamARankSum - teamBRankSum) <= RankDiffPosition;
}

bool CreateTeamDialog::doesTeamMakingDone(QList<Member *> teamA, QList<Member *> teamB, Position::Types type) {
	return teamA.empty() && teamB.empty() && type == Position::Default;
}

bool CreateTeamDialog::checkTwoTeamsCreated(QList<Member *> teamA, QList<Member *> teamB)
{
	int aSize = teamA.size(), bSize = teamB.size();
	return std::abs(aSize - bSize) <= 1 && aSize >= 6 && bSize >= 6;
}
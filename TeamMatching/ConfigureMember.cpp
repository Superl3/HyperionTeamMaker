#include "ConfigureMember.h"


#include <QBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QTextStream>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFileInfo>
#include <QListWidget>
#include <QMessageBox>

#include "Member.h"

ConfigureMember::ConfigureMember()
{
	auto pMainLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	setLayout(pMainLayout);

	memberList = new QListWidget();
	pMainLayout->addWidget(memberList);
	
	auto pBtnLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	pMainLayout->addLayout(pBtnLayout);

	auto pBtnAddMember = new QPushButton(QString::fromLocal8Bit("추가"));
	QObject::connect(pBtnAddMember, &QPushButton::clicked, this, &ConfigureMember::addMember);
	pBtnLayout->addWidget(pBtnAddMember);

	auto pBtnModifyMember = new QPushButton(QString::fromLocal8Bit("수정"));
	QObject::connect(pBtnModifyMember, &QPushButton::clicked, this, &ConfigureMember::modMember);
	pBtnLayout->addWidget(pBtnModifyMember);

	auto pBtnDeleteMember = new QPushButton(QString::fromLocal8Bit("삭제"));
	QObject::connect(pBtnDeleteMember, &QPushButton::clicked, this, &ConfigureMember::dropMember);
	pBtnLayout->addWidget(pBtnDeleteMember);

	auto pBtnClose = new QPushButton(QString::fromLocal8Bit("닫기"));
	QObject::connect(pBtnClose, &QPushButton::clicked, this, &ConfigureMember::close);
	pBtnLayout->addWidget(pBtnClose);
	load();
}

bool ConfigureMember::slotDoesNameExist(QString name, Member *self)
{
	auto items = memberList->findItems(name, Qt::MatchExactly);
	items.removeAll(self);

	return !items.empty();
}

void ConfigureMember::addMember()
{
	openMemberDialog(nullptr);
}

void ConfigureMember::modMember()
{
	auto selectedMember = getSelectedMember();
	openMemberDialog(selectedMember);
}

void ConfigureMember::dropMember()
{
	auto member = getSelectedMember();
	memberList->removeItemWidget(member);

	delete member;
	member = nullptr;

	save();
}

Member* ConfigureMember::getSelectedMember()
{
	Member* selectedMember = nullptr;
	do {
		auto items = memberList->selectedItems();
		if (items.empty()) break;

		selectedMember = dynamic_cast<Member*>(items.first());
	} while (false);
	return selectedMember;
}

void ConfigureMember::load()
{
	do {
		QFile memberFile{ memberPath };
		if (!memberFile.exists()) break;

		if (!memberFile.open(QFile::ReadOnly)) break;
		QTextStream in(&memberFile);
		
		while (!in.atEnd()) {
			QString line = in.readLine();
			auto member = Member::fromString(line);
			if(memberList->findItems(member->getName(), Qt::MatchExactly).empty())
				memberList->addItem(member);
		}

		memberFile.close();
		
	} while (false);
}

void ConfigureMember::save()
{
	do {
		QFile memberFile{memberPath};
	 	memberFile.open(QIODevice::WriteOnly);

		QTextStream out(&memberFile);
		int count = memberList->count();
		for (int i = 0; i < count; i++) {
			auto item = dynamic_cast<Member*>(memberList->item(i));
			if (!item) continue;

			out << item->toString() << '\n';
		}
		memberFile.close();
	} while (false);
}

void ConfigureMember::openMemberDialog(Member *_member)
{
	auto dialog = new MemberDialog(_member);
	QObject::connect(dialog, &MemberDialog::signalDoesNameExist, this, &ConfigureMember::slotDoesNameExist);
	
	if (dialog->exec() == QDialog::Accepted) {

		auto member = dialog->getMember();
		member->setText();
		if (!_member) memberList->addItem(member);
			
	}

	delete dialog;

	save();
}

MemberDialog::MemberDialog(Member *_member) : member(_member)
{
	initUI();

	if (!member)
		member = new Member(QString::fromLocal8Bit("슈슈"), 2500, 2500, 2500);

	nameEdit->setText(member->getName());

	dealerEdit->setText(QString::number(member->getDamageRank()));
	tankerEdit->setText(QString::number(member->getTankRank()));
	supportEdit->setText(QString::number(member->getSupportRank()));
}

MemberDialog::~MemberDialog()
{
	if (nameEdit)
		delete nameEdit;


	if (supportEdit)
		delete supportEdit;

	if (dealerEdit)
		delete dealerEdit;

	if (tankerEdit)
		delete tankerEdit;
}

Member * MemberDialog::getMember()
{
	return member;
}

void MemberDialog::checkScore()
{
	if (dealerEdit->text().toInt() < 0 || dealerEdit->text().toInt() > 5000)
		dealerEdit->undo();

	if (tankerEdit->text().toInt() < 0 || tankerEdit->text().toInt() > 5000)
		tankerEdit->undo();

	if (supportEdit->text().toInt() < 0 || supportEdit->text().toInt() > 5000)
		supportEdit->undo();
}

void MemberDialog::save()
{
	QString name = nameEdit->text();
	int dealer = dealerEdit->text().toInt();
	int tanker = tankerEdit->text().toInt();
	int healer = supportEdit->text().toInt();

	if (name.length() < 2) {
		QMessageBox(QMessageBox::Icon::Critical, QString::fromLocal8Bit("오류"), QString::fromLocal8Bit("이름을 2글자 이상 입력하세요")).exec();
	}
	else if (emit this->signalDoesNameExist(name, member)) {
		QMessageBox(QMessageBox::Icon::Critical, QString::fromLocal8Bit("오류"), QString::fromLocal8Bit("같은 닉네임이 이미 존재합니다!")).exec();
	}
	else {
		member->changeData(name, dealer, tanker, healer);

		accept();
		this->close();
	}
}

void MemberDialog::cancel()
{
	reject();
	this->close();
}

void MemberDialog::initUI()
{
	auto pMainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	setLayout(pMainLayout);

	auto pNameLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	pMainLayout->addLayout(pNameLayout);

	auto pNameLabel = new QLabel(QString::fromLocal8Bit("이름"));
	pNameLayout->addWidget(pNameLabel);

	nameEdit = new QLineEdit();
	pNameLayout->addWidget(nameEdit);

	auto pScoreLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	pMainLayout->addLayout(pScoreLayout);

	auto pDealerGroupbox = new QGroupBox(QString::fromLocal8Bit("딜러"));
	pScoreLayout->addWidget(pDealerGroupbox);

	auto pDealerLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	pDealerGroupbox->setLayout(pDealerLayout);

	dealerEdit = new QLineEdit();
	QObject::connect(dealerEdit, &QLineEdit::textChanged, this, &MemberDialog::checkScore);
	pDealerLayout->addWidget(dealerEdit);

	auto pTankerGroupbox = new QGroupBox(QString::fromLocal8Bit("탱커"));
	pScoreLayout->addWidget(pTankerGroupbox);

	auto pTankerLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	pTankerGroupbox->setLayout(pTankerLayout);

	tankerEdit = new QLineEdit();
	pTankerLayout->addWidget(tankerEdit);

	auto pSupportGroupbox = new QGroupBox(QString::fromLocal8Bit("힐러"));
	pScoreLayout->addWidget(pSupportGroupbox);

	auto pSupportLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	pSupportGroupbox->setLayout(pSupportLayout);

	supportEdit = new QLineEdit();
	pSupportLayout->addWidget(supportEdit);

	auto pBtnLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	pMainLayout->addLayout(pBtnLayout);

	auto pOKBtn = new QPushButton(QString::fromLocal8Bit("저장"));
	QObject::connect(pOKBtn, &QPushButton::clicked, this, &MemberDialog::save);
	pBtnLayout->addWidget(pOKBtn);

	auto pCancelBtn = new QPushButton(QString::fromLocal8Bit("취소"));
	QObject::connect(pCancelBtn, &QPushButton::clicked, this, &MemberDialog::cancel);
	pBtnLayout->addWidget(pCancelBtn);
}

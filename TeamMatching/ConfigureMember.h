#pragma once

#include <QDialog>
#include <QString>

class QListView;
class QLineEdit;
class QListWidget;

class Member;

class MemberDialog : public QDialog {
	Q_OBJECT
public:
	MemberDialog(Member *_member = nullptr);
	~MemberDialog();

	Member *getMember();

signals:
	bool signalDoesNameExist(QString name, Member *self);

public slots:
	void checkScore();
	void save();
	void cancel();

private:
	void initUI();

	QLineEdit *nameEdit = nullptr;
	QLineEdit *dealerEdit = nullptr, *supportEdit = nullptr, *tankerEdit = nullptr;

	Member* member;
};

class ConfigureMember : public QDialog {
	Q_OBJECT
public:
	ConfigureMember();
	~ConfigureMember() {};

public slots:
	bool slotDoesNameExist(QString name, Member *self);

	void addMember();
	void modMember();
	void dropMember();

private:
	QListWidget *memberList = nullptr;
	QString memberPath = "memberList.txt";

private:
	Member* getSelectedMember();
	void load();
	void save();
	void openMemberDialog(Member *_member);
};
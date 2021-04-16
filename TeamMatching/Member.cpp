#include "Member.h"

Member::Member(QString _name, int tank, int dps, int support) : QListWidgetItem(""),
name(_name), Tank(Position(tank)), Damage(Position(dps)), Support(Position(support))
{
	setText();
};

void Member::changeData(QString _name, int tank, int dps, int support)
{
	name = _name;
	Tank.setRank(tank);
	Damage.setRank(dps);
	Support.setRank(support);
}

Member* Member::fromString(QString raw)
{
	auto splitedRaw = raw.split('\t');
	QString name = splitedRaw[0];
	int tanker = splitedRaw[1].toInt();
	int dealer = splitedRaw[2].toInt();
	int support = splitedRaw[3].toInt();

	return new Member(name, tanker, dealer, support);
}

QString Member::toString()
{
	return name + '\t' +		
		QString::number(Tank.getRank()) + '\t' +
		QString::number(Damage.getRank()) + '\t' +
		QString::number(Support.getRank());
}

void Member::setText()
{
	QString syntax = name + '\t' +
		QString::number(Tank.getRank()) + " / " +
		QString::number(Damage.getRank()) + " / " +
		QString::number(Support.getRank());

	QListWidgetItem::setText(syntax);
}

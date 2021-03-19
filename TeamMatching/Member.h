#pragma once

#include <QVector>
#include <QListWidgetItem>

class Position {
public:
	enum Heroes {
		GENJI = 0, DOOMFIST, REAPER, MCCREE, MEI, BASTION, SOLDIER76, SOMBRA, SYMMETRA, ASHE, ECHO, WIDOWMAKER, JUNKRAT, TORBJORN, TRACER, PHARAH, HANZO,
		DVA, REINHARDT, WRECKINGBALL, ROADHOG, SIGMA, ORISA, WINSTON, ZARYA,
		LUCIO, MERCY, MOIRA, BAPTISTE, BRIGITTE, ANA, ZENYATTA
	};

public:
	Position(int _current) : best(_current), current(_current) {};
	Position(int _current, QVector<Heroes> _playable) : Position(_current) {
		playable = _playable;
	}

	Position(int _best, int _current) : best(_best), current(_current) {};
	Position(int _best, int _current, QVector<Heroes> _playable) : Position(_best, _current) {
		playable = _playable;
	}

	int getRank() { return best; }
	void setRank(int _best) { best = _best; current = _best; }

	int best;
	int current;

	QVector<Heroes> playable;
};

class Member : public QListWidgetItem{
public:
	Member(QString _name, int dps, int tank, int support);

	void changeData(QString _name, int dps, int tank, int support);

	static Member* fromString(QString raw);
	QString toString();

	QString getName() { return name; }
	int getDamageRank() { return Damage.getRank(); }
	int getTankRank() { return Tank.getRank(); }
	int getSupportRank() { return Support.getRank(); }

	void setText();

	static struct rankCompare {
	public:
		explicit rankCompare(QString _pos) : pos(_pos) {}
		bool operator () (Member *a, Member *b) const {
			if (pos == "Damage")
				return a->getDamageRank() > b->getDamageRank();
			else if (pos == "Tank")
				return a->getTankRank() > b->getTankRank();
			else
				return a->getSupportRank() > b->getSupportRank();
		}
		QString pos;
	};

private:
	Position Damage, Tank, Support;
	QString name;
};
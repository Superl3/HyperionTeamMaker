#pragma once

#include <QMainWindow>

class TeamMatching : public QMainWindow
{
    Q_OBJECT

public:
    TeamMatching(QWidget *parent = Q_NULLPTR);

public slots:
	void slotOpenConfigureDialog();
	void slotOpenCreateTeamDialog();
};

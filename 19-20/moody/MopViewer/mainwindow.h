/**
* Author      : Dr Carey Pridgeon
* Copyright   : Dr Carey Pridgeon 2009
* Licence     : Licensed under the Apache License, Version 2.0 (the "License");
*             : you may not use this file except in compliance with the License.
*             : You may obtain a copy of the License at
*             : http://www.apache.org/licenses/LICENSE-2.0
*             :
*             : Unless required by applicable law or agreed to in writing,
*             : software distributed under the License is distributed on
*             : an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
*             : either express or implied. See the License for the specific
*             : language governing permissions and limitations under the License.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "glwidget.h"
#include "controls.h"
#include "textdisplay.h"
#include "../moody/capsule/capsuleBase/mopfile/MopFile.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	public slots:
	void about();
	void openMopFile();
	void closeMopFile();
	void showControlPanel();
	void showConsole();
private:
	Ui::MainWindow *ui;
	GLWidget *glWidget;
	Controls * cPanel;
	TextDisplay *detailPanel;
	QTimer *timer;
	void setupFileMenu();

	private slots:
	void on_AxisSliderZ_valueChanged(int value);
	void on_AxisSliderY_valueChanged(int value);
	void on_AxisSliderX_valueChanged(int value);
	void resetAxisView();
	void adjustTimer(int delay);

signals:
	void x_axis_valueChanged(int );
	void y_axis_valueChanged(int );
	void z_axis_valueChanged(int );
	void resetZoomLevel(int level);
	void glStateResetRequest();
	void cPanelStateResetRequest();

};

#endif // MAINWINDOW_H

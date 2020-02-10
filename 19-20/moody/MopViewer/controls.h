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
#ifndef CONTROLS_H
#define CONTROLS_H
#include <QWidget>
#include "../moody/capsule/capsuleBase/etc/Advisor.h"
namespace Ui {
	class Controls;
}

class Controls : public QWidget
{
	Q_OBJECT

public:
	explicit Controls(QWidget *parent = 0);
	~Controls();

	public slots:
	void setZoomLevel(int level);
	void setMaxFocus(int value);
	void setMaxSelParticleOne(int value);
	void setMaxSelParticleTwo(int value);
	void resetState();
private:
	Ui::Controls *ui;
	bool pausedState;

	private slots:
	void on_stateVectorCheckBox_toggled(bool checked);
	void on_playbackSpeedSpinBox_valueChanged(int value);
	void on_resetViewButton_pressed();
	void on_selectedParticleTwoActive_toggled(bool checked);
	void on_selectedParticleOneActive_toggled(bool checked);
	void on_optionThreeRadioButton_toggled(bool checked);
	void on_optionTwoRadioButton_toggled(bool checked);
	void on_optionOneRadioButton_toggled(bool checked);
	void on_TrailLengthSpinBox_valueChanged(int value);
	void on_selectedParticleTrailsOnlyCheckBox_toggled(bool checked);
	void on_showTrailsCheckBox_toggled(bool checked);
	void on_relativeVelocityCheckBox_toggled(bool checked);
	void on_asAUCheckBox_toggled(bool checked);
	void on_distanceCheckBox_toggled(bool checked);
	void on_showLineCheckBox_toggled(bool checked);
	void on_showGlyphsCheckBox_toggled(bool checked);
	void on_selectedParticleOneSpinBox_valueChanged(int value);
	void on_selectedParticleTwoSpinBox_valueChanged(int value);
	void on_recordImageButton_pressed();
	void on_showPlacemarksCheckBox_toggled(bool checked);
	void on_FocusParticleSpinBox_valueChanged(int value);
	void on_zoomLevelSpinBox_valueChanged(int value);
	void on_restartButton_pressed();
	void on_playButton_pressed();


signals:
	void particleDisplayType(int );
	void TrailLengthSpinBox_valueChanged(int );
	void selectedParticleTrailsOnlyCheckBox_toggled(bool checked);
	void showTrailsCheckBox_toggled(bool checked);
	void relativeVelocityCheckBox_toggled(bool checked);
	void stateVector_toggled(bool checked);
	void asAUCheckBox_toggled(bool checked);
	void distanceCheckBox_toggled(bool checked);
	void showLineCheckBox_toggled(bool checked);
	void showGlyphsCheckBox_toggled(bool checked);
	void selectedParticleOneSpinBox_valueChanged(int );
	void selectedParticleTwoSpinBox_valueChanged(int );
	void recordImageButton_pressed();
	void showPlacemarksCheckBox_toggled(bool checked);
	void focusParticleSpinBox_valueChanged(int );
	void zoomLevelSpinBox_valueChanged(int );
	void restartButton_pressed();
	void sendPausedState(bool state);
	void selectedParticleOneActiveState(bool checked);
	void selectedParticleTwoActiveState(bool checked);
	void resetView();
	void playbackSpeedChanged(int delay);
};

#endif // CONTROLS_H

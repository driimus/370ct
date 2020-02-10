#include "controls.h"
#include "ui_controls.h"

Controls::Controls(QWidget *parent) :
QWidget(parent),
ui(new Ui::Controls)
{
	ui->setupUi(this);
	this->pausedState = true;
}

Controls::~Controls()
{
	delete ui;
}

//-------
// slots
//-------
void Controls::on_playButton_pressed()
{
	if(this->pausedState) {
		this->pausedState = false;
		ui->playButton->setText("Pause");
	} else {
		this->pausedState=true;
		ui->playButton->setText("Play");
	}
	emit sendPausedState(this->pausedState);
}

void Controls::on_restartButton_pressed() {
	emit restartButton_pressed();
}

void Controls::on_zoomLevelSpinBox_valueChanged(int value)
{
	emit zoomLevelSpinBox_valueChanged(value);
}

void Controls::setZoomLevel(int level) {
	ui->zoomLevelSpinBox->setValue(level);
}

void Controls::setMaxFocus(int value) {
	ui->FocusParticleSpinBox->setValue(value);
}

void Controls::setMaxSelParticleOne(int value) {
	ui->selectedParticleOneSpinBox->setValue(value);
}

void Controls::setMaxSelParticleTwo(int value) {
	ui->selectedParticleTwoSpinBox->setValue(value);
}

void Controls::on_FocusParticleSpinBox_valueChanged(int value) {
	emit focusParticleSpinBox_valueChanged(value);
}

void Controls::on_showPlacemarksCheckBox_toggled(bool checked)
{
	emit showPlacemarksCheckBox_toggled(checked);
}

void Controls::on_recordImageButton_pressed()
{
	emit recordImageButton_pressed();
}

void Controls::on_selectedParticleOneSpinBox_valueChanged(int value)
{
	emit selectedParticleOneSpinBox_valueChanged(value);
}

void Controls::on_selectedParticleTwoSpinBox_valueChanged(int value)
{
	emit selectedParticleTwoSpinBox_valueChanged(value);
}

void Controls::on_showGlyphsCheckBox_toggled(bool checked)
{
	emit showGlyphsCheckBox_toggled(checked);
}

void Controls::on_showLineCheckBox_toggled(bool checked)
{
	emit showLineCheckBox_toggled(checked);
}

void Controls::on_distanceCheckBox_toggled(bool checked)
{
	emit distanceCheckBox_toggled(checked);
}

void Controls::on_asAUCheckBox_toggled(bool checked)
{
	emit asAUCheckBox_toggled(checked);
}



void Controls::on_relativeVelocityCheckBox_toggled(bool checked)
{
	emit relativeVelocityCheckBox_toggled(checked);
}

void Controls::on_showTrailsCheckBox_toggled(bool checked)
{
	emit showTrailsCheckBox_toggled(checked);
}

void Controls::on_selectedParticleTrailsOnlyCheckBox_toggled(bool checked)
{
	emit selectedParticleTrailsOnlyCheckBox_toggled(checked);
}

void Controls::on_TrailLengthSpinBox_valueChanged(int value)
{
	emit TrailLengthSpinBox_valueChanged(value);
}

void Controls::on_optionOneRadioButton_toggled(bool checked)
{
	emit particleDisplayType(Advisor::Spheres);
}

void Controls::on_optionTwoRadioButton_toggled(bool checked)
{
	emit particleDisplayType(Advisor::Markers);
}

void Controls::on_optionThreeRadioButton_toggled(bool checked)
{
	emit particleDisplayType(Advisor::Dots);
}


void Controls::on_selectedParticleOneActive_toggled(bool checked)
{
	emit selectedParticleOneActiveState(checked);
}

void Controls::on_selectedParticleTwoActive_toggled(bool checked)
{
	emit selectedParticleTwoActiveState(checked);
}

void Controls::on_resetViewButton_pressed()
{
	emit resetView();
}

void Controls::on_playbackSpeedSpinBox_valueChanged(int value)
{
	emit playbackSpeedChanged(value);
}

void Controls::on_stateVectorCheckBox_toggled(bool checked)
{
	emit stateVector_toggled(checked);
}

void Controls::resetState() {
	ui->asAUCheckBox->setChecked(false);
	ui->distanceCheckBox->setChecked(false);
	ui->FocusParticleSpinBox->setValue(0);
	ui->optionOneRadioButton->setChecked(true);
	ui->optionTwoRadioButton->setChecked(false);
	ui->optionThreeRadioButton->setChecked(false);
	ui->playbackSpeedSpinBox->setValue(50);
	ui->playButton->setText("play");
	this->pausedState = true;
	ui->relativeVelocityCheckBox->setChecked(false);
	ui->selectedParticleOneActive->setChecked(false);
	ui->selectedParticleTwoActive->setChecked(false);
	ui->selectedParticleTrailsOnlyCheckBox->setChecked(false);
	ui->selectedParticleOneSpinBox->setValue(0);
	ui->selectedParticleTwoSpinBox->setValue(0);
	ui->showGlyphsCheckBox->setChecked(false);
	ui->showLineCheckBox->setChecked(false);
	ui->showPlacemarksCheckBox->setChecked(true);
	ui->showTrailsCheckBox->setChecked(false);
	ui->stateVectorCheckBox->setChecked(false);
	ui->TrailLengthSpinBox->setValue(100);
	ui->zoomLevelSpinBox->setValue(0);
}

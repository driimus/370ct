
#include "controls.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "QDesktopWidget"
MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//QGLFormat f;
	//f.setDoubleBuffer(true);
	glWidget = new GLWidget();
	//glWidget->format().setDoubleBuffer(true);
	ui->glContainer->addWidget(glWidget);
	this->timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), glWidget, SLOT(updateGL()));
	timer->start(50);
	// centre on the screen
	QDesktopWidget *desktop = QApplication::desktop();
	int screenWidth, width;
	int screenHeight, height;
	int x, y;
	QSize windowSize;
	screenWidth = desktop->width();
	screenHeight = desktop->height();
	windowSize = size();
	width = windowSize.width();
	height = windowSize.height();
	x = (screenWidth - width) / 2;
	y = (screenHeight - height) / 2;
	y -= 50;
	move ( x, y );
	// add file menu
	this->setupFileMenu();
	// add and position the control panel
	this->cPanel = new Controls(0);
	this->cPanel->move(x+this->frameSize().rwidth(),y);
	// set up and display the detail text window
	this->detailPanel = new TextDisplay(0);
	this->detailPanel->move((x-20)-this->detailPanel->frameSize().rwidth(),y);


	// connecting up all those yummy slots and signals
	//twixt the main window and glwidget
	connect(ui->AxisSliderX, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int)));
	connect(glWidget, SIGNAL(xRotationChanged(int)), ui->AxisSliderX, SLOT(setValue(int)));
	connect(ui->AxisSliderY, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int)));
	connect(glWidget, SIGNAL(yRotationChanged(int)),ui->AxisSliderY, SLOT(setValue(int)));
	connect(ui->AxisSliderZ, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));
	connect(glWidget, SIGNAL(zRotationChanged(int)), ui->AxisSliderZ, SLOT(setValue(int)));
	connect(glWidget, SIGNAL(scalerChange(int)), cPanel, SLOT(setZoomLevel(int)));
	connect(this, SIGNAL(resetZoomLevel(int)), cPanel, SLOT(setZoomLevel(int)));
	connect(this, SIGNAL(glStateResetRequest()), glWidget, SLOT(resetState()));
	connect(this, SIGNAL(cPanelStateResetRequest()),cPanel, SLOT(resetState()));

	// twixt the control panel and glWidget
	connect(cPanel, SIGNAL(sendPausedState(bool)), glWidget, SLOT(setPausedState(bool)));
	connect(cPanel, SIGNAL(particleDisplayType(int)), glWidget, SLOT(setParticleDisplayStyle(int)));
	connect(cPanel, SIGNAL(TrailLengthSpinBox_valueChanged(int )), glWidget, SLOT(setTrailLength(int)));
	connect(cPanel, SIGNAL(showTrailsCheckBox_toggled(bool)), glWidget, SLOT(setShowTrails(bool)));
	connect(cPanel, SIGNAL(selectedParticleTrailsOnlyCheckBox_toggled(bool)), glWidget, SLOT(setShowTrailsForSelectedParticlesOnly(bool)));
	connect(cPanel, SIGNAL(relativeVelocityCheckBox_toggled(bool)), glWidget, SLOT(setShowRelativeVelocity(bool)));
	connect(cPanel, SIGNAL(stateVector_toggled(bool)), glWidget, SLOT(setShowStateVector(bool)));
	connect(cPanel, SIGNAL(asAUCheckBox_toggled(bool)), glWidget, SLOT(setShowAsAU(bool)));
	connect(cPanel, SIGNAL(distanceCheckBox_toggled(bool)), glWidget, SLOT(setShowDistance(bool)));
	connect(cPanel, SIGNAL(showLineCheckBox_toggled(bool)), glWidget, SLOT(setShowConnectingLine(bool)));
	connect(cPanel, SIGNAL(showGlyphsCheckBox_toggled(bool)), glWidget, SLOT(setShowSelectedParticleGlyphs(bool)));
	connect(cPanel, SIGNAL(selectedParticleOneSpinBox_valueChanged(int )), glWidget, SLOT(setSelectedParticleOne(int)));
	connect(cPanel, SIGNAL(selectedParticleTwoSpinBox_valueChanged(int )), glWidget, SLOT(setSelectedParticleTwo(int)));
	connect(cPanel, SIGNAL(recordImageButton_pressed()), glWidget, SLOT(allowRecordStateToImage()));
	connect(cPanel, SIGNAL(showPlacemarksCheckBox_toggled(bool)), glWidget, SLOT(setShowPlacemarkParticles(bool)));
	connect(cPanel, SIGNAL(focusParticleSpinBox_valueChanged(int )), glWidget, SLOT(setFocusParticle(int)));
	connect(cPanel, SIGNAL(zoomLevelSpinBox_valueChanged(int )), glWidget, SLOT(setScaler(int)));
	connect(cPanel, SIGNAL(restartButton_pressed()), glWidget, SLOT(requirePlayBackRestart()));
	connect(cPanel, SIGNAL(selectedParticleOneActiveState(bool)), glWidget, SLOT(setSelectedParticleOneActiveState(bool)));
	connect(cPanel, SIGNAL(selectedParticleTwoActiveState(bool)), glWidget, SLOT(setSelectedParticleTwoActiveState(bool)));
	connect(glWidget, SIGNAL(lastParticleIndex(int )), cPanel, SLOT(setMaxFocus(int)));
	connect(glWidget, SIGNAL(lastParticleIndex_selParticle_1(int )), cPanel, SLOT(setMaxSelParticleOne(int)));
	connect(glWidget, SIGNAL(lastParticleIndex_selParticle_2(int )), cPanel, SLOT(setMaxSelParticleTwo(int)));

	// twixt the control panel and the main window
	connect(cPanel, SIGNAL(resetView()), this, SLOT(resetAxisView()));
	connect(cPanel, SIGNAL(playbackSpeedChanged(int)), this, SLOT(adjustTimer(int)));

	// twixt the glWidget and the detailPanel
	connect(glWidget, SIGNAL(clearConsole()), detailPanel, SLOT(clearText()));
	connect(glWidget, SIGNAL(sendTextToConsole(QString)), detailPanel, SLOT(writeText(QString)));




}


MainWindow::~MainWindow()
{
	delete ui;
	exit(0);
}

void MainWindow::setupFileMenu()
{
	QMenu *fileMenu = new QMenu(tr("&File"), this);
	menuBar()->addMenu(fileMenu);
	fileMenu->addAction(tr("&Open Mop File"), this, SLOT(openMopFile()),
	QKeySequence::Open);
	fileMenu->addAction(tr("&Close Mop File"), this, SLOT(closeMopFile()),
	QKeySequence::Close);
	fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()),
	QKeySequence::Quit);
	QMenu *settingsMenu = new QMenu(tr("&settings"), this);
	menuBar()->addMenu(settingsMenu);
	QAction *ctrlToggle = new QAction(tr("&Show Control Panel"), this);
	ctrlToggle->setCheckable(true);
	ctrlToggle->setChecked(true);
	connect(ctrlToggle, SIGNAL(triggered()),this, SLOT(showControlPanel()));
	settingsMenu->addAction(ctrlToggle);
	QAction *consoleToggle = new QAction(tr("&Show Console"), this);
	consoleToggle->setCheckable(true);
	consoleToggle->setChecked(true);
	connect(consoleToggle, SIGNAL(triggered()),this, SLOT(showConsole()));
	settingsMenu->addAction(consoleToggle);
}

void MainWindow::about() {

}

void MainWindow::openMopFile() {
	if (!glWidget->mopWorker->mopActive) {
		// open the mop file
		QString filename = QFileDialog::getOpenFileName(this,tr("Open Mop File"), "", tr("Mop Files (*.mop)"));
		if(filename!=NULL) {
			glWidget->mopWorker->createMopFile(filename);
                        glWidget->mopWorker->mopActive = true;
			emit glStateResetRequest();
			emit cPanelStateResetRequest();
			// grab the initial state for display
                        glWidget->mopWorker->loadNextState();
			this->cPanel->show();
			this->detailPanel->show();
			// reset all control panal vars to default

		}
	} else {
		// close the existing MopFile instance first
		this->closeMopFile();
		// open the new mop file
		QString filename = QFileDialog::getOpenFileName(this,tr("Open Mop File"), "", tr("Mop Files (*.mop)"));
		if(filename!=NULL) {
			glWidget->mopWorker->createMopFile(filename);
			glWidget->mopWorker->mopActive = true;
			emit glStateResetRequest();
			emit cPanelStateResetRequest();
			this->cPanel->show();
			this->detailPanel->show();
			// grab the initial state for display
			glWidget->mopWorker->loadNextState();

		}
	}
}

void MainWindow::closeMopFile() {
	if (glWidget->mopWorker->mopActive == true) {
		glWidget->mopWorker->mopActive = false;
		glWidget->mopWorker->deleteMopFile();
		this->cPanel->hide();
		this->detailPanel->hide();
		emit glStateResetRequest();
		emit cPanelStateResetRequest();

	}
}

void MainWindow::showControlPanel() {
	if (this->cPanel->isHidden()) {
		this->cPanel->show();
	} else {
		this->cPanel->hide();
	}
}
void MainWindow::showConsole() {
	if (this->detailPanel->isHidden()) {
		this->detailPanel->show();
	} else {
		this->detailPanel->hide();
	}
}

void MainWindow::resetAxisView() {
	ui->AxisSliderX->setValue(0);
	ui->AxisSliderY->setValue(0);
	ui->AxisSliderZ->setValue(0);
}

void MainWindow::on_AxisSliderX_valueChanged(int value)
{
	emit x_axis_valueChanged(value);
}

void MainWindow::on_AxisSliderY_valueChanged(int value)
{
	emit y_axis_valueChanged(value);
}

void MainWindow::on_AxisSliderZ_valueChanged(int value)
{
	emit z_axis_valueChanged(value);
}

void MainWindow::adjustTimer(int delay) {
	this->timer->stop();
	this->timer->start(delay);
}

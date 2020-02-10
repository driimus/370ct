/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <QtOpenGL>
#include <math.h>

#include "glwidget.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(QWidget *parent)
: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	// init the control variables
	this->xRot = 0;
	this->yRot = 0;
	this->zRot = 0;
	this->particleDisplayStyle = Advisor::Spheres;
	this->selectedParticleOne = 0;
	this->selectedParticleTwo = 0;
	this->focusParticle = 0;
	this->selectedParticleRotation = 0;
        this->trailSize = 100;
	this->imageNameCounter = 0;
        this->tmpNumParticles = 0;
	this->paused = true;
	this->showTrails = false;
	this->showTrailsForSelectedParticlesOnly = false;
	this->showRelativeVelocity = false;
	this->showStateVector = false;
	this->showAsAU = false;
	this->showDistance = false;
	this->showConnectingLine = false;
	this->showSelectedParticleGlyphs = false;
	this->recordStateToImage = false;
	this->showPlacemarkParticles = true;
	this->restartPlayback = false;
	this->selectedParticleOneActive = false;
	this->selectedParticleTwoActive = false;
	this->allowConsoleUpdate = true;

	this->mopWorker = new MopHandling(240);
        this->trailDisplay = new TrailManager();
	emit scalerChange(0);
	this->factor = 1;
	this->pattern = 0x9999;
	this->Light_Ambient[0] = 0.5f;
	this->Light_Ambient[1] = 0.5f;
	this->Light_Ambient[2] = 0.5f;
	this->Light_Ambient[3] = 1.0f;
	this->Light_Diffuse[0] = 1.2f;
	this->Light_Diffuse[1] = 1.2f;
	this->Light_Diffuse[2] = 1.2f;
	this->Light_Diffuse[3] = 1.0f;
	this->Light_Position[0] = 0;
	this->Light_Position[1] = 0;
	this->Light_Position[2] = 0.0f;
	this->Light_Position[3] = 1.0f;
	this->gray[0] = 0.75f;
	this->gray[1] = 0.75f;
	this->gray[2] = 0.75f;
	this->gray[3] = 1.0f;
	this->specular[0] = 1.0f;
	this->specular[1] = 1.0f;
	this->specular[2] = 1.0f;
	this->specular[3] = 1.0f;
	this->specref[0] = 1.0f;
	this->specref[1] = 1.0f;
	this->specref[2] = 1.0f;
	this->specref[3] = 1.0f;

	this->no_mat[0] = 0.0f;
	this->no_mat[1] = 0.0f;
	this->no_mat[2] = 0.0f;
	this->no_mat[3] = 1.0f;

	this->mat_ambient[0] = 0.7f;
	this->mat_ambient[1] = 0.7f;
	this->mat_ambient[2] = 0.7f;
	this->mat_ambient[3] = 1.0f;

	this->mat_ambient_color[0] = 0.8f;
	this->mat_ambient_color[1] = 0.8f;
	this->mat_ambient_color[2] = 0.2f;
	this->mat_ambient_color[3] = 1.0f;

	this->mat_diffuse[0] = 0.1f;
	this->mat_diffuse[1] = 0.5f;
	this->mat_diffuse[2] = 0.8f;
	this->mat_diffuse[3] = 1.0f;

	this->mat_specular[0] = 1.0f;
	this->mat_specular[1] = 1.0f;
	this->mat_specular[2] = 1.0f;
	this->mat_specular[3] = 1.0f;

	this->mat_emission[0] = 0.3f;
	this->mat_emission[1] = 0.2f;
	this->mat_emission[2] = 0.2f;
	this->mat_emission[3] = 0.0f;

	this->no_shininess = 0.0f;
	this->low_shininess = 5.0f;
	this->high_shininess = 100.0f;
}

GLWidget::~GLWidget()
{
	delete this->mopWorker;
}

QSize GLWidget::minimumSizeHint() const
{
	return QSize(50, 50);
}

QSize GLWidget::sizeHint() const

{
	return QSize(640, 480);
}

static void normalizeAngle(int &angle)
{
	if (angle < -180)
	angle = 180;
	if (angle > 180)
	angle = -180;
}

void GLWidget::setXRotation(int angle)
{
	normalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::setYRotation(int angle)
{
	normalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::setZRotation(int angle)
{
	normalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::initializeGL()
{
	glShadeModel( GL_SMOOTH );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	//glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	//glHint(GL_FOG_HINT,GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_CULL_FACE );
	glEnable( GL_DEPTH_TEST );
	//glEnable(GL_MULTISAMPLE);
	// Depth to clear depth buffer to
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	// Smooth Color Shading
	glShadeModel(GL_SMOOTH);
	// Set up a light, turn it on.
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT1,GL_POSITION,Light_Position);
	glLightfv(GL_LIGHT1,GL_AMBIENT,Light_Ambient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,Light_Diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR, specular);
	glEnable(GL_LIGHT1);
	// have surface material mirror the color.
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMateriali(GL_FRONT,GL_SHININESS,128);
        glClearColor (255, 255, 255, 255);
}

void GLWidget::paintGL() {
	if (this->mopWorker->mopActive) {
		if (this->mopWorker->ready) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			// Need to manipulate the ModelView matrix to move our model around.
			glMatrixMode(GL_MODELVIEW);

			for (int x(0);x<this->mopWorker->getNumParticles();x++) {
				this->drawParticle(x);
			}
		}
		if(this->selectedParticleOneActive) {
			if (this->selectedParticleOne!=this->selectedParticleTwo) {
				if (this->showSelectedParticleGlyphs) {
					this->markSelectedParticle(this->selectedParticleOne);
				}
			}
		}

		if(this->selectedParticleTwoActive) {
			if (this->selectedParticleOne!=this->selectedParticleTwo) {
				if (this->showSelectedParticleGlyphs) {
					this->markSelectedParticle(this->selectedParticleTwo);
				}
			}
		}

                if (this->showTrails) {
                        this->trailDisplay->displayTrails(this->focusParticle,this->showTrailsForSelectedParticlesOnly,this->selectedParticleOneActive, this->selectedParticleTwoActive, this->selectedParticleOne, this->selectedParticleTwo,xRot,yRot,zRot);
                }

		if (this->showConnectingLine) {
			if((this->selectedParticleOneActive)&&(this->selectedParticleTwoActive)) {
				this->drawLineBetweenParticles(this->selectedParticleOne,this->selectedParticleTwo);
			}
		}

		if (this->allowConsoleUpdate) {
			emit this->clearConsole();
			emit this->updateConsole();
			this->allowConsoleUpdate = false;
		}
                if (this->recordStateToImage) {
                        this->recordImage();
                        this->recordStateToImage = false;
                }

                if (!this->paused) {
                    this->tmpNumParticles = this->mopWorker->getNumParticles();
			this->mopWorker->loadNextState();
			this->allowConsoleUpdate = true;
                        if (this->showTrails) {
                            if (this->tmpNumParticles != this->mopWorker->getNumParticles()) {
                                this->trailDisplay->deleteTrails();
                                this->trailDisplay->createTrails(this->mopWorker, this->trailSize);
                            } else {
                                this->trailDisplay->updateTrails(this->mopWorker);
                            }
                        }
		}
	} else {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void GLWidget::updateConsole() {
	emit this->clearConsole();
	this->text = " State: " + QString::number(this->mopWorker->getStateCount());
	emit sendTextToConsole(this->text);
	this->text = " ";
	emit sendTextToConsole(this->text);
	if (this->selectedParticleOne!=this->selectedParticleTwo) {
		if(this->selectedParticleOneActive) {
			this->text = " Selected Particle One: " + QString::fromStdString(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleOne).name);
			emit sendTextToConsole(this->text);
			this->text = "     Mass: " + QString::number(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleOne).mass);
			emit sendTextToConsole(this->text);
			this->text = "     Radius: " + QString::number(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleOne).radius);
			emit sendTextToConsole(this->text);
			if (this->showStateVector) {
				this->text = "     Position (km)";
				emit sendTextToConsole(this->text);
				this->text = "       x: " + QString::number(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleOne).x);
				emit sendTextToConsole(this->text);
				this->text = "       y: " + QString::number(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleOne).y);
				emit sendTextToConsole(this->text);
				this->text = "       z: " + QString::number(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleOne).z);
				emit sendTextToConsole(this->text);
				this->text = "     Velocity (km/sec)";
				emit sendTextToConsole(this->text);
				this->text = "       xd: " + QString::number((this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleOne).xd)/1000);
				emit sendTextToConsole(this->text);
				this->text = "       yd: " + QString::number((this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleOne).yd)/1000);
				emit sendTextToConsole(this->text);
				this->text = "       zd: " + QString::number((this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleOne).zd)/1000);
				emit sendTextToConsole(this->text);
				this->text = "     Overall Velocity (KM/Sec): " + QString::number(this->calculateVelocity(this->selectedParticleOne,1000));
				emit sendTextToConsole(this->text);
			}
			this->text = " ";
			emit sendTextToConsole(this->text);
		}

		if(this->selectedParticleTwoActive) {
			this->text = " Selected Particle Two: " + QString::fromStdString(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleTwo).name);
			emit sendTextToConsole(this->text);
			this->text = "     Mass: " + QString::number(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleTwo).mass);
			emit sendTextToConsole(this->text);
			this->text = "     Radius: " + QString::number(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleTwo).radius);
			emit sendTextToConsole(this->text);
			if (this->showStateVector) {
				this->text = "     Position (KM)";
				emit sendTextToConsole(this->text);
				this->text = "       x: " + QString::number(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleTwo).x);
				emit sendTextToConsole(this->text);
				this->text = "       y: " + QString::number(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleTwo).y);
				emit sendTextToConsole(this->text);
				this->text = "       z: " + QString::number(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleTwo).z);
				emit sendTextToConsole(this->text);
				this->text = "     Velocity (KM/Sec)";
				emit sendTextToConsole(this->text);
				this->text = "       xd: " + QString::number((this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleTwo).xd)/1000);
				emit sendTextToConsole(this->text);
				this->text = "       yd: " + QString::number((this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleTwo).yd)/1000);
				emit sendTextToConsole(this->text);
				this->text = "       zd: " + QString::number((this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleTwo).zd)/1000);
				emit sendTextToConsole(this->text);
				this->text = "     Overall Velocity (KM/Sec): " + QString::number(this->calculateVelocity(this->selectedParticleTwo,1000));
				emit sendTextToConsole(this->text);
			}
			this->text = " ";
			emit sendTextToConsole(this->text);
		}

		if (this->showDistance) {
			if((this->selectedParticleOneActive)&&(this->selectedParticleTwoActive)) {
				if (this->showAsAU) {
                                        this->text = " Distance Between Particles as AU: " + QString::number(this->convertToAU(this->calculateDistance(this->selectedParticleOne,this->selectedParticleTwo,1)));

				} else {
					this->text = " Distance Between Particles as KM: " + QString::number(this->calculateDistance(this->selectedParticleOne,this->selectedParticleTwo,1000));
				}
				emit sendTextToConsole(this->text);
				this->text = " ";
				emit sendTextToConsole(this->text);
			}
		}
		if (this->showRelativeVelocity) {
			if((this->selectedParticleOneActive)&&(this->selectedParticleTwoActive)) {
				this->text = " Relative Velocities Per Axis";
				emit sendTextToConsole(this->text);
				this->text = "     xd: " + QString::number(sqrt(sqr(((this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleOne).xd)-(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleTwo).xd))/1000)));
				emit sendTextToConsole(this->text);
				this->text = "     yd: " + QString::number(sqrt(sqr(((this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleOne).yd)-(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleTwo).yd))/1000)));
				emit sendTextToConsole(this->text);
				this->text = "     yd: " + QString::number(sqrt(sqr(((this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleOne).zd)-(this->mopWorker->getLoadedState()->getMopItem(this->selectedParticleTwo).zd))/1000)));
				emit sendTextToConsole(this->text);
				this->text = " Relative Velocity Overall (KM/Sec): " + QString::number(this->calculateRelativeVelocity(this->selectedParticleOne,this->selectedParticleTwo,1000));
				emit sendTextToConsole(this->text);
				this->text = " ";
				emit sendTextToConsole(this->text);
			}
		}
	}

}

void GLWidget::drawParticle(int index) {
	glPushMatrix();
	glLoadIdentity();
	glRotated(this->xRot, 1.0, 0.0, 0.0);
	glRotated(this->yRot, 0.0, 1.0, 0.0);
	glRotated(this->zRot, 0.0, 0.0, 1.0);
	glColor3ub (this->mopWorker->getLoadedState()->getMopItem(index).red,this->mopWorker->getLoadedState()->getMopItem(index).green,this->mopWorker->getLoadedState()->getMopItem(index).blue);
	// shift position relative to the current focus particle
	glTranslatef((this->mopWorker->getDisplayState()->getMopItem(index).x)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).x),(this->mopWorker->getDisplayState()->getMopItem(index).y)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).y),(this->mopWorker->getDisplayState()->getMopItem(index).z)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).z));
	// what gets used to represent the particle is decided here
	// first, is this a placemarker particle or an ordinary one?
	if (this->mopWorker->getLoadedState()->getMopItem(index).identity == Advisor::nonInteractive) {
		if (this->showPlacemarkParticles) {
			// draw some lines, a nice 3d crosshair type of thing
			glEnable(GL_LINE_STIPPLE);
			glLineStipple(factor,pattern);
			glDisable(GL_LIGHTING);
			glBegin(GL_LINES);
			glVertex3f(-10,0,0);
			glVertex3f(10,0,0);
			glVertex3f(0,-10,0);
			glVertex3f(0,10,0);
			glVertex3f(0,0,-10);
			glVertex3f(0,0,10);
			glEnd();
			glDisable(GL_LINE_STIPPLE);
			glEnable(GL_LIGHTING);
			// and stick a little cube at the centre
			glutSolidCube(2);
		}
	} else { // not a placemarker, goody :)
		switch(this->particleDisplayStyle) {
		case Advisor::Spheres: { // ordinary sphere
				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
				glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
				glutSolidSphere (this->mopWorker->getLoadedState()->getMopItem(index).visualRepresentation/3, 30, 20);
			}
			break;
		case Advisor::Markers: { // group of pixels, lower graphic display cost
				glDisable(GL_LIGHTING);
				glBegin(GL_LINES);
				glVertex3f(-2,0,0);
				glVertex3f(2,0,0);
				glVertex3f(0,-2,0);
				glVertex3f(0,2,0);
				glVertex3f(0,0,-2);
				glVertex3f(0,0,2);
				glEnd();
				glEnable(GL_LIGHTING);
			}
			break;
		case Advisor::Dots: { // single pixel, lowest graphics display cost
				glDisable(GL_LIGHTING);
				glBegin(GL_POINTS);
				glVertex3f(0,0,0);
				glEnd();
				glEnable(GL_LIGHTING);
			}
			break;
		}
	}
	glPopMatrix();
}

void GLWidget::markSelectedParticle(int index) {
	glPushMatrix();
	glLoadIdentity();
	glRotated(xRot, 1.0, 0.0, 0.0);
	glRotated(yRot, 0.0, 1.0, 0.0);
	glRotated(zRot, 0.0, 0.0, 1.0);
	// shift position relative to the current focus particle
	glTranslatef((this->mopWorker->getDisplayState()->getMopItem(index).x)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).x+ 20),(this->mopWorker->getDisplayState()->getMopItem(index).y)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).y),(this->mopWorker->getDisplayState()->getMopItem(index).z)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).z));
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor4f (0.0f,0.0f,0.0f, .10); //black
	glVertex3f(0,0,0);
	glVertex3f(+20,0,0);
	glEnd();
	glEnable(GL_LIGHTING);
	//apply current rotation to x
	glRotatef (selectedParticleRotation, 1.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidCube(3);
	glColor3ub (this->mopWorker->getLoadedState()->getMopItem(index).red,this->mopWorker->getLoadedState()->getMopItem(index).green,this->mopWorker->getLoadedState()->getMopItem(index).blue);
	glutSolidTorus(2, 3, 8, 16);
	if(selectedParticleRotation<360) {
		selectedParticleRotation++;
	} else {
		selectedParticleRotation = 0;
	}
	glPopMatrix();
}

void GLWidget::drawLineBetweenParticles(int index1, int index2) {
	if (index1!=index2) {
		glPushMatrix();
		glLoadIdentity();
		glRotated(xRot, 1.0, 0.0, 0.0);
		glRotated(yRot, 0.0, 1.0, 0.0);
		glRotated(zRot, 0.0, 0.0, 1.0);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(factor,pattern);
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
		glColor4f (0.0f,0.0f,0.0f, .10);
		glVertex3f(((this->mopWorker->getDisplayState()->getMopItem(index1).x)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).x)),(this->mopWorker->getDisplayState()->getMopItem(index1).y)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).y),(this->mopWorker->getDisplayState()->getMopItem(index1).z)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).z));
		glVertex3f(((this->mopWorker->getDisplayState()->getMopItem(index2).x)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).x)),(this->mopWorker->getDisplayState()->getMopItem(index2).y)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).y),(this->mopWorker->getDisplayState()->getMopItem(index2).z)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).z));
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_LINE_STIPPLE);
		glPopMatrix();
	}
}

void GLWidget::drawLineBetweenParticles(int index1, int index2, int r, int g, int b) {
	if (index1!=index2) {
		glPushMatrix();
		glLoadIdentity();
		glRotated(xRot, 1.0, 0.0, 0.0);
		glRotated(yRot, 0.0, 1.0, 0.0);
		glRotated(zRot, 0.0, 0.0, 1.0);
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
		glColor4f (r,g,b, .10);
		glVertex3f(((this->mopWorker->getDisplayState()->getMopItem(index1).x)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).x)),(this->mopWorker->getDisplayState()->getMopItem(index1).y)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).y),(this->mopWorker->getDisplayState()->getMopItem(index1).z)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).z));
		glVertex3f(((this->mopWorker->getDisplayState()->getMopItem(index2).x)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).x)),(this->mopWorker->getDisplayState()->getMopItem(index2).y)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).y),(this->mopWorker->getDisplayState()->getMopItem(index2).z)-(this->mopWorker->getDisplayState()->getMopItem(this->focusParticle).z));
		glEnd();
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}

void GLWidget::resizeGL(int width, int height) {
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (-(width/2),(width/2), -(height/2), (height/2), -1000.0F, 1000.0F);

	glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
	lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + 8 * dy);
		setYRotation(yRot + 8 * dx);
	} else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + 8 * dy);
		setZRotation(zRot + 8 * dx);
	}
	lastPos = event->pos();
}

void GLWidget::changeTrailLength(int trailSize) {
	if (this->showTrails) {
		this->trailDisplay->resizeTrails(trailSize);
	}
}

void GLWidget::AddNewTrail() {
	if (this->showTrails) {
		if (this->mopWorker->getLoadedState()->getMopItem(this->mopWorker->getNumParticles()-1).identity!=Advisor::nonInteractive) {
			this->trailDisplay->addTrail();
		}
	}
}

bool GLWidget::getPausedState() {
	return this->paused;
}

void GLWidget::setParticleDisplayStyle(int style) {
	this->particleDisplayStyle = style;
}

void GLWidget::setTrailLength(int size) {
    if (this->showTrails) {
        if (this->trailDisplay->getDoTrailsExist()) {
                this->trailDisplay->resizeTrails(size);
        }
    } else {
        this->trailSize = size;
    }
}

void GLWidget::setShowTrails(bool choice) {
    this->showTrails = choice;
        if (this->showTrails) {
                this->trailDisplay->createTrails(this->mopWorker, this->trailSize);
	} else {
		if(this->trailDisplay->getDoTrailsExist()){
                        this->trailDisplay->deleteTrails();
		}
        }
}

void GLWidget::setShowTrailsForSelectedParticlesOnly(bool choice) {
	this->showTrailsForSelectedParticlesOnly = choice;
}

void GLWidget::setShowRelativeVelocity(bool choice) {
	this->showRelativeVelocity = choice;
	this->allowConsoleUpdate = true;
}

void GLWidget::setShowStateVector(bool choice) {
	this->showStateVector = choice;
	this->allowConsoleUpdate = true;
}

void GLWidget::setShowAsAU(bool choice) {
	this->showAsAU = choice;
	this->allowConsoleUpdate = true;
}

void GLWidget::setShowDistance(bool choice) {
	this->showDistance = choice;
	this->allowConsoleUpdate = true;
}

void GLWidget::setShowConnectingLine(bool choice) {
	this->showConnectingLine = choice;
}

void GLWidget::setShowSelectedParticleGlyphs(bool choice) {
	this->showSelectedParticleGlyphs = choice;
}

void GLWidget::setSelectedParticleOne(int index) {
	if ((index>=0)&&(index<this->mopWorker->getNumParticles())) {
		this->selectedParticleOne = index;
		this->allowConsoleUpdate = true;
	}
	if (index>=this->mopWorker->getNumParticles()) {
		emit lastParticleIndex_selParticle_1(this->mopWorker->getNumParticles()-1);
	}
}

void GLWidget::setSelectedParticleTwo(int index) {
	if ((index>=0)&&(index<this->mopWorker->getNumParticles())) {
		this->selectedParticleTwo = index;
		this->allowConsoleUpdate = true;
	}
	if (index>=this->mopWorker->getNumParticles()) {
		emit lastParticleIndex_selParticle_2(this->mopWorker->getNumParticles()-1);
	}
}

void GLWidget::allowRecordStateToImage() {
	this->recordStateToImage = true;
}

void GLWidget::setShowPlacemarkParticles(bool choice) {
	this->showPlacemarkParticles = choice;
}

void GLWidget::setFocusParticle(int index) {
	if ((index>=0)&&(index<this->mopWorker->getNumParticles())) {
		this->focusParticle = index;
	}
	if (index>=this->mopWorker->getNumParticles()) {
		emit lastParticleIndex(this->mopWorker->getNumParticles()-1);
	}
}

void GLWidget::setScaler(int level) {
	this->mopWorker->setScaler(level);
        this->trailDisplay->clearTrails();
}

void GLWidget::requirePlayBackRestart() {
	this->mopWorker->restartPlayback();
        this->trailDisplay->clearTrails();
}

void GLWidget::setPausedState(bool choice) {
	this->paused = choice;
}

double GLWidget::sqr( double x) const {
	return ((x)*(x));
}

double GLWidget::calculateDistance(int index1, int index2, int devisor) {
	if (devisor!=0) {
		double m1x(this->mopWorker->getLoadedState()->getMopItem(index1).x);
		double m1y(this->mopWorker->getLoadedState()->getMopItem(index1).y);
		double m1z(this->mopWorker->getLoadedState()->getMopItem(index1).z);
		double m2x(this->mopWorker->getLoadedState()->getMopItem(index2).x);
		double m2y(this->mopWorker->getLoadedState()->getMopItem(index2).y);
		double m2z(this->mopWorker->getLoadedState()->getMopItem(index2).z);
                return sqrt(sqr((m1x/devisor) - (m2x/devisor))+sqr((m1y/devisor) - (m2y/devisor))+sqr((m1z/devisor) - (m2z/devisor)));
	}
	return -1; // default fail
}

double GLWidget::calculateVelocity(int index,int devisor) {
	if (devisor!=0) {
		double x(this->mopWorker->getLoadedState()->getMopItem(index).xd);
		double y(this->mopWorker->getLoadedState()->getMopItem(index).yd);
		double z(this->mopWorker->getLoadedState()->getMopItem(index).zd);
		return sqrt(sqr(x)+sqr(y)+sqr(z))/devisor;
	}
	return -1; // default fail
}

double GLWidget::calculateRelativeVelocity(int index1, int index2,int devisor) {
	if (devisor!=0) {
		double x1(this->mopWorker->getLoadedState()->getMopItem(index1).xd);
		double y1(this->mopWorker->getLoadedState()->getMopItem(index1).yd);
		double z1(this->mopWorker->getLoadedState()->getMopItem(index1).zd);
		double x2(this->mopWorker->getLoadedState()->getMopItem(index2).xd);
		double y2(this->mopWorker->getLoadedState()->getMopItem(index2).yd);
		double z2(this->mopWorker->getLoadedState()->getMopItem(index2).zd);
		return sqrt(sqr(x1-x2)+sqr(y1-y2)+sqr(z1-z2))/devisor;
	}
	return -1; // default fail
}

double GLWidget::convertToAU(double distance) {
        return distance/AU;
}

void GLWidget::setSelectedParticleOneActiveState(bool choice) {
	this->selectedParticleOneActive = choice;
	this->allowConsoleUpdate = true;
}

void GLWidget::setSelectedParticleTwoActiveState(bool choice) {
	this->selectedParticleTwoActive = choice;
	this->allowConsoleUpdate = true;
}

void GLWidget::recordTrails(){
	if (!this->paused) {
		if (this->showTrails) {
			if (this->trailDisplay->getTrailSize()>0) {
				//this->trailDisplay->updateTrails();
			}
		}
	}
}

void GLWidget::drawTrails() {
	if (this->showTrails) {

	}
}

void GLWidget::recordImage() {
	if (this->mopWorker->ready) {
		QString fname,fnum;
		fname = "image_";
		fnum.setNum(this->imageNameCounter);
		fname.append(fnum);
		fname.append(".png");
		QImage image = this->grabFrameBuffer();
		QString fileName = QFileDialog::getSaveFileName(
		this,
		tr("Save as Image file"),
		(fname),
		tr("PNG (*.png);;Windows Bitmap (*.bmp);;All Files (*.*)"));

		if(fileName != ""){
			bool isOk = image.save(fileName);
                        if(!isOk){
				QString msgText = tr("Failed to write into ") + fileName;
				QMessageBox::critical(this, tr("Error Writing"), msgText);
			} else {
				this->imageNameCounter++;
			}
		}
	}
        this->recordStateToImage=false;
}

void GLWidget::resetState() {
	this->xRot = 0;
	this->yRot = 0;
	this->zRot = 0;
        this->trailSize = 100;
	this->particleDisplayStyle = Advisor::Spheres;
	this->selectedParticleOne = 0;
	this->selectedParticleTwo = 0;
	this->focusParticle = 0;
	this->selectedParticleRotation = 0;
        this->imageNameCounter = 0;
	this->paused = true;
	this->showTrails = false;
	this->showTrailsForSelectedParticlesOnly = false;
	this->showRelativeVelocity = false;
	this->showStateVector = false;
	this->showAsAU = false;
	this->showDistance = false;
	this->showConnectingLine = false;
	this->showSelectedParticleGlyphs = false;
	this->recordStateToImage = false;
	this->showPlacemarkParticles = true;
	this->restartPlayback = false;
	this->selectedParticleOneActive = false;
	this->selectedParticleTwoActive = false;
	this->allowConsoleUpdate = true;
}

int GLWidget::getTrailSize() {
    return this->trailSize;
}

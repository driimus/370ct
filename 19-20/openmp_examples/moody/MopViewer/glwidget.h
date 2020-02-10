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

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "../moody/capsule/capsuleBase/etc/Advisor.h"
#include "../moody/capsule/capsuleBase/etc/Numerics.h"
#include "qtglut.h"
#include "mophandling.h"
#include "trailmanager.h"
//#include <QDebug>


class GLWidget : public QGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();
	MopHandling * mopWorker;
	QSize minimumSizeHint() const;
        QSize sizeHint() const;
        void resizeTrails(int trailSize);
	void changeTrailLength(int trailSize);
	void AddNewTrail();
        int getTrailSize();
        TrailManager *getTrailDisplay() {
            return this->trailDisplay;
        }

signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);
	void scalerChange(int scaler);
	void lastParticleIndex(int index);
	void lastParticleIndex_selParticle_1(int index);
	void lastParticleIndex_selParticle_2(int index);
	void clearConsole();
	void sendTextToConsole(QString text);
	public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	bool getPausedState();
	void setParticleDisplayStyle(int style);
	void setTrailLength(int size);
	void setShowTrails(bool choice);
	void setShowTrailsForSelectedParticlesOnly(bool choice);
	void setShowRelativeVelocity(bool choice);
	void setShowStateVector(bool choice);
	void setShowAsAU(bool choice);
	void setShowDistance(bool choice);
	void setShowConnectingLine(bool choice);
	void setShowSelectedParticleGlyphs(bool choice);
	void setSelectedParticleOne(int index);
	void setSelectedParticleTwo(int index);
	void allowRecordStateToImage();
	void setShowPlacemarkParticles(bool choice);
	void setFocusParticle(int index);
	void setScaler(int level);
	void requirePlayBackRestart();
	void setPausedState(bool choice);
	void setSelectedParticleOneActiveState(bool choice);
	void setSelectedParticleTwoActiveState(bool choice);
	void resetState();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	QPoint lastPos;
	QString text;
	TrailManager *trailDisplay;
	int imageNameCounter;
	int xRot;
	int yRot;
        int zRot;
	int particleDisplayStyle;
	int selectedParticleOne;
	int selectedParticleTwo;
	int focusParticle;
	int selectedParticleRotation;
        int trailSize;
	bool paused;
	bool showTrails;
	bool showTrailsForSelectedParticlesOnly;
	bool showRelativeVelocity;
	bool showStateVector;
	bool showAsAU;
	bool showDistance;
	bool showConnectingLine;
	bool showSelectedParticleGlyphs;
	bool recordStateToImage;
	bool showPlacemarkParticles;
	bool restartPlayback;
	bool selectedParticleOneActive;
	bool selectedParticleTwoActive;
	bool allowConsoleUpdate;
        int tmpNumParticles;



	// line stipple vars
	int factor;
	ushort pattern;
	// lighting etc
	float Light_Ambient[4];
	float Light_Diffuse[4];
	float Light_Position[4];
	float gray[4];
	float specular[4];
	float specref[4];
	float no_mat[4];
	float mat_ambient[4];
	float mat_ambient_color[4];
	float mat_diffuse[4];
	float mat_specular[4];

	float mat_emission[4];
	float no_shininess;
	float low_shininess;
	float high_shininess;
	//methods
	void drawParticle(int index);
	void markSelectedParticle(int index);
	void drawLineBetweenParticles(int index1, int index2);
	void drawLineBetweenParticles(int index1, int index2, int r, int g, int b);
	void recordTrails();
	void drawTrails();
	double sqr( double x) const;
	double calculateDistance(int index1, int index2, int devisor);
	void drawText(int x, int y, QColor colour, QString text);
	void updateConsole();
	double convertToAU(double distance);
	void recordImage();
	double calculateVelocity(int index,int devisor);
	double calculateRelativeVelocity(int index1, int index2,int devisor);
};

#endif

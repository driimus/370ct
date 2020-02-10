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
#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <QWidget>
#include <qclipboard.h>
namespace Ui {
	class TextDisplay;
}

class TextDisplay : public QWidget
{
	Q_OBJECT

public:
	explicit TextDisplay(QWidget *parent = 0);
	~TextDisplay();
	public slots:
	void clearText();
	void writeText(QString text);
private:
	Ui::TextDisplay *ui;

	private slots:
	void on_copyToClipboardButton_pressed();
};

#endif // TEXTDISPLAY_H

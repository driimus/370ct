#include "textdisplay.h"
#include "ui_textdisplay.h"

TextDisplay::TextDisplay(QWidget *parent) :
QWidget(parent),
ui(new Ui::TextDisplay)
{
	ui->setupUi(this);
}

TextDisplay::~TextDisplay()
{
	delete ui;
}

void TextDisplay::clearText() {
	ui->console->clear();
}

void TextDisplay::writeText(QString text) {
	ui->console->appendPlainText(text);
}

void TextDisplay::on_copyToClipboardButton_pressed() {
	QClipboard *cb = QApplication::clipboard();
	cb->setText(ui->console->document()->toPlainText());
}



#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QMessageBox>
#include <iostream>
#include "Unpossible.h"
#include "Validation.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto widget = new QWidget;
    auto layout = new QVBoxLayout(widget);

    auto button = new QPushButton("Check", nullptr);
    auto text = new QTextEdit("", widget);

    QObject::connect(button, &QPushButton::clicked, [&text](){
      std::string value = text->toPlainText().toStdString();
	    std::cout << value;
	    bool result = isPossible(reformatInput(value));
      QString res = result ? "correct" : "bad";
      QMessageBox::information(nullptr,"Answer", res);
    });

    layout->addWidget(text);
    layout->addWidget(button);

    widget->setLayout(layout);
    widget->show();

    return QApplication::exec();
}
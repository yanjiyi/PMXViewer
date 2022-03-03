#include <QApplication>
#include "HeaderWidget.h"


int main(int argc, char **argv) {
  QApplication app(argc, argv);

  HeaderWidget widget;
  widget.show();

  return app.exec();
}

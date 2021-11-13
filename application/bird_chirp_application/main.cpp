#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale: uiLanguages) {
    const QString baseName = "bird_chirp.application_" + QLocale(locale).name();
	if (translator.load(":/i18n/" + baseName)) {
	  application.installTranslator(&translator);
	  break;
	}
  }

  MainWindow main_window;
  main_window.show();
  return application.exec();
}

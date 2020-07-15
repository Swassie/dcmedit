#pragma once
#include <QWidget>

class Main_window;

class Start_view : public QWidget
{
  Q_OBJECT

public:
  Start_view(Main_window&);
  void setup();

private:
  Main_window& m_main_window;
};

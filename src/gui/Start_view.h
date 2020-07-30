#pragma once
#include <QWidget>

class Main_window;

class Start_view : public QWidget
{
  Q_OBJECT

public:
  void setup(Main_window&);
};

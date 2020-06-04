#include "View.h"

View::View() {
    static size_t i = 0;
    QPalette pal = palette();
    setMinimumSize(QSize(200, 200));
    pal.setColor(QPalette::Background, QColor(i, i + 30, i + 50));
    setAutoFillBackground(true);
    setPalette(pal);
    i += 10;
}

#pragma once
#include "ui/progressbar/IProgress_view.h"

#include <QDialog>
#include <QLabel>
#include <QProgressBar>

class Progress_view : public QDialog, public IProgress_view
{
    Q_OBJECT
public:
    Progress_view(QWidget*);

    void set_max(int) override;
    void set_value(int) override;
    void set_text(const std::string&) override;

    void show() override;
    void close() override;

private:
    void reject() override;

    QProgressBar* m_progress_bar;
    QLabel* m_text;
};

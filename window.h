#ifndef WINDOW_H
#define WINDOW_H
#include "button.h"

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFormLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QScrollArea>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE
class Button;

class Window : public QWidget
{
    Q_OBJECT
public:
    Window(QWidget* parent = nullptr);
    void setMode();
    double countFitts();
    int getLength();
    void resetTable();
private slots:
    void clickButton();
    void timeHit();
private:
    template<typename PointerToMemberFunction>
    Button* createButton(const QString&, const PointerToMemberFunction&);
    template<typename PointerToMemberFunction>
    Button* createNewButton(const QString&, const PointerToMemberFunction&);
    Button* button;
    enum class Mode {
        FIRST = 0,
        SECOND,
        THIRD,
        FOURTH
    };
    bool m_is_created = false;
    QTimer* m_timer;
    QElapsedTimer* m_elapsed_time;
    Mode m_mode = Mode::FIRST;
    QTableWidget *m_table;
    enum {NUMBER_MODE = 4};
    Button* m_buttons_mode[NUMBER_MODE];
    int m_time = 0;
    int index = 1;

    QScrollArea* scroll_area;
    QGroupBox* m_table_box;
    QGridLayout* m_table_layout;
    QGroupBox *m_buttons_box;
    QWidget* m_window_widget;
    Button* new_button;
    QGridLayout* m_window_layout;
    QGroupBox *m_window_box;
    QWidget* m_buttons_widget;
    QVBoxLayout* m_buttons_layout;
    QGridLayout* m_main_layout;

    int m_button_x = 0;
    int m_button_y = 0;
};

#endif // WINDOW_H

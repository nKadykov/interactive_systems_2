#include "window.h"
#include <QtMath>

Window::Window(QWidget* parent) : QWidget(parent), m_timer(new QTimer(this)), m_elapsed_time(new QElapsedTimer()) {
    m_table = new QTableWidget(this);
    m_table->setRowCount(20);
    m_table->setColumnCount(4);
    m_window_widget = new QWidget();
    QTableWidgetItem* item1 = new QTableWidgetItem;
    item1->setText(tr("Mode"));
    m_table->setItem(0, 0, item1);
    QTableWidgetItem* item2 = new QTableWidgetItem;
    item2->setText(tr("Time"));
    m_table->setItem(0, 1, item2);
    QTableWidgetItem* item3 = new QTableWidgetItem;
    item3->setText(tr("Fitts"));
    m_table->setItem(0, 2, item3);
    QTableWidgetItem* item4 = new QTableWidgetItem;
    item4->setText(tr("Length"));
    m_table->setItem(0, 3, item4);

    for(int i = 0; i < NUMBER_MODE; ++i) {
        m_buttons_mode[i] = createButton(tr("MODE: ") + QString::number(i + 1), &Window::setMode);
        m_buttons_mode[i]->setStyleSheet("background-color: white");
    }

    connect(m_timer, &QTimer::timeout, this, &Window::timeHit);

    m_buttons_layout = new QVBoxLayout;
    for(int i = 0; i < NUMBER_MODE; ++i) {
        m_buttons_layout->addWidget(m_buttons_mode[i]);
    }
    m_buttons_box = new QGroupBox(tr("Mode"));
    m_buttons_box->setLayout(m_buttons_layout);

    m_window_layout = new QGridLayout;
    m_window_box = new QGroupBox;
    m_window_box->setLayout(m_window_layout);
    m_window_box->setFixedSize(QSize(1280, 720));

    m_table_box = new QGroupBox(tr("Table"));
    m_table_layout = new QGridLayout;
    m_table_layout->addWidget(m_table);
    m_table_box->setLayout(m_table_layout);
    m_table_box->setFixedSize(QSize(400, 500));

    m_main_layout = new QGridLayout;
    m_main_layout->addWidget(m_window_box, 0, 0, 2, 1);
    m_main_layout->addWidget(m_buttons_box, 0, 1, 1, 1);
    m_main_layout->addWidget(m_table_box, 1, 1, 1, 1);
    setLayout(m_main_layout);

    m_timer->setInterval(1000);
    m_elapsed_time->start();
    m_timer->start();
}

template<typename PointerToMemberFunction>
Button* Window::createButton(const QString &text, const PointerToMemberFunction &member) {
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member);
    return button;
}

template<typename PointerToMemberFunction>
Button* Window::createNewButton(const QString &text, const PointerToMemberFunction &member) {
    Button *button = new Button(text, m_window_widget);
    connect(button, &Button::clicked, this, member);
    return button;
}

void Window::clickButton() {
    Button *clicked_button = qobject_cast<Button*>(sender());
    m_is_created = false;
    int e = m_elapsed_time->elapsed();

    if(index > 20) {
        index = 1;
    }

    QTableWidgetItem* item1 = new QTableWidgetItem;
    item1->setText(QString::number(static_cast<int>(m_mode) + 1));
    m_table->setItem(index, 0, item1);
    QTableWidgetItem* item2 = new QTableWidgetItem;
    item2->setText(QString::number(e / 1000) + "." + QString::number(e % 1000));
    m_table->setItem(index, 1, item2);
    QTableWidgetItem* item3 = new QTableWidgetItem;
    item3->setText(QString::number(this->countFitts()));
    m_table->setItem(index, 2, item3);
    QTableWidgetItem* item4 = new QTableWidgetItem;
    item4->setText(QString::number(this->getLength()));
    m_table->setItem(index, 3, item4);

    m_table->setItem(index, 2, item3);
    m_elapsed_time->restart();
    index++;
    m_window_layout->removeWidget(m_window_widget);
    m_window_widget = new QWidget();
    m_button_x = 0;
    clicked_button->deleteLater();
}

double Window::countFitts() {
    return qLn(this->getLength() / 100 + 1) / qLn(2);
}

int Window::getLength() {
    int length = qSqrt(qPow(m_button_x + 50, 2) + qPow(m_button_y + 50, 2));
    return length;
}

void Window::resetTable() {
    m_table->clear();
    QTableWidgetItem* item1 = new QTableWidgetItem;
    item1->setText(tr("Mode"));
    m_table->setItem(0, 0, item1);
    QTableWidgetItem* item2 = new QTableWidgetItem;
    item2->setText(tr("Time"));
    m_table->setItem(0, 1, item2);
    QTableWidgetItem* item3 = new QTableWidgetItem;
    item3->setText(tr("Fitts"));
    m_table->setItem(0, 2, item3);
    QTableWidgetItem* item4 = new QTableWidgetItem;
    item4->setText(tr("Length"));
    m_table->setItem(0, 3, item4);
}

void Window::setMode() {
    Button *clicked_button = qobject_cast<Button*>(sender());
    if(clicked_button == m_buttons_mode[0]) {
        m_mode = Mode::FIRST;
        resetTable();
        index = 1;
    }
    if(clicked_button == m_buttons_mode[1]) {
        m_mode = Mode::SECOND;
        resetTable();
        index = 1;
    }
    if(clicked_button == m_buttons_mode[2]) {
        m_mode = Mode::THIRD;
        resetTable();
        index = 1;
    }
    if(clicked_button == m_buttons_mode[3]) {
        m_mode = Mode::FOURTH;
        resetTable();
        index = 1;
    }
}

void Window::timeHit() {
    int time = 500;
    int elapsed = m_elapsed_time->elapsed();
    int index;
    int keyboard_part = 0;
    int width;
    if(elapsed > time && (!m_is_created)) {
        switch (m_mode) {
            case Mode::FIRST:
                m_button_x = 1000;
                m_button_y = 0;
                new_button = createNewButton(tr(""), &Window::clickButton);
                new_button->setGeometry(m_button_x, m_button_y, 100, 100);
                m_window_layout->addWidget(m_window_widget);
                m_is_created = true;
                m_elapsed_time->start();
                break;
            case Mode::SECOND:
                m_button_x = rand() % 1000;
                m_button_y = 0;
                new_button = createNewButton(tr(""), &Window::clickButton);
                new_button->setGeometry(m_button_x, m_button_y, 100, 100);
                m_window_layout->addWidget(m_window_widget);
                m_is_created = true;
                m_elapsed_time->start();
                break;
            case Mode::THIRD:
                m_button_x = rand() % 1000;
                m_button_y = 0;
                new_button = createNewButton(tr(""), &Window::clickButton);
                width = rand()%50;
                new_button->setGeometry(m_button_x, m_button_y, 50 + width, 50 + width);
                m_window_layout->addWidget(m_window_widget);
                m_is_created = true;
                m_elapsed_time->start();
                break;
            case Mode::FOURTH:
                m_button_x = rand() % 1000;
                m_button_y = rand() % 500;
                new_button = createNewButton(tr(""), &Window::clickButton);
                new_button->setGeometry(m_button_x, m_button_y, 100, 100);
                m_window_layout->addWidget(m_window_widget);
                m_is_created = true;
                m_elapsed_time->start();
                break;
        }
    }
}

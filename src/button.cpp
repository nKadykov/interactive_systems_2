#include "button.h"

Button::Button(const QString &text, QWidget* parent) : QToolButton(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setText(text);
}

QSize Button::sizeHint() const {
    QSize size = QToolButton::sizeHint();
    size.rheight() += 40;
    size.rwidth() = qMax(size.width(), size.height());

    return size;
}

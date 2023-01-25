#include "counter.h"

Counter::Counter(QWidget * parent)
    : QWidget(parent), layout(this)
    , gray_background(this), colored_background(this)
{
    connect(&colored_background, &QPushButton::clicked, [=, this]{emit clicked();});
}

void Counter::operator = (Counter rhs)
{
    this->setParent(rhs.parentWidget());
}

void Counter::swap_background(bool colored)
{
    gray_background.setVisible(!colored);
    colored_background.setVisible(colored);
}

void Counter::setText(QString text)
{
    gray_background.setText(text);
    colored_background.setText(text);
}

void Counter::default_style(QString gray_url, QString colored_url)
{
    this->setStyleSheet(" QPushButton {"
                        "border: none;"
                        "text-align: right;"
                        "font-size: 30px;"
                        "font-weight: bold;"
                        "color : #674d3c;"
                        "}");
    gray_background.setStyleSheet("QWidget {background-image:url("+gray_url+")}");
    gray_background.show();
    colored_background.setStyleSheet("QWidget {background-image:url("+colored_url+")}");
    colored_background.hide();

    layout.addWidget(&gray_background);
    layout.addWidget(&colored_background);
    layout.setContentsMargins(0,0,0,0);
}

void Counter::set_fixed_size(int width, int height)
{
    gray_background.setFixedSize(width, height);
    colored_background.setFixedSize(width, height);
}

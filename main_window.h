#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <optional>

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>

#include "run_in_background.h"

class Window : public QWidget {
    Q_OBJECT
public:
    Window() :
        QWidget{},
        button_{new QPushButton{"Run", this}},
        text_edit_{new QTextEdit{this}}
    {
        auto *layout = new QVBoxLayout{this};
        layout->addWidget(button_);
        layout->addWidget(text_edit_);

        connect(button_, &QPushButton::clicked, this, &Window::button_clicked);
    }

public slots:
    void button_clicked(bool) {
        // string result
        run_in_background(
            []() {
                std::this_thread::sleep_for(std::chrono::seconds{1});
                return QString{"string"};
            },
            [text_edit = this->text_edit_](QString result) {
                // no need to synchronize access to text edit
                text_edit->append(result);
            });

        // number result
        run_in_background(
            []() {
                std::this_thread::sleep_for(std::chrono::seconds{2});
                return 12345;
            },
            [text_edit = this->text_edit_](int result) {
                // no need to synchronize access to text edit
                text_edit->append(QString::number(result));
            });
    }

private:
    QPushButton *button_{};
    QTextEdit *text_edit_{};
};

#endif // MAIN_WINDOW_H

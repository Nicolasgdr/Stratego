#ifndef WELCOME_HOME_PAGE_H
#define WELCOME_HOME_PAGE_H

#include <QWidget>
class Client;

namespace Ui {
class welcome_home_page;
}

/**
 * @brief Class of the connexion frame view.
 */
class welcome_home_page : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief Creates a new connexion frame.
     * @param parent The parent widget of the connexion frame
     */
    welcome_home_page(QWidget *parent = nullptr);
    /**
     * @brief Creates a new connexion frame, with client controller
     * @param parent The parent widget of the connexion frame
     * @param controller The controller for the client.
     */
    welcome_home_page(QWidget*parent=nullptr,Client* controller=nullptr);
    /**
     * @brief Display the connexion frame
     */
    void show_welcome_gui();
    /**
     * @brief Sets the connexion button enabled.
     */
    void unlock_button();
    /**
     * @brief Close the connection frame.
     */
    void close_windows();

private slots:
    void on__sendBt_clicked();

private:

    Ui::welcome_home_page *ui;
    Client * controller;
};

#endif // WELCOME_HOME_PAGE_H

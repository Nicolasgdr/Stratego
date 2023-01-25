#include "listofgame.h"
#include "ui_listofgame.h"
#include "Client.h"
#include <QMessageBox>
#include <QTimer>

ListOfGame::ListOfGame(QWidget *parent, Client* cli) :
    QWidget(parent),
    ui(new Ui::ListOfGame),
    cli(cli)
{
    ui->setupUi(this);
    ui->pseudo->setText("Welcome " + cli->get_player_pseudo());
    connect(ui->AvailableGame, &QListWidget::itemClicked, this, &ListOfGame::on_clicked_item);
}

void ListOfGame::showListOfGame(){
    this->show();
}

void ListOfGame::refresh(std::vector<lobby_info> lobbies, int nbPlayers, int stat){
    ui->nbVictories->setText(QString::number(stat));
    ui->AvailableGame->clear();
    ui->NbPlayerOnline->setText(QString::number(nbPlayers));
    for (lobby_info game : lobbies){
        CaseLobby *case_lobby = new CaseLobby(game.creator, game.id_game, game.color, ui->AvailableGame);
        ui->AvailableGame->addItem(case_lobby);
    }
}

void ListOfGame::showPrivateGame(int gameId){
    QString msg = "Game id ";
    msg += QString::number(gameId);
    msg += ". Remember it.";

    QMessageBox* box = new QMessageBox;
    box->setWindowTitle("Private Game");
    box->setText(msg);
    box->setStandardButtons(QMessageBox::Ok);
    box->setDefaultButton(QMessageBox::Ok);
    box->show();
}

void ListOfGame::showError(QString msg){
    QMessageBox* box = new QMessageBox;
    box->setWindowTitle("Error");
    box->setText(msg);
    box->setStandardButtons(QMessageBox::Ok);
    box->setDefaultButton(QMessageBox::Ok);
    box->show();
    cli->setSoloGame(false);
    cli->returning_to_lobby();
}

void ListOfGame::on_NewGameButton_clicked()
{
    bool isPrivate = ui->Button_private->isChecked();
    bool isAlone = ui->Button_solo->isChecked();
    Color color = (ui->comboBox->currentText() == "Red") ? Color::RED : Color::BLUE;
    cli->create_game(isPrivate,isAlone,color);
    ui->NewGameButton->setDisabled(true);
}

void ListOfGame::on_clicked_item(QListWidgetItem* item){
    CaseLobby * i = static_cast<CaseLobby *>(item);
    if(i->getCreator() != cli->get_player_pseudo()){
        cli->launch_game(cli->get_player_pseudo(),i->getGameId(),i->getColor());
        ui->NewGameButton->setDisabled(false);
        this->hide();
    }
}

void ListOfGame::on_join_clicked(){
    cli->launch_game(cli->get_player_pseudo(),ui->privateGame->text().toInt());
}

void ListOfGame::enableCreateButton(){
    ui->NewGameButton->setDisabled(false);
}

void ListOfGame::on_reload_game_clicked()
{
    cli->setSoloGame(true);
    cli->reload_game(ui->id_game->text().toInt());
}


void ListOfGame::on_Button_private_toggled(bool checked)
{
    if(checked)
        ui->Button_solo->setCheckable(false);
    if(!checked)
        ui->Button_solo->setCheckable(true);
}


void ListOfGame::on_Button_solo_toggled(bool checked)
{
    if(checked){
        ui->Button_private->setCheckable(false);
        ui->comboBox->setEnabled(false);
        ui->comboBox->setCurrentIndex(0);
    }
    if(!checked){
        ui->Button_private->setCheckable(true);
        ui->comboBox->setEnabled(true);
    }
}


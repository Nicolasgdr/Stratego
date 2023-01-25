#include "convert.h"

QString cvrt::to_qstring(Color color)
{
    switch (color)
    {
        case RED : return "Rouge";
        case BLUE : return "Bleu";
        case NONE : return "Incolore";
        default : return "N/A";
    }
}

QString cvrt::to_qstring(Rank rank)
{
    switch (rank)
    {
    case FLAG : return "Drapeau";
    case SPY : return "Espionne";
    case SCOUT : return "Eclaireur";
    case MINER : return "Demineur";
    case SERGEANT : return "Sergent";
    case LIEUTENANT : return "Lieutenant";
    case CAPTAIN : return "Capitaine";
    case MAJOR : return "Major";
    case COLONEL : return "Colonel";
    case GENERAL : return "General";
    case MARSHAL : return "Marechal";
    case BOMB : return "Bombe";
    case UNKNOWN : return "Inconnu";
    default : return "N/A";
    }
}

char cvrt::to_char(Color color)
{
    switch (color)
    {
        case RED : return 'R';
        case BLUE : return 'B';
        case NONE : return ' ';
        default : return '/';
    }
}

char cvrt::to_char(Rank rank)
{
    switch (rank)
    {
        case FLAG : return 'D';
        case SPY : return '1';
        case SCOUT : return '2';
        case MINER : return '3';
        case SERGEANT : return '4';
        case LIEUTENANT : return '5';
        case CAPTAIN : return '6';
        case MAJOR : return '7';
        case COLONEL : return '8';
        case GENERAL : return '9';
        case MARSHAL : return 'M';
        case BOMB : return 'B';
        case UNKNOWN : return 'X';
        case WATER : return '~';
        case EMPTY : return ' ';
        default : return '/';
    }
}

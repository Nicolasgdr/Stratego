#ifndef CONVERT_H
#define CONVERT_H

#include <QString>

#include "../Stratego_libs/Model/color.h"
#include "../Stratego_libs/Model/rank.h"

/**
 * @brief Conversions to string or character for French console display.
 */

namespace cvrt
{
    /**
     * @brief Convert the given color into a string.
     * @details return "N/A" if the color is neither RED, BLUE nor NONE.
     * @param color The player's color.
     * @return A string representing the color.
     */
    QString to_qstring(Color color);

    /**
     * @brief Convert the given piece's rank into a string.
     * @details return "N/A" if the rank is invalid.
     * @param rank The rank of a piece.
     * @return A string representing the rank.
     */
    QString to_qstring(Rank rank);

    /**
     * @brief Convert the given color into a character.
     * @details return '/' if the color is neither RED, BLUE nor NONE.
     * @param color The color of a piece.
     * @return 'R' for RED, 'B' for BLUE and ' ' for NONE.
     */
    char to_char(Color color);

    /**
     * @brief Convert the given rank into a character.
     * @details An UNKNOW rank will be converted as 'X', a WATER as '~' and
     * an EMPTY as ' '.
     * The pieces will be converted as (listed by increasing strength) :
     * 'F', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'M', 'B'.
     * Any other input will be converted as '/'.
     * @throws invalid_argument if the rank is invalid.
     * @param rank The rank of a piece.
     * @return A char representing the rank.
     */
    char to_char(Rank rank);
}

#endif // CONVERT_H

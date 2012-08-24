/*!
 * \file main.cpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */

#include <QtCore/QDebug>
#include <iostream>
#include "daemon.hpp"


/*!
 * @brief fonction main
 *
 * @param argc
 * @param argv[]
 * @return int
 */
int main(int argc, char *argv[]){
    Daemon app(argc, argv);

    app.run();
}
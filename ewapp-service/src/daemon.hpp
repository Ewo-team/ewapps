/*!
 * \file daemon.hpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 19 aout 2012
 */

#ifndef DAEMON_HPP
#define DAEMON_HPP

#include <QObject>
#include <QStringList>
#include <QMap>
#include "qtservice.h"

class Apps;

/*!
 * @brief classe principale
 * C'est une classe qui va gérer le cycle de vie du daemon
 */
class Daemon : public QtService<QCoreApplication>{


    protected:
        QStringList args;
        QMap<QString, Apps*> apps;

    public:

        static const QString SERVICE_NAME;


    public:
        /*!
     * @brief constructeur
     *
     * @param argc arguments count
     * @param argv[] arguments values
     */
        explicit Daemon(int argc, char *argv[]);

        /*!
     * @brief destructeur
     *
     */
        ~Daemon();

    protected:
        void start();
        void stop();
        void pause();
        void resume();
        void processCommand(int code);
};

#endif // DAEMON_HPP

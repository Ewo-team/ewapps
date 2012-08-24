/*!
 * \file controller.hpp
 * \author Benjamin Herbomez <benjamin.herbomez@gmail.com>
 * \version 0.1
 * \date 24 aout 2012
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QStringList>
#include <QLatin1String>
#include "qtservice.h"

/**
 * @brief class qui permet de controler le service
 *
 */
class Controller : public QtServiceController{

    protected:
        QStringList args;

    public:
        static const QString START;
        static const QString STOP;
        static const QString RESTART;
        static const QString RELOAD;
        static const QString STATE;

        static const QString SERVICE_NAME;

    public:

        /**
         * @brief constructeur
         *
         * Construit le controler à partir des arguments passés en commande
         *
         * @param argc nombre d'arguments
         * @param argv[] liste des arguments
         */
        Controller(int argc, char *argv[]);


        /**
         * @brief destructeur
         *
         */
        ~Controller();


        /**
         * @brief lance le controler
         *
         */
        void run();

    protected:

        /**
         * @brief gestion de la méthode start
         *
         * @param appsList liste des applications à demmarer
         */
        void handleStart(QStringList appsList);

        /**
         * @brief gestion du stop d'applis
         *
         * @param appsList liste des applications à stoper
         */
        void handleStop(QStringList appsList);

        /**
         * @brief gestion de la méthode restart
         *
         * @param appsList liste des applications à demmarer
         */
        void handleRestart(QStringList appsList);

        /**
         * @brief gestion des applications à recharger
         *
         * @param appsList liste des applications à recharger
         */
        void handleReload(QStringList appsList);


        /**
         * @brief gestion de la demande d'état
         *
         * @param appsList liste des applications dont on veut l'état
         * @return QString état des applications
         */
        QString handleState(QStringList appsList);

        /*!
         * @brief affiche l'utilisation de la commande
         *
         */
        void displayUsage();
};


#endif // CONTROLLER_HPP

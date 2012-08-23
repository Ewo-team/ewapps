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
#include "qtsinglecoreapplication.h"

/*!
 * @brief classe principale
 * C'est une classe qui va gérer le cycle de vie du daemon
 */
class Daemon : public QtSingleCoreApplication{
    Q_OBJECT

protected:
    QStringList args;


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

    /*!
     * @brief run the application
     *
     * @return int le status de retour de l'application
     */
    int run();

protected:
    /*!
     * @brief fonction appelée si le daemon est déjà lancé
     *
     * @return int
     */
    void handleNewArgs();



    /*!
     * @brief affiche l'utilisation de la commande
     *
     */
    void displayUsage();
signals:
    
public slots:
    /*!
     * @brief gestion des messages reçus
     *
     * @param message message à traiter.
     */
    void handleCommand(const QString& message);
};

#endif // DAEMON_HPP

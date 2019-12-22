#ifndef CHAR_H
#define CHAR_H

#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>
#include <QFile>

#include <iostream>

class Char {
    struct WeaponDamage
    {
        int slashDamage{};
        int thrustDamage{};
        int bluntDamage{};
    };
public:
    Char() {
        hp = 0;
        level = 0;
    }
    Char(QString name, int hp, int level) : name{name}, hp{hp}, level{level} {

    }

    //getter and setter
    void setName(QString name) {this->name = name;}
    QString getName() const {return name;}

    void setLevel(int level) {this->level = level;}
    int getLevel() const {return level;}

    void setHp(int hp) {this->hp = hp;}
    int getHp() const {return hp;}


    //========== json ==========
    //struct einlesen
    void readWeaponJ(const QJsonObject &json);
    void writeWeaponJ(QJsonObject &json) const;

    void readJ(const QJsonObject &json);
    void writeJ(QJsonObject &json) const;

    void loadPrepareJ(const QJsonObject &json);
    void storeJ(QJsonObject &json) const;

    void loadJ();
    void saveJ();

private:
    QString name;
    int hp;
    int level;
    WeaponDamage weapon;
};





#endif // CHAR_H

//! [0] Es MUSS IMMER alles komplett eingelsesen und geschrieben werden, ansonsten werden Sachen überschrieben!!!


/*
 * vorgehen vom speichern und lesen von und in eine json Date:
 *
 * [0]schreiben und laden:
 * [1].Schritt: Attribute des Objekts in json Values verpacken
 * [2].Schritt: Ein QJSonObject bennenen, dieses Objekt in die write methode übergeben und das Objekt json typisch benennen
 *  es können qJsonObjects in neue QJSonObjects gescpeichert werden um mehtr struktur zu bekommen
 *
 *
 * [4] Lesen eines Json Dokuments
 *
 */

#include "Char.h"



//! [0] In eine JSon Datei schreiben

//! [1] Attribute in json values umwandeln
void Char::writeJ(QJsonObject &json) const {
    json["Name"]=name;
    json["Healthpoints"]=hp;
    if(level != 0)//überprüfung ob level gesetzt wurde oder nicht
    json["Level"]=level;

    //struct
    QJsonObject weaponObjectJ;
    writeWeaponJ(weaponObjectJ);
    json["Waffe"]=weaponObjectJ;
}

//struct
void Char::writeWeaponJ(QJsonObject &json) const {
    json["Schlagschaden"]=weapon.slashDamage;
    json["Stichschaden"]=weapon.thrustDamage;
    json["HiebSchaden"]=weapon.bluntDamage;
}



//! [2] Die geschriebenen Attribute in einem QJSonObject speichern
void Char::storeJ(QJsonObject &json) const {

    QJsonObject charObject;
    writeJ(charObject);
    json["Character"]=charObject;

    /* QJsonArray levelArray;
    //wieder für jedes element level aus dem vector mLevel
    foreach (const Level level, mLevels) {
        //neues object für jedes einzelne level
        QJsonObject levelObject;
        //jedes level schreibt in in das object hinein
        level.write(levelObject);
        //object wird in das array eingetragen
        levelArray.append(levelObject);
    }
    //foreach vorbei, array wird für json benannt
    json["levels"] = levelArray;
    */
}

//! [3] IN eine .json datei speichern
void Char::saveJ() {

    QFile saveFileJ("test.json");

    if(!saveFileJ.open(QIODevice::WriteOnly)) {
        qWarning("Task failed succesfully");
    }
    //saveObj wird hier als übergeordnetes Objekt genutz in das alles hineingescgrieben wurde.
    //Das schreiben selber passiert in der aufgerufenen Methode
    QJsonObject saveObj;
    storeJ(saveObj);

    QJsonDocument saveDocJ(saveObj);

    saveFileJ.write(saveDocJ.toJson());
}
//====================   ====================
//! [4]

void Char::readJ(const QJsonObject &json) {

    if(json.contains("Name") && json["Name"].isString()) {
        name = json["Name"].toString();
    }
    if(json.contains("Healthpoints") && json["Healthpoints"].isDouble()) {
        hp = json["Healthpoints"].toInt();
    }
    if(json.contains("Level") && json["Level"].isDouble()) {
        level = json["Level"].toInt();
    }

    //struct
    if(json.contains("Waffe") && json["Waffe"].isObject()) {
        readWeaponJ(json["Waffe"].toObject());
    }
}

//struct
void Char::readWeaponJ(const QJsonObject &json) {
    if(json.contains("Schlagschaden") && json["Schlagschaden"].isDouble()) {
        weapon.slashDamage = json["Schlagschaden"].toInt();
    }
    if(json.contains("Stichschaden") && json["Stichschaden"].isDouble()) {
        weapon.thrustDamage = json["Stichschaden"].toInt();
    }
    if(json.contains("HiebSchaden") && json["HiebSchaden"].isDouble()) {
        weapon.bluntDamage = json["HiebSchaden"].toInt();
    }
}

void Char::loadPrepareJ(const QJsonObject &json) {

    if(json.contains("Character") && json["Character"].isObject()) {
        readJ(json["Character"].toObject());
    }

    /*
     * //test für levels ob es ein arary ist
    if (json.contains("levels") && json["levels"].isArray()) {
        //neues array erstellen und darin den inhalt aus dem json arary kopieren
        QJsonArray levelArray = json["levels"].toArray();
        //vector clearen
        mLevels.clear();
        //größe des vectors reservieren
        mLevels.reserve(levelArray.size());
        //inhalt des temp arrays wird pro index einem object übergeben
        for (int levelIndex = 0; levelIndex < levelArray.size(); ++levelIndex) {
            //und zwar hier
            QJsonObject levelObject = levelArray[levelIndex].toObject();
            //level ertellen
            Level level;
            //jedem level wird jezt der Inhalt des objects übergeben
            level.read(levelObject);
            //die einzelnen levels werden zu dem vector hinzugefügt
            mLevels.append(level);
        }
    }
    */
}

void Char::loadJ() {

    QFile loadFile("test.json");

    if(!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Task failed succesfuly");
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDocJ(QJsonDocument::fromJson(saveData));

    loadPrepareJ(loadDocJ.object());
}



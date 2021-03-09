#ifndef BELANG_H
#define BELANG_H

#include <QtCore>
#include <QDebug>
#include <QFont>
#include <QDir>
#include <QTranslator>
#include <QString>
#include <QGuiApplication>
#include <QObject>
#include <QDebug>
#include <QQmlEngine>

#define DEF_TS_FOLDER ":/lang"

class BELang : public QObject
{
    std::vector<QString> langs;

    Q_OBJECT

    int defLangId;
    QString defTsFolder;

    int currLangId = 0;
    QTranslator *translator;
    QQmlEngine *m_engine;
    QJsonDocument fontConfig;

public:

    explicit BELang(QQmlEngine *engine, const std::initializer_list<QString> langs, const int defLangIndex = 0, const QString& tsFolder = DEF_TS_FOLDER);
    virtual ~BELang() = default;

    Q_INVOKABLE QVariant getFont(const QString& fontId);
    Q_INVOKABLE void selectLanguage(const int lang_id) { selectLanguage(lang_id, getLangCodebyId(lang_id)); }
    Q_INVOKABLE void selectLanguage(const QString& lang_code) { selectLanguage(getLangIdByCode(lang_code), lang_code); }

signals:

    void languageChanged();

private:

    inline QString getLangCodebyId(const size_t langId) { return (langId > langs.size()) ? "" : langs[langId] ; }
    inline int getLangIdByCode(const QString& langCode) { int i = -1; for(auto lc: langs) { i++; if (lc == langCode) break; } return i; }

    void selectLanguage(const int lang_id, const QString& lang_code);
    void loadFontConfig();
};

#endif // BELANG_H

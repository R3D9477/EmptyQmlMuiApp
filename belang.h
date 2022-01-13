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
    std::vector<QString> m_langs;

    Q_OBJECT

    size_t m_defLangId{0};
    QString m_defTsFolder;

    size_t m_currLangId{0};
    QTranslator *m_translator;
    QQmlEngine *m_engine;
    QJsonDocument m_fontConfig;

public:

    explicit BELang(QQmlEngine *engine, const std::initializer_list<QString> langs,
        const size_t defLangIndex = 0, const QString& tsFolder = DEF_TS_FOLDER);

    virtual ~BELang() = default;

    Q_INVOKABLE QVariant getFont(const QString& fontId);
    Q_INVOKABLE void selectLanguage(const size_t lang_id) { selectLanguage(lang_id, getLangCodebyId(lang_id)); }
    Q_INVOKABLE void selectLanguage(const QString& lang_code) { selectLanguage(getLangIdByCode(lang_code), lang_code); }

    Q_INVOKABLE size_t getCurrLangId () const { return this->m_currLangId; }
    Q_INVOKABLE QString getCurrLangCode() const { return getLangCodebyId(this->m_currLangId); }

signals:

    void languageChanged();

private:

    inline QString getLangCodebyId(const size_t langId) const { return (langId > m_langs.size()) ? "" : m_langs[langId] ; }
    inline size_t getLangIdByCode(const QString& langCode) const { size_t i = 0; for (auto lc: m_langs) { i++; if (lc == langCode) break; } return i; }

    void selectLanguage(const size_t lang_id, const QString& lang_code);
    void loadFontConfig();
};

#endif // BELANG_H

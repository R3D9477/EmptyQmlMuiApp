#include "belang.h"

BELang::BELang(QQmlEngine *engine, const std::initializer_list<QString> langs,
    const size_t defLangIndex, const QString& tsFolder)
{
    this->m_defLangId = ( defLangIndex < langs.size() ) ? defLangIndex : 0;
    this->m_defTsFolder = tsFolder;

    this->m_translator = new QTranslator(this);
    this->m_engine = engine;

    for (auto& l: langs) this->m_langs.push_back(l);

    this->loadFontConfig();
}

QVariant BELang::getFont(const QString& fontId)
{
    QFont font;
    font.setFamily(font.defaultFamily());

    if (!this->m_fontConfig.isEmpty()) {

        auto jobj = this->m_fontConfig.object();

        if (jobj.contains(fontId)) {
            auto fcLang = jobj[fontId].toObject();
            if (fcLang.contains("family"))
                font.setFamily(fcLang["family"].toString());
            if (fcLang.contains("size"))
                font.setPointSizeF(fcLang["size"].toVariant().toInt());
            if (fcLang.contains("bold"))
                font.setBold(fcLang["bold"].toVariant().toBool());
            if (fcLang.contains("italic"))
                font.setItalic(fcLang["italic"].toVariant().toBool());
        }
    }

    return font;
}

void BELang::loadFontConfig()
{
    QFile cfFile(QString("%1/fc_%2.json").arg(this->m_defTsFolder, getLangCodebyId(this->m_currLangId)));

    if (cfFile.open(QIODevice::ReadOnly)) {

        QJsonParseError jerr;
        QJsonDocument fcJsBuff = QJsonDocument::fromJson(cfFile.readAll(), &jerr);

        if (jerr.error == QJsonParseError::NoError)
            this->m_fontConfig = fcJsBuff;

        cfFile.close();
        return;
    }

    this->m_fontConfig = QJsonDocument();
}

void BELang::selectLanguage(const size_t lang_id, const QString& lang_code)
{
    if (this->m_langs.size() > 0) {

        if (lang_code == this->m_langs[this->m_defLangId]) qGuiApp->removeTranslator(this->m_translator);
        else if (m_translator->load(QString("tr_%1").arg(lang_code), this->m_defTsFolder)) qApp->installTranslator(this->m_translator);

        this->m_currLangId = lang_id;
        this->loadFontConfig();
        this->m_engine->retranslate();

        emit languageChanged();
    }
}

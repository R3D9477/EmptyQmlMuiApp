#include "belang.h"

BELang::BELang(QQmlEngine *engine, const std::initializer_list<QString> langs, const int defLangIndex, const QString& tsFolder)
{
    this->defLangId = ( defLangIndex < int(langs.size()) ) ? defLangIndex : 0;
    this->defTsFolder = tsFolder;

    this->translator = new QTranslator(this);
    this->m_engine = engine;

    for (auto& l: langs) this->langs.push_back(l);

    this->loadFontConfig();
}

QVariant BELang::getFont(const QString& fontId)
{
    QFont font;
    font.setFamily(font.defaultFamily());

    if (!this->fontConfig.isEmpty()) {

        auto jobj = this->fontConfig.object();

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
    QFile cfFile(QString("%1/fc_%2.json").arg(this->defTsFolder, getLangCodebyId(this->currLangId)));

    if (cfFile.open(QIODevice::ReadOnly)) {

        QJsonParseError jerr;
        QJsonDocument fcJsBuff = QJsonDocument::fromJson(cfFile.readAll(), &jerr);

        if (jerr.error == QJsonParseError::NoError)
            this->fontConfig = fcJsBuff;

        cfFile.close();
        return;
    }

    this->fontConfig = QJsonDocument();
}

void BELang::selectLanguage(const int lang_id, const QString& lang_code)
{
    if (this->langs.size() > 0) {

        if (lang_code == this->langs[this->defLangId]) qGuiApp->removeTranslator(this->translator);
        else if (translator->load(QString("tr_%1").arg(lang_code), this->defTsFolder)) qApp->installTranslator(this->translator);

        this->currLangId = lang_id;
        this->loadFontConfig();
        this->m_engine->retranslate();

        emit languageChanged();
    }
}

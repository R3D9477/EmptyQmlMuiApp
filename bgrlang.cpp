#include "bgrlang.h"

BGRLang::BGRLang(QQmlEngine *engine, std::initializer_list<QString> langs)
{
    translator = new QTranslator(this);
    m_engine = engine;
    for (auto l: langs) this->langs.push_back(l);
}

QVariant BGRLang::getFont(const QString& fontId)
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

void BGRLang::loadFontConfig()
{
    QFile cfFile(QString(":/lang/fc_%1.json").arg(getLangCodebyId(this->currLangId)));

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

void BGRLang::selectLanguage(const int lang_id, const QString& lang_code) {
    if (this->langs.size() > 0) {
        if (lang_code == this->langs[0])
            qGuiApp->removeTranslator(this->translator);
        else if (translator->load(QString("tr_%1").arg(lang_code), ":/lang"))
            qApp->installTranslator(this->translator);
        this->currLangId = lang_id;
        this->loadFontConfig();
        this->m_engine->retranslate();
        emit languageChanged();
    }
}

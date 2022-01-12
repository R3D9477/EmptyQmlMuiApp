import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World!")

    Row {
        x: 0
        y: 0

        Button {
            id: btnSetEnLang
            text: qsTr("English")

            Connections {
                target: btnSetEnLang
                function onClicked() { beLang.selectLanguage("en") }
            }
        }

        Button {
            id: btnSetEsLang
            text: qsTr("Español")

            Connections {
                target: btnSetEsLang
                function onClicked() { beLang.selectLanguage("es") }
            }
        }

        Button {
            id: btnSetRuLang
            text: qsTr("Русский")

            Connections {
                target: btnSetRuLang
                function onClicked() { beLang.selectLanguage("ru") }
            }
        }
    }

    Text {
        id: text1
        x: 0
        y: 50
        width: 199
        height: 24
        text: qsTr("Hello World!")
        horizontalAlignment: Text.AlignHCenter

        Component.onCompleted: font = beLang.getFont("label")
        Connections { target: beLang; function onLanguageChanged () { text1.font = beLang.getFont("label"); } }
    }
}

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
                function onClicked() { bgrLang.selectLanguage("en") }
            }
        }

        Button {
            id: btnSetEsLang
            text: qsTr("Español")

            Connections {
                target: btnSetEsLang
                function onClicked() { bgrLang.selectLanguage("es") }
            }
        }

        Button {
            id: btnSetRuLang
            text: qsTr("Русский")

            Connections {
                target: btnSetRuLang
                function onClicked() { bgrLang.selectLanguage("ru") }
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

        Component.onCompleted: font = bgrLang.getFont("label")
        Connections { target: bgrLang; function onLanguageChanged () { text1.font = bgrLang.getFont("label"); } }
    }
}

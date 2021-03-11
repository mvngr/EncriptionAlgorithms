import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Ciphers.Transposition 1.0
import Ciphers.MagicSquare 1.0

ApplicationWindow {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Android project")

    property var fontSize: 14
    property var textColor: "#ffffff"

    font.pixelSize: fontSize




    Column {
        property var paddingSize: parent.width * 0.02
        anchors.fill: parent
        padding: paddingSize

        ComboBox {
            id: chiperChooser
            width: parent.width - parent.paddingSize * 2
            textRole: "text"

            model: ListModel {

                id: model
                ListElement { text: qsTr("Шифр перестановок"); value: "Transposition" }
                ListElement { text: qsTr("Шифр магический квадрат"); value: "MagicSquare" }
            }

            currentIndex: 0
        }

        Text {
            id: sourceTextPlaceholder
            text: qsTr("Исходный текст:")
            font.pixelSize: fontSize
            color: textColor
        }


        TextField {
            id: sourceText
            text: ""
        }

        Text {
            id: encryptedTextPlaceholder
            text: qsTr("Зашифрованный текст:")
            font.pixelSize: fontSize
            color: textColor
        }

        TextField {
            id: encryptedText
            text: ""
        }
    }

}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/

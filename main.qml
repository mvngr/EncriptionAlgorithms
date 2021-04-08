import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Ciphers.Transposition 1.0
import Ciphers.MagicSquare 1.0
import Ciphers.Caesar 1.0
import Ciphers.Gronsfeld 1.0

ApplicationWindow {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Android project")

    property var fontSize: 14
    property var textColor: "#ffffff"

    font.pixelSize: fontSize

    function currentClass()
    {
        var targetClass

        switch(chiperChooser.model.get(chiperChooser.currentIndex).value)
        {
        case 'Transposition':
            targetClass = transpositionCipher
            break
        case 'MagicSquare':
            targetClass = magicSquareCipher
            break
        case 'Caesar':
            targetClass = caesarCipher
            break
        case 'Gronsfeld':
            targetClass = gronsfeldCipher
            break
        }

        return targetClass
    }

    Column {
        property var paddingSize: parent.width * 0.02
        property var defaultWidth: width - paddingSize * 2
        anchors.fill: parent
        padding: paddingSize

        MagicSquareCipher {
            id: magicSquareCipher
        }

        TranspositionCipher {
            id: transpositionCipher
        }

        CaesarCipher {
            id: caesarCipher
        }

        GronsfeldCipher {
            id: gronsfeldCipher
        }

        ComboBox {
            id: chiperChooser
            width: parent.defaultWidth
            textRole: "text"

            model: ListModel {

                id: model
                ListElement { text: qsTr("Шифр Гронсфельда"); value: "Gronsfeld" }
                ListElement { text: qsTr("Шифр перестановок"); value: "Transposition" }
                ListElement { text: qsTr("Шифр магический квадрат"); value: "MagicSquare" }
                ListElement { text: qsTr("Шифр Цезаря"); value: "Caesar" }
            }

            currentIndex: 0

            onCurrentTextChanged: function() {
                keyText.text = mainWindow.currentClass().defaultKey()
            }
        }

        Text {
            id: keyTextPlaceholder
            text: qsTr("Ключ:")
            font.pixelSize: fontSize
            color: textColor
        }

        TextField {
            id: keyText
            text: ""
            width: parent.defaultWidth
            onTextChanged: function() {
                var currentClass = mainWindow.currentClass()
                var isOk = currentClass.setKey(text)
                if(isOk !== true)
                {
                    errors.text = currentClass.errorString()
                }
            }
        }

        Text {
            id: sourceTextPlaceholder
            text: qsTr("Исходный (расшифрованный) текст:")
            font.pixelSize: fontSize
            color: textColor
        }

        TextField {
            id: sourceText
            text: ""
            width: parent.defaultWidth
        }


        Button {
            id: doEncrypt
            text: qsTr("Зашифровать")
            onClicked: function() {
                var targetClass = mainWindow.currentClass()
                encryptedText.text = targetClass.encrypt(sourceText.text)
                errors.text = targetClass.errorString()
            }
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
            width: parent.defaultWidth
        }

        Button {
            id: doDecrypt
            text: qsTr("Расшифровать")
            onClicked: function() {
                var targetClass = mainWindow.currentClass()
                sourceText.text = targetClass.decrypt(encryptedText.text)
                errors.text = targetClass.errorString()
            }
        }

        Text {
            id: errors
            text: ""
            font.pixelSize: fontSize
            color: '#ff6666'
        }
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/

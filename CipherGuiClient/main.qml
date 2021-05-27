import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Ciphers.Transposition 1.0
import Ciphers.MagicSquare 1.0
import Ciphers.Caesar 1.0
import Ciphers.Gronsfeld 1.0
import Ciphers.Playfair 1.0
import Ciphers.GiovanniPorta 1.0
import Ciphers.Vigenere 1.0
import Ciphers.Trithemius 1.0
import Ciphers.Spiral 1.0
import CiphersTcpClient 1.0

ApplicationWindow {
    id: mainWindow
    width: 640
    height: 600
    visible: true
    title: qsTr("Android project")

    property int fontSize: 14
    property string textColor: "#ffffff"

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
        case 'Playfair':
            targetClass = playfairCipher
            break
        case 'GiovanniPorta':
            targetClass = giovanniPortaCipher
            break
        case 'Vigenere':
            targetClass = vigenereCipher
            break
        case 'Trithemius':
            targetClass = trithemiusCipher
            break
        case 'Spiral':
            targetClass = spiralCipher
            break
        }

        return targetClass
    }

    Column {
        property real paddingSize: parent.width * 0.02
        property real defaultWidth: width - paddingSize * 2
        anchors.fill: parent
        padding: paddingSize

        TcpClient {
            id: tcpClient

            onRecieveMessageFromServer: function() {
                textArea.text = serverMessage
            }
        }

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

        PlayfairCipher {
            id: playfairCipher
        }

        GiovanniPortaCipher {
            id: giovanniPortaCipher
        }

        VigenereCipher {
            id: vigenereCipher
        }

        TrithemiusCipher {
            id: trithemiusCipher
        }

        SpiralCipher {
            id: spiralCipher
        }

        ComboBox {
            id: chiperChooser
            width: parent.defaultWidth
            textRole: "text"

            model: ListModel {

                id: model

                ListElement { text: qsTr("Шифр Спирали"); value: "Spiral" }
                ListElement { text: qsTr("Шифр Цезаря"); value: "Caesar" }
                ListElement { text: qsTr("Шифр Трисемуса"); value: "Trithemius" }
                ListElement { text: qsTr("Шифр Виженера"); value: "Vigenere" }
                ListElement { text: qsTr("Шифр Джованни Порты"); value: "GiovanniPorta" }
                ListElement { text: qsTr("Шифр Плейфера"); value: "Playfair" }
                ListElement { text: qsTr("Шифр Гронсфельда"); value: "Gronsfeld" }
                ListElement { text: qsTr("Шифр перестановок"); value: "Transposition" }
                ListElement { text: qsTr("Шифр магический квадрат"); value: "MagicSquare" }
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

        Text {
            id: ipServerPlaceholder
            text: qsTr("IP адрес сервера:")
            font.pixelSize: fontSize
            color: textColor
        }

        TextField {
            id: ipServer
            text: "127.0.0.1"
            width: parent.defaultWidth
            onTextChanged: function() {
                tcpClient.setHost(ipServer.text);
            }
        }

        Button {
            id: sendToServer
            text: qsTr("Отправить на сервер")
            onClicked: function() {
                var targetClass = mainWindow.currentClass()
                var cipherName = chiperChooser.model.get(chiperChooser.currentIndex).value
                tcpClient.sendDataToServer(cipherName, targetClass.encrypt(sourceText.text))
            }
        }

        Text {
            id: serverBoxPlaceholder
            text: qsTr("Информация с сервера:")
            font.pixelSize: fontSize
            color: textColor
        }

        TextArea {
            id: textArea
            placeholderText: qsTr("Информация с сервера")
            width: parent.defaultWidth
            height: 100
            enabled: false
            color: textColor
            wrapMode: Text.WordWrap
        }


    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/

import QtQuick

Window {
    id : root
    width: 640
    height: 480
    visible: true
    title: qsTr("Игра Пятнашки")

    GameBoard {
        anchors.fill: parent
    }
}

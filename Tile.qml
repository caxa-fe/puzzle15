import QtQuick

Rectangle {

    color: "lightgreen"
    border.color: "#77bd77"
    border.width: width / 40
    radius: width / 10

    property string tileText: ""

    Text {
        text: parent.tileText
        font.family: "Segoe"
        font.bold: true
        font.pointSize: Math.max(2, Math.min(parent.width, parent.height) / 2)
        color: "green"
        anchors.centerIn: parent

    }

}

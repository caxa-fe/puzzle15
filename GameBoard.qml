import QtQuick
import Game 1.0
GridView {
    id: root
    model: GameBoardModel {

    }

    cellWidth: width / root.model.dimension
    cellHeight: height / root.model.dimension

    delegate: Item {
        id: cellWrap
        width:  root.cellWidth
        height: root.cellHeight

        visible: display !== root.model.hiddenElementValue

        Tile {
            tileText: display
            anchors.fill: parent
            anchors.margins: (root.cellWidth + root.cellHeight) / 160
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.model.move(index);
                }
            }
        }
    }

}

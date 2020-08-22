import QtQuick.Layouts 1.1
import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.1
import QtQuick.Controls 1.4 as C1
import QtQuick.Controls.Styles 1.2

C1.TableView {
    id: tableView
    width: 800
    height: 600
    property alias tableView: tableView
    alternatingRowColors: false
    layer.textureSize.width: 1
    model: persons
    selectionMode: C1.SelectionMode.SingleSelection

    C1.TableViewColumn {
        role: "iid"
        title: "ID"
    }
    C1.TableViewColumn {
        role: "name"
        title: "Name"
    }
    C1.TableViewColumn {
        role: "phone"
        title: "Phone"
    }
    C1.TableViewColumn {
        role: "country"
        title: "Country"
    }

    MouseArea {
         anchors.fill: parent
         acceptedButtons: Qt.RightButton
         onClicked: {
             tableView.update()
             cMenu.open()
         }
     }

     Menu {
         id: cMenu
         title: "&contextMenu"
         MenuItem {
             text: "A&dd"
             onTriggered: {
                 persons.add()
                 tableView.update()
             }
         }

         MenuItem {
             text: "R&emove"
             onTriggered: {
                 persons.removeRow(tableView.currentRow.toFixed(0))
                 tableView.update()
             }
         }
     }

    Component {
         id: editableDelegate
         Item {
             Text {
                 width: parent.width
                 anchors.margins: 4
                 anchors.left: parent.left
                 anchors.verticalCenter: parent.verticalCenter
                 elide: styleData.elideMode
                 text: styleData.value !== undefined ? styleData.value : ""
                 color: styleData.textColor
                 visible: !styleData.selected
             }
             Loader {
                 id: loaderEditor
                 anchors.fill: parent
                 anchors.margins: 4
                 Connections {
                     target: loaderEditor.item
                     onEditingFinished: {
                         persons.updateCell(styleData.row, loaderEditor.item.text, styleData.column)
                         tableView.update()
                     }
                 }
                 sourceComponent: styleData.selected ? editor : null
                 Component {
                     id: editor
                     TextInput {
                         id: textinput
                         color: styleData.textColor
                         text: styleData.value
                         MouseArea {
                             id: mouseArea
                             anchors.fill: parent
                             hoverEnabled: true
                             onClicked: textinput.forceActiveFocus()
                         }
                     }
                 }
             }
         }
     }
     itemDelegate: {
         return editableDelegate;
     }
}

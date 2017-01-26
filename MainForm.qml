import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2

Item {

    anchors.fill: parent
    property alias preview: preview
    property alias lbl_status: lbl_status
    property alias bt_browse: bt_browse
    property alias slider_threshold: slider_threshold
    property alias slider_scale: slider_scale
    property alias img_container: img_container

    width: 240
    height: 320

    Rectangle {

        FileDialog {
            id: file_dialog
            visible: false
            title: "Select an image"
            nameFilters: ["Image files (*.png *.jpg)"]
            onAccepted: {
                main_qml.update_filename(fileUrl)
            }
        }

        id: rect
        color: "#69d56f"
        anchors.fill: parent
        ColumnLayout {
            id: columnLayout
            anchors.fill: parent
            anchors.margins: 3

            ColumnLayout {
                id: columnLayout1
                Layout.fillWidth: true
                Text {
                    id: text1
                    text: qsTr("THRESHOLD:")
                    Layout.fillWidth: true
                    fontSizeMode: Text.Fit
                    font.family: "Courier"
                    font.pixelSize: 20
                }

                Slider {
                    id: slider_threshold
                    activeFocusOnPress: false
                    tickmarksEnabled: false
                    value: 0
                    maximumValue: 127
                    stepSize: 1
                    Layout.fillWidth: true
                }

                Text {
                    id: text2
                    text: qsTr("OBJECT SCALE:")
                    font.pixelSize: 20
                    fontSizeMode: Text.Fit
                    font.family: "Courier"
                    Layout.fillWidth: true
                }

                Slider {
                    id: slider_scale
                    minimumValue: 0
                    tickmarksEnabled: true
                    value: 0
                    maximumValue: 100
                    stepSize: 1
                    Layout.fillWidth: true
                }
            }

            RowLayout {
                anchors.margins: 5
                spacing: 10
                Layout.fillWidth: true

                Label {
                    id: label
                    text: qsTr("STATUS: ")
                    font.pointSize: 12
                    fontSizeMode: Text.Fit
                    font.family: "Courier"
                }

                Label {
                    id: lbl_status
                    Layout.fillWidth: true
                    text: qsTr("Threshold = 0;\nObject scale = 0px;\nShrimp = 0seed(s);")
                    leftPadding: -1
                    rightPadding: -0.1
                    fontSizeMode: Text.Fit
                    font.pointSize: 10
                    font.family: "Courier"
                }
            }

            Rectangle {
                id: img_container
                border.color: "black"
                Layout.fillHeight: true
                Layout.fillWidth: true

                Image {
                    id: preview
                    source: "shrimp.png"
                    anchors.rightMargin: 10
                    anchors.leftMargin: 10
                    anchors.bottomMargin: 10
                    anchors.topMargin: 10
                    fillMode: Image.PreserveAspectFit
                    anchors.fill: parent
                    cache: false
                }
            }

            Button {
                id: bt_browse
                Layout.fillWidth: true
                text: qsTr("BROWSE")
                enabled: true
                onClicked: file_dialog.visible = true
            }
        }
    }
}

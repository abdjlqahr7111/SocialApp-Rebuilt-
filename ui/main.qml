import QtQuick
import QtQuick.Controls
import QtMultimedia
import SocialApp.Core 1.0

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true
    title: "SocialApp"

    property bool isRecording: false

    DatabaseHandler {
        id: dbHandler
        Component.onCompleted: {
            if (dbHandler.initialize()) {
                console.log("Database initialized successfully")
            } else {
                console.error("Database initialization failed")
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: mainView
    }

    Component {
        id: mainView
        
        Rectangle {
            color: "#1a1a2e"
            
            Column {
                anchors.centerIn: parent
                spacing: 20

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "SocialApp"
                    color: "white"
                    font.pixelSize: 32
                    font.bold: true
                }

                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Open Camera"
                    onClicked: stackView.push(cameraView)
                }

                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "View Stories"
                    onClicked: stackView.push(storiesView)
                }
            }
        }
    }

    Component {
        id: cameraView
        
        Rectangle {
            color: "black"
            
            CaptureSession {
                id: captureSession
                camera: Camera {
                    id: camera
                    active: true
                }
                videoOutput: videoOutput
            }

            VideoOutput {
                id: videoOutput
                anchors.fill: parent
            }

            Rectangle {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 30
                width: 70
                height: 70
                radius: 35
                color: root.isRecording ? "red" : "white"
                border.width: 4
                border.color: "gray"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        root.isRecording = !root.isRecording
                        if (root.isRecording) {
                            console.log("Recording started")
                        } else {
                            console.log("Recording stopped")
                        }
                    }
                }
            }

            Button {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.margins: 20
                text: "Back"
                onClicked: stackView.pop()
            }
        }
    }

    Component {
        id: storiesView
        
        Rectangle {
            color: "#1a1a2e"

            Text {
                anchors.centerIn: parent
                text: "Stories coming soon..."
                color: "white"
                font.pixelSize: 18
            }

            Button {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.margins: 20
                text: "Back"
                onClicked: stackView.pop()
            }
        }
    }
}

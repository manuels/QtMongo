import Qt 4.7

Rectangle {
    width: 150
    height: 40

    signal buttonClicked()
    property string text

    Text {
        id: myText
        text: parent.text
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        ColorAnimation on color {
            id: uiFeedback
            from: "white"
            to: "black"
            duration: 300
        }
    }

    MouseArea {
        id: myMouseArea
        anchors.fill: parent
        onClicked: {
            uiFeedback.start()
            parent.buttonClicked()
        }
    }

    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#e2e2e2"
        }

        GradientStop {
            position: 0.67
            color: "#bbbbbb"
        }

        GradientStop {
            position: 1
            color: "#eeeeee"
        }
    }
}

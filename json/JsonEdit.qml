import Qt 4.7
import "json2.js" as Json

Rectangle {
    border.color: "gray"

    property variant object: {}
    property bool _changeByUser: true

    onObjectChanged: {
        if (_changeByUser)
            edit.text = ""+Json.JSON.stringify(object, null, "  ")
    }

    TextEdit {
        id: edit
        anchors.fill: parent

        onTextChanged: {
            try {
                var obj = Json.JSON.parse(text)

                parent._changeByUser = false
                parent.object = obj
                parent._changeByUser = true
            }
            catch(e) {}
        }
    }
}

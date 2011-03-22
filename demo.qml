// TAKE CARE OF PATH IN qmldir FILE!
import Qt 4.7
import "QtMongo"
import "QtMongo/lib/json/json2.js" as Json

Row {
    Column {
        Text {
            text: "<b>Object List:</b>"
        }

        ListView {
            id: listview
            focus: true
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            width: 250
            height: 500

            MongoDB {
                id: db
                name: "testdb"
                host: "localhost"

                collections: [
                    MongoCollection {
                            id: mythings
                            name: "things"
                    }
                ]
            }

            // this corresponds to
            // model = mythings.find({x:4}):
            model: MongoQuery {
                collection: mythings
                query: {}
//              if you want to use objects here, you MUST use return stmts:
//              sort: { return { j: -1 } }
            }

            delegate: mydelegate
            Component {
                id: mydelegate
                Text {
                    text: "Object "+_id
                }
            }

            onCurrentIndexChanged: jsonEdit.object = listview.model.get(listview.currentIndex)
        }
    }

    Column {
        width: 500
        Row {
            spacing: 2

            Button {
                text: "save this object"
                onButtonClicked: { mythings.save(jsonEdit.object) }
            }
            Button {
                text: "query this object"
                onButtonClicked: {
                    listview.model = mythings.find(jsonEdit.object)
                                             .toModel(listview.model) // we need a parent here!
                }
            }
        }

        JsonEdit {
            id: jsonEdit
            height: 300
            width: parent.width
        }

        Rectangle {
            id: hint
            height: 100
            width: parent.width
            color: "red"

            Text {
                anchors.fill: parent
                wrapMode: Text.WordWrap
                text: "<b>Use up and down keys to navigate!</b><br/>"+
                      "You also might want to modify the <b>MongoDB.name property</b> to your database name "+
                      "and the <b>MongoCollection.name property</b> to your collection name to see any data"
            }
        }

        Row {
            spacing: 2

            Button {
                text: "Run MapReduce Demo"
                onButtonClicked: {
                    var map = function() { emit(1,{}) }
                    var reduce = function( key , values ) { return 123; };
                    var result = mythings.mapReduce(map, reduce, "testname");

                    console.log( result.find({}).count() )
                    console.log( Json.JSON.stringify(result.find({}).toArray()) )
                    listview.model = result.find({}).toModel(listview)
                }
            }
        }
    }
}

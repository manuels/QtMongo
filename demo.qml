// TAKE CARE OF PATH IN qmldir FILE!
import Qt 4.7
import "QtMongo"
import "json"
import "json/json2.js" as Json

Row {
    Text {
        text: dummyBLA;
        width:  mytest;
    }
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

/*                collections: [
                    MongoCollection {
                            id: mythings
                            name: "things"
                    }
                ]*/
            }

            delegate: mydelegate

            // this corresponds to
            // model = mythings.find({}):
/*            model: MongoQuery {
                collection: mythings
                query: { return {} }
            }*/

            Component {
                id: mydelegate

                Text {
                     // delegates can access the model using the 'obj' variable:
                    text: "Object "+obj._id
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
                text: "insert this object"
                onButtonClicked: { mythings.insert(jsonEdit.object) }
            }
            Button {
                text: "query this object"
                onButtonClicked: listview.model = mythings.find(jsonEdit.object)
            }
            Button {
                text: "my test"
                onButtonClicked: {
                    console.log(Mongo)
                    console.log(db._db)
                    console.log( Json.JSON.stringify(db._db) )
                    console.log( Json.JSON.stringify(db._db.prototype) )
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
                    var map = function() {
                        emit( "1" , { counter : 1 } );
                    }
                    var reduce = function( key , values ) {
                        return { a: "b" };
                    };
                    var result = mythings.mapReduce(map.toString(),
                                                    reduce.toString(),
                                                    {},
                                                    "myMapReduce");

                    console.log( "MapReduce result:" )
                    console.log( Json.JSON.stringify(result) )
                    listview.model = result.find() // why is this result empty??
                }
            }
        }
    }

    /*
    Here just some example code:

    console.log("this corresponds to SQL's 'WHERE j=5':")
    console.debug( db.collection("testdb.things").find({j:5}) )
    console.log("insert an object:")
    console.debug( db.collection("testdb.things").insert({ddd:445}) )

    console.log("find all objects with 'j=5' and present it in the listview:")
    listview.model = db.collection("testdb.things").find({j:5})
    console.log("find all objects and present it in the listview:")
    listview.model = db.collection("testdb.things").find({})

    console.log("find all objects with ddd=445, create a copy of it (upsert) and modify ddd to 446:")
    console.debug( db.collection("testdb.things").update({ddd:445},{ddd:446}, {upsert: true}) )
    console.log("find all objects in mythings")
    console.debug( mythings.find({}) )
    */
}

// TAKE CARE OF PATH IN qmldir FILE!
import Qt 4.7

ListView {
    id: listview
    width: 300
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

    delegate: mydelegate
    // this corresponds to mythings.find({})
    model: MongoQuery {
        collection: mythings
        query: {}
    }

    Component {
        id: mydelegate
        Text { text: obj.toString() }
    }

    Rectangle {
        id: rectangle1
        x: 183
        y: 72
        width: 100
        height: 100
        color: "#d53737"


        MouseArea {
            id: mouse_area1
            anchors.fill: parent


            onClicked: {
                // this corresponds to SQL's "WHERE j=5":
                console.debug( db.collection("testdb.things").find({j:5}) )
                // insert an object:
                console.debug( db.collection("testdb.things").insert({ddd:445}) )

                // find all objects with "j=5" and present it in the listview:
                listview.model = db.collection("testdb.things").find({j:5})
                // find all objects and present it in the listview:
                listview.model = db.collection("testdb.things").find({})

                // find all objects with ddd=445, create a copy of it (upsert) and modify ddd to 446:
                console.debug( db.collection("testdb.things").update({ddd:445},{ddd:446}, {upsert: true}) )
                // find all objects in mythings
                console.debug( mythings.find({}) )

                // map reduce:
                console.debug("mapReduce:");
                var map = function() { emit(this.j); }
                var reduce = function(k,vals) { return 1; }
                // take care: you've got to call toString() for each function!
                console.debug( mythings.mapReduce(map.toString(), reduce.toString()) )
                // but you cannot get the result of mapReduce, yet. That's what I'm currently working on
            }
        }
    }

}

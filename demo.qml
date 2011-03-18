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
                console.debug( db.collection("testdb.things").find({j:5}) )
                console.debug( db.collection("testdb.things").insert({ddd:445}) )

                listview.model = db.collection("testdb.things").find({j:5})
                listview.model = db.collection("testdb.things").find({})
                db.collection("testdb.things").find({}, ["j"]).forEach(function(x) { console.log(x) } )

                console.debug( db.collection("testdb.things").update({ddd:445},{ddd:446}, {upsert: true}) )
                console.debug( db.collections )
                console.debug( mythings.find({}) )

                console.debug("mapReduce:");
                var map = function() { emit(this.j); }
                var reduce = function(k,vals) { return 1; }

                console.inspect( mythings.mapReduce(map.toString(), reduce.toString()) )
            }
        }
    }

}

// TAKE CARE OF PATH IN qmldir FILE!
import Qt 4.7

Rectangle {
    width: 800
    height: 500

    ListView {
        id: listview
        width: 300
        height: 500
        focus: true
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

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

        // this corresponds to
        // model = mythings.find({}):
        model: MongoQuery {
            collection: mythings
            query: {}
        }

        Component {
            id: mydelegate

            Text {
                text: "Object "+obj._id
            }
        }

        onCurrentIndexChanged: {
            var obj = listview.model.list()[listview.currentIndex];
            var str = "{\n"
            for(var key in obj)
                str += "\t"+key+": "+obj[key]+"\n"
            str +="}\n"

            currentObjAsJson.text = str
        }
    }

    TextEdit {
        id: currentObjAsJson
        anchors.left: listview.right
        width: 600
        text: "hallo"
    }

    /*
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
    console.log("find all objects in mythings and convert it to an array of objects:")
    console.inspect( mythings.find({}).list() )

    console.debug("mapReduce:");
    var map = function() {
        emit( "1" , { count : 1 } );
    }
    var reduce = function( key , values ){
        var total = 0;
        for ( var i=0; i<values.length; i++ )
            total += values[i].count;
        return { count: total };
    };
    var result = mythings.mapReduce(map, reduce);
    console.log( "result:" )
    console.inspect( result )
    console.log( "result.result.find():" )
    console.inspect( result )
    console.inspect( result.find().list() )
    */


    Rectangle {
        id: hint
        width: 300
        height:  50
        color: "red"

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Text {
            text: "<b>Use up and down keys to navigate!</b>"
        }
    }
}

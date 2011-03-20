import Qt 4.7
import "../lib/mongodb/shell/db.js" as MongoDB
import "../json/json2.js" as Json


Item {
    id: db

    property string name
    property string host

    property variant _db
    Component.onCompleted: {
        console.log("MongoDB (QML) constructor begin")
        var db= new MongoDB.DB(Mongo.init(host), name)
        MongoDB.printjson(db.stats())
        MongoDB.printjson(db.getCollection("things").find().limit(3).next())
        console.log("MongoDB (QML) constructor end")
    }
}

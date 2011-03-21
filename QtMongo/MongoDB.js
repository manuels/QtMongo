var DB
var DBCollection
var DBQuery
var MapReduceResult
var __mrerror__

Qt.include("lib/mongodb/query.js")
Qt.include("lib/mongodb/collection.js")
Qt.include("lib/mongodb/db.js")

Qt.include("mongo.js")

var db;
var init = function(mongo, name) {
    db = new DB(mongo, name)
}

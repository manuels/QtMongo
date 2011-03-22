Qt.include("mongo.js")

var db;
var init = function(mongo, name) {
    db = new DB(mongo, name)
}

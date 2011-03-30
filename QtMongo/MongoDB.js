Qt.include("MongoDriverWrapper.js")
Qt.include("mongo.js")

var db;
var Mongo = new MongoDriverWrapper(mongoDriver);

var init = function(host, name) {
    db = new DB(Mongo.init(host), name)
}

/**
 * Comment this return statement out to run the unit test:
 */
//return;


console.log("Starting Unit Tests")

init("localhost", "unittestdb")
console.log("DB connection ready. Starting...")
Qt.include("jstests.js")

console.log("Unit Tests Ended")

db._mongo.myFind = function() {
    console.log("myfind")
}

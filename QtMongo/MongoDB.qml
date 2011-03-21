import Qt 4.7
import "MongoDB.js" as MongoDB
import "lib/json/json2.js" as Json

Item {
    id: mongoDatabase

    property string name
    property string host: "localhost"

    property list<MongoCollection> collections

    function addUser(username, password, readOnly) {
        return MongoDB.db.addUser(username, password, readOnly)
    }
    function auth(username, password) {
        return MongoDB.db.auth(username, password)
    }
    function cloneDatabase(fromhost) {
        return MongoDB.db.cloneDatabse(fromhost)
    }
    function copyDatabase(fromdb, todb, fromhost) {
        return MongoDB.db.copyDatabase(fromdb, todb, fromhost)
    }
    function createCollection(name, flags) {
        return MongoDB.db.createCollection(name, flags)
    }
    function currentOp() {
        return MongoDB.db.currentOp()
    }
    function dropDatabase() {
        return MongoDB.db.dropDatabase()
    }
    function removeEval(func, args) { // functions called 'eval' are not allowed
        return MongoDB.db.eval(func, args)
    }
    function getCollection(cname) {
        return MongoDB.db.getCollection(cname)
    }
    function getCollectionNames() {
        return MongoDB.db.getCollectionNames()
    }
    function getLastError() {
        return MongoDB.db.getLastError()
    }
    function getLastErrorObj() {
        return MongoDB.db.getLastErrorObj()
    }
    function getMongo() {
        return MongoDB.db.getMongo()
    }
    function getName() {
        return MongoDB.db.getName()
    }
    function getPrevError() {
        return MongoDB.db.getPrevError()
    }
    function getProfilingLevel() {
        return MongoDB.db.getProfilingLevel()
    }
    function getReplicationInfo() {
        return MongoDB.db.getReplicationInfo()
    }
    function getSisterDB(name) {
        return MongoDB.db.getSisterDB(name)
    }
    function killOp(opid) {
        return MongoDB.db.killOp(opid)
    }
    function printCollectionStats() {
        return MongoDB.db.printCollectionStats()
    }
    function printReplicationInfo() {
        return MongoDB.db.printReplicationInfo()
    }
    function printSlaveReplicationInfo() {
        return MongoDB.db.printSlaveReplicationInfo()
    }
    function printShardingStatus() {
        return MongoDB.db.printShardingStatus()
    }
    function removeUser(username) {
        return MongoDB.db.removeUser(username)
    }
    function repairDatabase() {
        return repairDatabase()
    }
    function resetError() {
        return MongoDB.db.resetError()
    }
    function runCommand(cmdObj) {
        return MongoDB.db.runCommand(cmdObj)
    }
    function serverStatus() {
        return MongoDB.db.serverStatus()
    }
    function setProfilingLevel(level, slowms) {
        return MongoDB.db.setProfilingLevel(leve, slowms)
    }
    function shutdownServer() {
        return MongoDB.db.shutdownServer()
    }
    function stats() {
        return MongoDB.db.stats()
    }
    function version() {
        return MongoDB.db.version()
    }

    Component.onCompleted: {
        MongoDB.init(Mongo.init(host), mongoDatabase.name)

        // initialize collections
        for(var i = 0; i < collections.length; ++i) {
            var coll = collections[i]
            var name = coll.name

            coll._init( MongoDB.db.getCollection(name) )
        }
    }
}

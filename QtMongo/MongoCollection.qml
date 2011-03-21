import Qt 4.7
import "MongoCollection.js" as MongoCollection

Item {
    id: mongoCollection
    property string name

    function dataSize() { return MongoCollection._coll.dataSize() }
    function distinct(key) { return MongoCollection._coll.distinct(key) }
    function drop() { return MongoCollection._coll.drop() }
    function dropIndex(name) { return MongoCollection._coll.dropIndex(name) }
    function dropIndexes() { return MongoCollection._coll.dropIndexes() }
    function ensureIndex(keypattern,options) { return MongoCollection._coll.ensureIndex(keypattern,options) }
    function reIndex() { return MongoCollection._coll.reIndex() }
    function find(query, fields) { return MongoCollection._coll.find(query, fields) }
    function findOne(query) { return MongoCollection._coll.findOne(query) }
    function findAndModify(obj) { return MongoCollection._coll.findAndModify(obj) }
    function getDB() { return MongoCollection._coll.getDB() }
    function getIndexes() { return MongoCollection._coll.getIndexes() }
    function group(obj) { return MongoCollection._coll.group(obj) }
    function mapReduce(mapFunction, reduceFunction, opt) { return MongoCollection._coll.mapReduce(mapFunction, reduceFunction, opt) }
    function remove(query) { return MongoCollection._coll.remove(query) }
    function renameCollection(newName, dropTarget) { return MongoCollection._coll.renameCollection(newName, dropTarget) }
    function runCommand(name, options) { return MongoCollection._coll.runCommand(name, options) }
    function save(obj) { return MongoCollection._coll.save(obj) }
    function stats() { return MongoCollection._coll.stats() }
    function storageSize() { return MongoCollection._coll.storageSize() }
    function totalIndexSize() { return MongoCollection._coll.totalIndexSize() }
    function totalSize() { return MongoCollection._coll.totalSize() }
    function update(query, object, upsert_bool, multi_bool) { return MongoCollection._coll.update(query, object, upsert_bool, multi_bool) }
    function validate() { return MongoCollection._coll.validate() }
    function getShardVersion() { return MongoCollection._coll.getShardVersion() }

    function _init(_coll) {
        MongoCollection._coll = _coll
    }
}

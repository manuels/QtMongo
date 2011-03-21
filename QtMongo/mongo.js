/**
 * this file ensures, that the mongo-js files get all their functions they
 * to use from their "native" mongo environment
 *
 * It also patches some mongo functions to work in the QML engine
 */
Qt.include("MongoCode.js")

var printjson = function(o) { console.log( Json.JSON.stringify(o) ) }
var tojson = Json.JSON.stringify

var assert = function(arg, msg) { if (!arg) throw "Assertion failed: "+msg }
assert.eq = function(a,b, msg) { if (a!=b) throw "Assertion.Eq failed: "+msg+" "+tojson(a)+" "+tojson(b) }

Object.prototype.extend = function(dst, src) {
    for(var key in src) {
        if (!Object.prototype[key])
            dst[key] = src[key]
    }
}

Object.prototype.keySet = function() {
    var set = []
    for(var key in this)
        if (!Object.prototype[key])
            set.push(key)
    return set
}

// patch mapReduce function
DBCollection.prototype.mapReduce = (function() {
    return function(map, reduce, optionsOrOutString) {
        assert( optionsOrOutString , "need to an optionsOrOutString" )

        var options = {}
        var output
        if ( typeof( optionsOrOutString ) == "string" )
            output = optionsOrOutString;
        else
            options = optionsOrOutString

        var raw = this._db._mongo.mapReduce(this._fullName, map, reduce, options, output)
        return new MapReduceResult(this._db, raw)
    }
    /* this shit does not work:
    var original = DBCollection.prototype.mapReduce;
    return function(map, reduce, opt) {
        try {
        return original.call(this,
                             new MongoCode(map, {}),
                             new MongoCode(reduce, {}),
                             opt);
        }
        catch(e) {
            console.log("mapReduce threw an exception: "+e)
        }
    };*/
})();

DBQuery.prototype.toModel = function(parent) {
    var newObject = Qt.createQmlObject("import Qt 4.7; ListModel {}", parent, "DBQuery.toModel()::dynamicCode");

    this._exec()
    while(this._cursor.hasNext())
        newObject.append( this._cursor.next() )
    return newObject
}

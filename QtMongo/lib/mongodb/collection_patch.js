var DBCollection
var MapReduceResult

Qt.include("collection.js")

DBCollection.prototype._massageObject = (function() {
    var original = DBCollection.prototype._massageObject;
    return function(q) {
        var type = typeof q;
        if ( type == "function" ) {
            return { $where : mongoDriver.createFunction(q.toString(), {}) };
        }

        return original.call(this, q);
    }
})()

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

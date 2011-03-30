var MongoDriverWrapper = function(mongoDriver) {
    this._mongoDriver = mongoDriver;
    console.log("MongoDriverWrapper")
    console.log(mongoDriver.test)
}

MongoDriverWrapper.prototype.init = function(host) {
    this._mongoDriver = mongoDriver.init(host);
    return this;
}

MongoDriverWrapper.prototype.convertObject = function(obj) {
    console.log("MongoDriverWrapper.convertObject(): "+obj);
    if (obj instanceof ObjectId) {
        console.log("  found an ObjectId");
        return this._mongoDriver.createObjectId(obj);
    }
    if (typeof(obj) == "string")
        return obj;

    var propertyBlacklist = [Object.prototype.deleteLater];
    if (obj instanceof Object) {
        var key;
        for(key in obj) {
            if (propertyBlacklist.indexOf(obj[key]) > -1)
                continue;

            console.log("  convertObject key: "+key)
            obj[key] = this.convertObject(obj[key]);
        }
    }
    return obj;
}

MongoDriverWrapper.prototype.insert = function(ns, obj) {
    console.log("MongoDriverWrapper.insert() "+ns+" "+obj)
    return this._mongoDriver.insert(ns, this.convertObject(obj));
}

MongoDriverWrapper.prototype.find = function(ns, query, fields, limit, skip, batchSize, options) {
    return this._mongoDriver.find(ns, this.convertObject(query), fields, limit, skip, batchSize, options);
}

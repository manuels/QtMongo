var MongoCode = function(code, scope) {
    this.__TYPE__ = "THIS_IS_MONGO_CODE"
    this.__code = code.toString()
    this.__scope = scope
}

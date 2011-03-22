var DBQuery

Qt.include("query.js")

DBQuery.prototype.toModel = function(parent) {
    var newObject = Qt.createQmlObject("import Qt 4.7; ListModel {}", parent, "DBQuery.toModel()::dynamicCode");

    this._exec()
    while(this._cursor.hasNext())
        newObject.append( this._cursor.next() )
    return newObject
}

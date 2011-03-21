import Qt 4.7
import "lib/json/json2.js" as Json

ListModel {
    id: mongoQuery

    property MongoCollection collection
    property variant query
    property variant sort
    property int limit: -1
    property int skip: 0

    function update() {
        clear()

        var cursor = collection.find(query)

        if (sort)
            cursor = cursor.sort(sort)
        if (skip>-1)
            cursor = cursor.skip(skip)
        if (limit>-1)
            cursor = cursor.limit(limit)

        while(cursor.hasNext)
            append(cursor.next())
    }

    Component.onCompleted: {
        update()
    }
}

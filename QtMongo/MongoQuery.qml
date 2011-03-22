import Qt 4.7
import "lib/json/json2.js" as Json

ListModel {
    id: mongoQuery

    property MongoCollection collection
    property variant query
    property variant sort
    property int limit: -1
    property int skip: 0
    property bool snapshot: false
    property bool $returnKey: false
    property int $maxScan: -1
    property variant $min
    property variant $max
    property bool $showDiskLoc: false
    property variant $hint

    function update() {
        clear()

        var cursor = collection.find(query)
        console.log( Json.JSON.stringify(query) )

        if ($returnKey)
            cursor = cursor._addSpecial("$returnKey", $returnKey)
        if (snapshot)
            cursor = cursor.snapshot()
        if ($min)
            cursor = cursor._addSpecial("$min", $min)
        if ($max)
            cursor = cursor._addSpecial("$max", $max)
        if ($showDiskLoc)
            cursor = cursor._addSpecial("$showDiskLoc", true)
        if ($hint)
            cursor = cursor._addSpecial("$hint", $hint)

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

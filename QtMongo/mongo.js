.pragma library
Qt.include("../json/json2.js")
function include(file) {
    var inc = Qt.include(file)
    if (inc.status)
        console.log("including '"+file+"' failed:"+ JSON.stringify(inc))
}

include("lib/mongodb/query_patch.js")
include("lib/mongodb/utils_patch.js")
include("lib/mongodb/collection_patch.js")
include("lib/mongodb/db_patch.js")

include("MongoCode.js")

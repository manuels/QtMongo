function Field(val){
    this.value = val;
}

Field.prototype = {
    get value(){
        return this._value;
    },
    set value(val){
        this._value = val;
    }
};

var f = new Field("test")
console.log("")

var t;
include("lib/jstests/where1.js")
include("lib/jstests/where2.js")
//include("lib/jstests/where3.js") // fails because of "t=db.where1"

db.find1=db.getCollection("find1")
include("lib/jstests/find1.js")

db.find2=db.getCollection("find2")
var r
include("lib/jstests/find2.js")

db.find3=db.getCollection("find3")
include("lib/jstests/find3.js")

var o
db.find4=db.getCollection("find4")
include("lib/jstests/find4.js")

var x
db.find5=db.getCollection("find5")
include("lib/jstests/find5.js")

db.find6=db.getCollection("find6")
db.find6a=db.getCollection("find6a")
include("lib/jstests/find6.js")

db.find7=db.getCollection("find7")
include("lib/jstests/find7.js")

// this file ensures, that the mongo-js files get all their functions they
// to use from their "native" mongo environment

var assert = function(arg) { if (!arg) throw "Assertion failed" }
assert.eq = function(a,b) { if (a!=b) throw "Assertion.Eq failed" }

var printjson = function(o) { console.log( Json.JSON.stringify(o) ) }

// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var $$String = require("bs-platform/lib/js/string.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");

function expect(expected, actual) {
  var match = expected === actual;
  if (match) {
    return /* Pass */0;
  } else {
    return /* Fail */["Expected: " + (expected + (" | Received: " + actual))];
  }
}

function runTests(tests) {
  var failingTests = List.map((function (failedTest) {
          var match = failedTest.testResult;
          var reason;
          if (match) {
            reason = match[0];
          } else {
            throw [
                  Caml_builtin_exceptions.match_failure,
                  /* tuple */[
                    "TestLib.re",
                    38,
                    11
                  ]
                ];
          }
          return {
                  reason: reason,
                  description: failedTest.description
                };
        }), List.filter((function (testCaseResult) {
                var match = testCaseResult.testResult;
                if (match) {
                  return true;
                } else {
                  return false;
                }
              }))(List.map((function (testCase) {
                  return {
                          testResult: Curry._1(testCase.test, /* () */0),
                          description: testCase.description
                        };
                }), tests)));
  var failedTestMessage = function (failedTestCase) {
    return failedTestCase.description + (" FAILED | " + failedTestCase.reason);
  };
  var messages = List.map(failedTestMessage, failingTests);
  var match = List.length(messages);
  if (match !== 0) {
    console.log($$String.concat("\n", messages));
    return /* () */0;
  } else {
    console.log("All tests passed.");
    return /* () */0;
  }
}

exports.expect = expect;
exports.runTests = runTests;
/* No side effect */

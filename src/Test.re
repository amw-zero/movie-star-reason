open MovieStarReason;

type testResult =
  | Pass
  | Fail(string);

type testCase = {
  test: unit => testResult,
  description: string,
};

type testCaseResult = {
  testResult,
  description: string,
};

type failedTestCase = {
  reason: string,
  description: string,
};

let expect = (expected, actual) =>
  expected == actual
    ? Pass
    : Fail("Expected: " ++ expected ++ " | Received: " ++ actual);


// Tests

let testViewingMovies = () => {
  let state = {movies: [||], favoritedMovies: []};
  let state = Command.viewTopMovies(state);

  let expectedMovie = {title: "Wayne's World"};
  expect(expectedMovie.title, state.movies[0].title);
};

let testFavoritingMovies = () => {
  let title = "Movie 1"
  let state = {movies: [|{title: title}|], favoritedMovies: []};
  let state = Command.toggleFavoriteMovie(state.movies[0], state);


  expect(List.hd(state.favoritedMovies).title, title);
};

// state := Command.toggleFavoriteMovie(state^.movies[2], state^)

// Js.log(state^.favoritedMovies)

let tests = [
  {test: testViewingMovies, description: "Viewing Movies"},
  {test: testFavoritingMovies, description: "Favoriting Movies"}
];

let failingTests =
  tests
  |> List.map(testCase =>
       {testResult: testCase.test(), description: testCase.description}
     )
  |> List.filter(testCaseResult =>
       switch (testCaseResult.testResult) {
       | Fail(_) => true
       | Pass => false
       }
     )
  |> List.map(failedTest => {
       let reason =
         switch (failedTest.testResult) {
         | Fail(reason) => reason
         };
       {reason, description: failedTest.description};
     });

let failedTestMessage = failedTestCase =>
  failedTestCase.description ++ " FAILED | " ++ failedTestCase.reason;

let messages = List.map(failedTestMessage, failingTests);
switch (List.length(messages)) {
  | 0 => Js.log("All tests passed.");
  | _ => Js.log(messages |> String.concat("\n"))
};


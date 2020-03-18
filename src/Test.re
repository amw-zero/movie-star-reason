open MovieStarReason;
open TestLib;

let asyncViewingMovies = () => {
  let initialState = defaultState;

  let states: ref(list(movieStarState)) = ref([]);
  let observer = s => states := [s, ...states^];

  let server = f => f([|{title: "Test Movie"}|]);

  Command.asyncTopMovies(initialState, server, observer);

  let [finalState, intermediateState] = states^;
  let intermediateStateCheck = intermediateState.isLoadingMovies == true;
  let finalStateCheck = finalState.movies[0].title == "Test Movie";

  switch (intermediateStateCheck, finalStateCheck) {
  | (false, false) => Fail("Everything is broken")
  | (false, true) => Fail("Intermediate state failed")
  | (true, false) => Fail("Final state failed")
  | (true, true) => Pass
  };
};

let testViewingMovies = () => {
  let initialState = defaultState;

  let {state, dataDependency} = Command.viewTopMovies(initialState);
  //  let world = {queue: f => f()};
  //  let finalState = execute(intermediateEnv, world);

  let expectedMovie = {title: "Wayne's World"};
  expect(expectedMovie.title, state.movies[0].title);
};

let testFavoritingMovies = () => {
  let title = "Movie 1";
  let state = {...defaultState, movies: [|{title: title}|]};

  let state = Command.toggleFavoriteMovie(state.movies[0], state);

  expect(List.hd(state.favoritedMovies).title, title);
};

let testClearingFavoriteMovies = () => {
  let state = {...defaultState, favoritedMovies: [{title: "Favorite"}]};
  let state = Command.clearFavoriteMovies(state);

  expect(List.length(state.favoritedMovies) |> string_of_int, "0");
};

let tests = [
  {test: testViewingMovies, description: "Viewing Movies"},
  {test: testFavoritingMovies, description: "Favoriting Movies"},
  {test: testClearingFavoriteMovies, description: "Clearing Favorite Movies"},
  {test: asyncViewingMovies, description: "Async fetching movies"},
];

runTests(tests);
